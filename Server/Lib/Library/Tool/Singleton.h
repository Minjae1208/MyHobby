#pragma once

#include <memory>
#include <mutex>

template <typename T>
class CSingleton
{
public:
	CSingleton()
	{

	}

	~CSingleton()
	{
		if (nullptr != _instance)
			_instance.reset();
	}

	static std::shared_ptr<T> Instance()
	{
		std::call_once(CSingleton<T>::_flag, []()
		{
			_instance = std::make_shared<T>();
		});

		return _instance;
	}

private:
	static std::shared_ptr<T> _instance;
	static std::once_flag _flag;
};

template<typename T> std::shared_ptr<T> CSingleton<T>::_instance = nullptr;
template<typename T> std::once_flag  CSingleton<T>::_flag;
