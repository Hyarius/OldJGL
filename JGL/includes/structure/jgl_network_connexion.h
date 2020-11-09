#ifndef JGL_NETWORK_CONNEXION_H
#define JGL_NETWORK_CONNEXION_H

#include "jgl_includes.h"
#include "jgl_network_message.h"

namespace jgl
{

	enum class Connexion_owner
	{
		error = -1,
		server,
		client
	};

	template<typename T>
	class Connexion
	{
	protected:
		asio::ip::tcp::socket _socket;
		asio::io_context& _context;
		jgl::Locked_queue<Message<T>> _output;
		jgl::Locked_queue<jgl::Input_message<T>>* _input;
		jgl::Message<T> _tmp_message;
		Connexion_owner _owner = Connexion_owner::error;
		uint32_t _id = 0;

	public:
		Connexion(Connexion_owner parent, asio::io_context& p_context, asio::ip::tcp::socket p_socket, jgl::Locked_queue<jgl::Input_message<T>>* p_input)
			: _context(p_context), _socket(std::move(p_socket)), _input(p_input), _tmp_message({})
		{
			_owner = parent;
		}

		virtual ~Connexion()
		{}

		jgl::Locked_queue<jgl::Input_message<T>>& input()
		{
			return (_input);
		}

		uint32_t id() const
		{
			return (_id);
		}

		void connect_to_client(uint32_t uid = 0)
		{
			if (_owner == Connexion_owner::server)
			{
				if (_socket.is_open())
				{
					_id = uid;
					read_header();
				}
			}
		}

		void connect_to_server(const asio::ip::tcp::resolver::results_type& endpoints)
		{
			if (_owner == Connexion_owner::client)
			{
				asio::async_connect(_socket, endpoints,
					[this](std::error_code ec, asio::ip::tcp::endpoint endpoint)
					{
						if (!ec)
							read_header();
					});
			}
		}

		void disconnect()
		{
			if (is_connected())
				asio::post(_context, [this]() { _socket.close(); });
		}

		bool is_connected() const
		{
			return (_socket.is_open());
		}

		void start()
		{

		}

		void send(const jgl::Message<T>& msg)
		{
			asio::post(_context,
				[this, msg]()
				{
					bool state = _output.empty();
					_output.push_back(msg);
					if (state == true)
						write_header();
				});
		}

	private:
		void write_header()
		{
			asio::async_write(_socket, asio::buffer(&_output.front().header, sizeof(Message_header<T>)),
				[this](std::error_code ec, std::size_t length)
				{
					if (!ec)
					{
						if (_output.front().content.size() > 0)
							write_content();
						else
						{
							_output.pop_front();

							if (!_output.empty())
								write_header();
						}
					}
					else
					{
						std::cout << "[" << _id << "] Write Header Fail.\n";
						_socket.close();
					}
				});
		}

		void write_content()
		{
			asio::async_write(_socket, asio::buffer(_output.front().content.data(), _output.front().content.size()),
				[this](std::error_code ec, std::size_t length)
				{
					if (!ec)
					{
						_output.pop_front();

						if (!_output.empty())
							write_header();
					}
					else
					{
						std::cout << "[" << _id << "] Write Body Fail.\n";
						_socket.close();
					}
				});
		}

		void read_header()
		{
			asio::async_read(_socket, asio::buffer(&_tmp_message.header, sizeof(Message_header<T>)),
				[this](std::error_code ec, std::size_t length)
				{
					if (!ec)
					{
						if (_tmp_message.header.size > 0)
						{
							_tmp_message.content.resize(_tmp_message.header.size);
							read_content();
						}
						else
						{
							add_message_to_queue();
						}
					}
					else
					{
						std::cout << "[" << _id << "] Read Header Fail.\n";
						_socket.close();
					}
				});
		}

		void read_content()
		{
			asio::async_read(_socket, asio::buffer(_tmp_message.content.data(), _tmp_message.content.size()),
				[this](std::error_code ec, std::size_t length)
				{
					if (!ec)
					{
						add_message_to_queue();
					}
					else
					{
						std::cout << "[" << _id << "] Read Body Fail.\n";
						_socket.close();
					}
				});
		}

		void add_message_to_queue()
		{
			if (_owner == Connexion_owner::server)
				_input->push_back({ this, _tmp_message });
			else
				_input->push_back({ nullptr, _tmp_message });
			read_header();
		}
	};

}

#endif