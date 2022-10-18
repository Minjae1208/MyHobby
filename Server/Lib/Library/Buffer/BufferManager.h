#pragma once

class CBuffer;

class CBufferManager : public CSingleton<CBufferManager>
{
private:
	using iter = std::unordered_map<size_t, CBuffer*>::iterator;
	std::unordered_map<size_t, CBuffer*> buffers;

public:
	CBufferManager();
	~CBufferManager();

	void MakeBuffer(size_t size, int32 count);
	char* Get(size_t size);
	bool Put(char* pData, size_t size);
};