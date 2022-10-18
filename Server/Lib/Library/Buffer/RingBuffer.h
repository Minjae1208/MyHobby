#pragma once

// @brief Ring Buffer Class
class CRingBuffer
{
private:
	// @brief Origin Buffer
	char* buffer;
	// @brief Buffer's size
	size_t size;
	// @brief Buffer's Read Position
	int32 read_pos = 0;
	// @brief Buffer's Write Position
	int32 write_pos = 0;

public:
	CRingBuffer(char* pBuffer, size_t size);
	~CRingBuffer();

	// @brief 
	char* GetBuffer();
	// @brief 
	bool ReadData(char* pData, size_t len);
	// @brief 
	bool WriteData(char* pData, size_t len);
	// @brief 
	int32 GetLength();

};