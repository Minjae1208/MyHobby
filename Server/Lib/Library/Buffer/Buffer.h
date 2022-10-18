#pragma once

// @brief Fixed Buffer Pool
class CBuffer
{
private:
	// @brief 
	std::vector<char*> pool;
	// @brief 
	std::list<char*> origin_ptr;

	// @brief 
	std::mutex index_lock;

	// @brief 
	int index = 0;

	int total_count = 0;

	size_t size = 0;
	int count = 0;

public:
	// @brief ±âº» 50°³
	CBuffer(size_t size, int count = 50);
	virtual ~CBuffer();

public:
	char* Pop();
	void Push(char* pData);

private:
	void _Alloc(int count);
};