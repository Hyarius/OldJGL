#ifndef JGL_NETWORK_SERVER_H
#define JGL_NETWORK_SERVER_H

#include "jgl_locked_queue.h"
#include "jgl_network_message.h"
#include "jgl_network_connexion.h"

namespace jgl
{
	template<typename T>
	class Server
	{
	public :
		typedef void (*server_activity_funct_ptr)(jgl::Connexion<T>*, jgl::Message<T>&, jgl::Data);
		typedef void (*login_funct_ptr)(jgl::Connexion<T>*, jgl::Data);
		typedef void (*logout_funct_ptr)(jgl::Connexion<T>*, jgl::Data);
	
	protected:

		login_funct_ptr _login_funct = nullptr;
		jgl::Data _login_param;
		logout_funct_ptr _logout_funct = nullptr;
		jgl::Data _logout_param;

		int32_t _key = 0;
		int64_t _major_version_key_number = 0;
		int64_t _medium_version_key_number = 0;
		int64_t _minor_version_key_number = 0;
		int64_t _abstract_version_key_number = 0;

		jgl::Locked_queue<jgl::Input_message<T>> _input;

		std::deque<jgl::Connexion<T>*> _active_connexion;
		std::deque<jgl::Connexion<T>*> _accepted_connexion;

		asio::io_context _asio_context;
		std::thread _thread_context;

		asio::ip::tcp::acceptor _acceptor;

		std::map<T, server_activity_funct_ptr> _activity_map;
		std::map<T, jgl::Data> _activity_param_map;

		uint32_t _id_count = 10000;

	public:
		Server(uint16_t port)
			: _acceptor(_asio_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
		{

		}

		virtual ~Server()
		{
			stop();
		}

		void add_activity(T msg_type, server_activity_funct_ptr funct, jgl::Data param)
		{
			_activity_map[msg_type] = funct;
			_activity_param_map[msg_type] = param;
		}

		void set_login_function(login_funct_ptr p_login_funct, jgl::Data param)
		{
			_login_funct = p_login_funct;
			_login_param = param;
		}
		void set_logout_function(logout_funct_ptr p_logout_funct, jgl::Data param)
		{
			_logout_funct = p_logout_funct;
			_logout_param = param;
		}

		void set_key(int32_t p_key)
		{
			_key = p_key;
		}

		void set_version(int major_version, int medium_version, int minor_version, int abstract_version)
		{
			_major_version_key_number = major_version;
			_medium_version_key_number = medium_version;
			_minor_version_key_number = minor_version;
			_abstract_version_key_number = abstract_version;
		}

		int64_t compute_magic_number(int32_t value)
		{
			return (((_major_version_key_number << 48) ^ value) + ((_medium_version_key_number << 32) & value) + ((_minor_version_key_number << 16) | value) + (_abstract_version_key_number));
		}

		bool start()
		{
			try
			{
				wait_for_connexion();

				_thread_context = std::thread([this]() { _asio_context.run(); });
			}
			catch (std::exception& e)
			{
				std::cerr << "[SERVER] Exception: " << e.what() << "\n";
				return false;
			}

			std::cout << "[SERVER] Started!\n";
			return true;
		}

		void stop()
		{
			_asio_context.stop();

			if (_thread_context.joinable())
				_thread_context.join();

			std::cout << "[SERVER] Stopped!\n";
		}

		void wait_for_connexion()
		{
			_acceptor.async_accept(
				[this](std::error_code ec, asio::ip::tcp::socket socket)
				{
					if (!ec)
					{
						std::cout << "[SERVER] New Connexion: " << socket.remote_endpoint() << "\n";

						jgl::Connexion<T>* newconn = new jgl::Connexion<T>(jgl::Connexion_owner::server, _asio_context, std::move(socket), &_input);

						client_connect(newconn);
						_active_connexion.push_back(std::move(newconn));

						_active_connexion.back()->connect_to_client(_id_count++);

						std::cout << "[" << _active_connexion.back()->id() << "] Connexion Approved\n";

					}
					else
					{
						std::cout << "[SERVER] New Connexion Error: " << ec.message() << "\n";
					}

					wait_for_connexion();
				});
		}

		void message(jgl::Connexion<T>* client, const jgl::Message<T>& msg)
		{
			if (client != nullptr && client->is_connected())
			{
				client->send(msg);
			}
			else
			{
				client_disconnect(client);
				_active_connexion.erase(
					std::remove(_active_connexion.begin(), _active_connexion.end(), client), _active_connexion.end());
				_accepted_connexion.erase(
					std::remove(_accepted_connexion.begin(), _accepted_connexion.end(), client), _accepted_connexion.end());
			}
		}

		void message_all(const jgl::Message<T>& msg, jgl::Connexion<T>* p_ignore = nullptr)
		{
			bool error = false;

			for (auto& client : _active_connexion)
			{
				if (client != nullptr && client->is_connected())
				{
					if (client != p_ignore)
						client->send(msg);
				}
				else if (client != nullptr)
				{
					client_disconnect(client);
					delete client;
					client = nullptr;
					error = true;
				}
			}

			if (error == true)
			{
				_active_connexion.erase(std::remove(_active_connexion.begin(), _active_connexion.end(), nullptr), _active_connexion.end());
				_accepted_connexion.erase(std::remove(_accepted_connexion.begin(), _accepted_connexion.end(), nullptr), _accepted_connexion.end());
			}
		}

		void update()
		{
			while (_input.empty() == false)
			{
				auto msg = _input.pop_front();

				on_message_reception(msg.remote, msg.msg);
			}
			for (auto& client : _active_connexion)
			{
				if (client != nullptr && client->is_connected() == false)
				{
					client_disconnect(client);
					delete client;
					client = nullptr;
				}
			}
		}

		void on_message_reception(jgl::Connexion<T>* client, jgl::Message<T>& msg)
		{
			if (client->state() == jgl::Connexion_state::accepted)
			{
				if (_activity_map.count(msg.type()) != 0)
				{
					_activity_map[msg.type()](client, msg, _activity_param_map[msg.type()]);
				}
				else
				{
					std::cout << "Message_received of unknow id (" << static_cast<int>(msg.type()) << ")" << std::endl;
				}
			}
			else if (client->state() == jgl::Connexion_state::unknown)
			{
				valid_client_connect(client, msg);
			}
		}

		void client_connect(jgl::Connexion<T>* client)
		{
			std::cout << "Received connection from a new client [" << client->id() << "]" << std::endl;
			jgl::Message<T> msg;

			msg << _key;
			client->send(msg);
		};

		bool valid_client_connect(jgl::Connexion<T>* client, jgl::Message<T>& msg)
		{
			std::cout << "Validation connection from a client [" << client->id() << "]" << std::endl;
			int32_t key;
			int64_t presumed_result;
			int64_t real_result;

			msg >> key;
			msg >> presumed_result;


			std::cout << "Key received : " << key << " of size " << sizeof(key) << std::endl;
			real_result = compute_magic_number(key);
			std::cout << "Awsner : " << real_result << " of size " << sizeof(real_result) << std::endl;
			std::cout << "Magic number send : " << key << " -> result proposed : " << presumed_result << " vs espected " << real_result << std::endl;
			if (real_result == presumed_result)
			{
				client->accepted_by_server();
				if (_login_funct != nullptr)
					_login_funct(client, _login_param);
				msg.clear();
				msg << true;
				client->send(msg);
				return (true);
			}
			else
			{
				client->refused_by_server();
				msg.clear();
				msg << false;
				client->send(msg);
				return (false);
			}
		}

		void client_disconnect(jgl::Connexion<T>* client)
		{
			if (_logout_funct != nullptr)
				_logout_funct(client, _logout_param);
		};

	};
}

#endif
