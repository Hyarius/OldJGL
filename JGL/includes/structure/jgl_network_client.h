#ifndef JGL_NETWORK_CLIENT_H
#define JGL_NETWORK_CLIENT_H

#include "jgl_locked_queue.h"
#include "jgl_network_message.h"
#include "jgl_network_connexion.h"

namespace jgl
{
	template <typename T>
	class Client_interface
	{
	protected:
		asio::io_context _asio_context;
		std::thread _thread_context;
		jgl::Connexion<T>* _connexion;

		jgl::Locked_queue<jgl::Input_message<T>> _input;

	public:
		Client_interface()
		{
		}

		virtual ~Client_interface()
		{
			disconnect();
		}

		bool connect(const std::string& host, const uint16_t port)
		{
			try
			{
				asio::ip::tcp::resolver resolver(_asio_context);
				asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));

				_connexion = new Connexion<T>(jgl::Connexion_owner::client, _asio_context, asio::ip::tcp::socket(_asio_context), &_input);

				_connexion->connect_to_server(endpoints);

				_thread_context = std::thread([this]() { _asio_context.run(); });
			}
			catch (std::exception& e)
			{
				std::cerr << "Client Exception: " << e.what() << "\n";
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
				_thread_context.join();

			delete _connexion;
		}

		bool is_connected()
		{
			if (_connexion)
				return _connexion->is_connected();
			else
				return false;
		}

		virtual void update() = 0;

	public:
		void send(const jgl::Message<T>& msg)
		{
			if (is_connected())
				_connexion->send(msg);
		}

		jgl::Locked_queue<jgl::Input_message<T>>& input()
		{
			return (_input);
		}
	};
}

#endif