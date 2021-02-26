#ifndef JGL_NETWORK_SERVER_H
#define JGL_NETWORK_SERVER_H

#include "jgl_locked_queue.h"
#include "jgl_network_message.h"
#include "jgl_network_connexion.h"

namespace jgl
{
	template<typename T>
	class Server_interface
	{
	protected:
		jgl::Locked_queue<jgl::Input_message<T>> _input;

		std::deque<jgl::Connexion<T>*> _active_connexion;

		asio::io_context _asio_context;
		std::thread _thread_context;

		asio::ip::tcp::acceptor _acceptor;

		uint32_t _id_count = 10000;

	public:
		Server_interface(uint16_t port)
			: _acceptor(_asio_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
		{

		}

		virtual ~Server_interface()
		{
			stop();
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

						if (client_connect(newconn))
						{
							_active_connexion.push_back(std::move(newconn));

							_active_connexion.back()->connect_to_client(_id_count++);

							std::cout << "[" << _active_connexion.back()->id() << "] Connexion Approved\n";
						}
						else
						{
							std::cout << "[-----] Connexion Denied\n";
						}
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
				_active_connexion.erase(std::remove(_active_connexion.begin(), _active_connexion.end(), nullptr), _active_connexion.end());
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

	protected:
		virtual bool client_connect(jgl::Connexion<T>* client) = 0;

		virtual void client_disconnect(jgl::Connexion<T>* client) = 0;

		virtual void on_message_reception(jgl::Connexion<T>* client, jgl::Message<T>& msg) = 0;
	};
}

#endif