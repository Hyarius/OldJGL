#ifndef JGL_NETWORK_CLIENT_H
#define JGL_NETWORK_CLIENT_H

#include "jgl_locked_queue.h"
#include "jgl_network_message.h"
#include "jgl_network_connexion.h"

namespace jgl
{
	template <typename T>
	class Client
	{
	public :
		typedef void (*client_activity_funct_ptr)(jgl::Message<T>&, jgl::Data);
	protected:
		asio::io_context _asio_context;
		std::thread _thread_context;
		jgl::Connexion<T>* _connexion;

		int64_t _major_version_key_number = 0;
		int64_t _medium_version_key_number = 0;
		int64_t _minor_version_key_number = 0;
		int64_t _abstract_version_key_number = 0;

		std::map<T, client_activity_funct_ptr> _activity_map;
		std::map<T, jgl::Data> _activity_param_map;

		jgl::Locked_queue<jgl::Input_message<T>> _input;

	public:
		Client()
		{
			std::cout << "Client created" << std::endl;
		}

		virtual ~Client()
		{
			disconnect();
		}



		void add_activity(T msg_type, client_activity_funct_ptr funct, jgl::Data param)
		{
			_activity_map[msg_type] = funct;
			_activity_param_map[msg_type] = param;
		}

		void set_version(int major_version, int medium_version, int minor_version, int abstract_version)
		{
			_major_version_key_number = major_version;
			_medium_version_key_number = medium_version;
			_minor_version_key_number = minor_version;
			_abstract_version_key_number = abstract_version;
		}

		int64_t compute_magic_number(int16_t value)
		{
			return (((_major_version_key_number << 48) ^ value) + ((_medium_version_key_number << 32) & value) + ((_minor_version_key_number << 16) | value) + (_abstract_version_key_number));
		}

		bool connect(const std::string& host, const uint16_t port)
		{
			std::cout << "Client connexion started" << std::endl;
			try
			{
				asio::ip::tcp::resolver resolver(_asio_context);
				asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));

				_connexion = new Connexion<T>(jgl::Connexion_owner::client, _asio_context, asio::ip::tcp::socket(_asio_context), &_input);

				_connexion->connect_to_server(endpoints);

				_thread_context = std::thread([this]() { _asio_context.run(); });
			}
			catch (const std::exception& e)
			{
				std::cerr << "Client Exception: " << e.what() << "\n";
				return false;
			}
			catch (const std::string& ex)
			{
				std::cerr << "Client Exception: " << ex << "\n";
				return false;
			}
			catch (...)
			{
				std::cerr << "Client Exception unknow" << "\n";
				return false;
			}
			return true;
		}

		bool reconnect(const std::string& host, const uint16_t port)
		{
			try
			{
				asio::ip::tcp::resolver resolver(_asio_context);
				asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));

				_connexion->connect_to_server(endpoints);
				_connexion->input()->clear();
			}
			catch (const std::exception& e)
			{
				std::cerr << "Client Exception: " << e.what() << "\n";
				return false;
			}
			catch (const std::string& ex)
			{
				std::cerr << "Client Exception: " << ex << "\n";
				return false;
			}
			catch (...)
			{
				std::cerr << "Client Exception unknow" << "\n";
				return false;
			}
			return true;
		}

		void disconnect()
		{
			if (is_connected())
			{
				_connexion->disconnect();
			}
		
			_asio_context.stop();
			if (_thread_context.joinable())
			{
				_thread_context.join();
			}
			_input.clear();
		}

		bool is_connected()
		{
			if (_connexion)
				return _connexion->is_connected();
			else
				return false;
		}

		void update()
		{
			if (_connexion->state() == jgl::Connexion_state::unknown)
			{
				if (_input.empty() == false)
				{
					auto msg = _input.pop_front().msg;
					
					if (msg.size() == sizeof(int64_t))
					{
						int64_t key;
						int64_t result;

						msg >> key;

						msg.clear();
						result = compute_magic_number(key);
						msg << result;
						msg << key;
						send(msg);
					}
					else if (msg.size() == sizeof(bool))
					{
						bool accepted;

						msg >> accepted;
						if (accepted == true)
							_connexion->accepted_by_server();
						else
							_connexion->refused_by_server();
					}
				}
			}
			else if (_connexion->state() == jgl::Connexion_state::accepted)
			{
				if (_input.empty() == false)
				{
					auto msg = _input.pop_front().msg;

					if (_activity_map.count(msg.type()) != 0)
					{
						_activity_map[msg.type()](msg, _activity_param_map[msg.type()]);
					}
					else
					{
						std::cout << "Message_received of unknow id (" << static_cast<int>(msg.type()) << ")" << std::endl;
					}
				}
			}
			
		}

	public:
		void send(const jgl::Message<T>& msg)
		{
			if (is_connected() && _connexion->state() != jgl::Connexion_state::refused)
				_connexion->send(msg);
		}

		jgl::Locked_queue<jgl::Input_message<T>>& input()
		{
			return (_input);
		}
	};
}

#endif