#ifndef JGL_LOCKED_QUEUE_H
#define JGL_LOCKED_QUEUE_H

namespace jgl
{
	template<typename T>
	class Locked_queue
	{
	protected:
		std::mutex muxQueue;
		std::deque<T> _content;
		std::condition_variable cvBlocking;
		std::mutex muxBlocking;

	public:
		Locked_queue() = default;
		Locked_queue(const Locked_queue<T>&) = delete;
		virtual ~Locked_queue() { clear(); }

		const T& front()
		{
			std::scoped_lock lock(muxQueue);
			return _content.front();
		}

		const T& back()
		{
			std::scoped_lock lock(muxQueue);
			return _content.back();
		}

		T pop_front()
		{
			std::scoped_lock lock(muxQueue);
			auto t = std::move(_content.front());
			_content.pop_front();
			return t;
		}

		T pop_back()
		{
			std::scoped_lock lock(muxQueue);
			auto t = std::move(_content.back());
			_content.pop_back();
			return t;
		}

		void push_back(const T& item)
		{
			std::scoped_lock lock(muxQueue);
			_content.emplace_back(std::move(item));

			std::unique_lock<std::mutex> ul(muxBlocking);
			cvBlocking.notify_one();
		}

		void push_front(const T& item)
		{
			std::scoped_lock lock(muxQueue);
			_content.emplace_front(std::move(item));

			std::unique_lock<std::mutex> ul(muxBlocking);
			cvBlocking.notify_one();
		}

		bool empty()
		{
			std::scoped_lock lock(muxQueue);
			return _content.empty();
		}

		size_t count()
		{
			std::scoped_lock lock(muxQueue);
			return _content.size();
		}

		void clear()
		{
			std::scoped_lock lock(muxQueue);
			_content.clear();
		}

		void wait()
		{
			while (empty())
			{
				std::unique_lock<std::mutex> ul(muxBlocking);
				cvBlocking.wait(ul);
			}
		}
	};

}

#endif