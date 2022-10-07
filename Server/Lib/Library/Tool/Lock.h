#pragma once


class CLock
{
	std::mutex& lock;

public:
	CLock(std::mutex& lock) : lock(lock)
	{
		lock.lock(); 
	};
	~CLock()
	{
		lock.unlock();
	};
};