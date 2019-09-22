#pragma once

namespace age
{
	template<typename T>
	class Singleton
	{
	public:
		template<typename... Args>
		static T &get(Args... args)
		{
			static T* t;

			if (t == nullptr)
			{
				t = new T(args...);
			}

			return *t;
		}
	};
}