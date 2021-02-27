#ifndef JGL_NETWORK_MESSAGE_H
#define JGL_NETWORK_MESSAGE_H

#include "jgl_includes.h"

namespace jgl
{
	template <typename T>
	struct Message_header
	{
		T id{};
		uint32_t size = 0;
		Message_header()
		{

		}
		Message_header(T type)
		{
			id = type;
			size = 0;
		}
	};

	template <typename T>
	struct Message
	{
		Message_header<T> header{};
		std::vector<uint8_t> content;

		T type() const
		{
			return (header.id);
		}

		size_t size() const
		{
			return content.size();
		}

		bool empty()
		{
			if (header.size == 0)
				return (true);
			return (false);
		}

		Message(T type)
		{
			header = Message_header(type);
			content.clear();
		}

		void clear()
		{
			header.size = 0;
			content.clear();
		}

		friend std::ostream& operator << (std::ostream& os, const Message<T>& msg)
		{
			os << "ID:" << int(msg.header.id) << " Size:" << msg.header.size;
			return os;
		}

		jgl::String get_string()
		{
			jgl::String text;
			size_t size;
			size_t i;

			*this >> size;
			std::cout << "Size read : " << size << std::endl;
			while (empty() == false && i < size)
			{
				jgl::Glyph c;
				*this >> c;
				std::cout << "Glyph read : " << c << std::endl;
				text.push_front(c);
				i++;
			}

			return (text);
		}

		void add_string(jgl::String text)
		{
			for (size_t i = 0; i < text.size(); i++)
				*this << text[i];
			*this << text.size();
		}

		template<typename DataType>
		friend Message<T>& operator << (Message<T>& msg, const DataType& data)
		{
			static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pushed into vector");

			size_t i = msg.content.size();

			msg.content.resize(msg.content.size() + sizeof(DataType));

			std::memcpy(msg.content.data() + i, &data, sizeof(DataType));

			msg.header.size = msg.size();

			return msg;
		}

		template<typename DataType>
		friend Message<T>& operator >> (Message<T>& msg, DataType& data)
		{
			static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pulled from vector");

			size_t i = msg.content.size() - sizeof(DataType);

			std::memcpy(&data, msg.content.data() + i, sizeof(DataType));

			msg.content.resize(i);

			msg.header.size = msg.size();

			return msg;
		}
	};

	template <typename T>
	class Connexion;

	template <typename T>
	struct Input_message
	{
		Connexion<T>* remote = nullptr;
		Message<T> msg;

		T type()
		{
			return (msg.type());
		}

		// Again, a friendly string maker
		friend std::ostream& operator<<(std::ostream& os, const Input_message<T>& msg)
		{
			os << msg.msg;
			return os;
		}
	};
}

#endif
