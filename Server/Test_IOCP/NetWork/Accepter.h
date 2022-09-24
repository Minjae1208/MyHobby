#pragma once

// @biref  Accepter 클래스
class CAccepter
{
private:
	std::thread worker;
public:
	CAccepter();
	~CAccepter();

public:
	// @brief Accetper 실행 함수
	void StartAccepter();
	// @brief Accepter 함수를 스레드로 돌리기 위한 함수
	static void WorkerRun(CAccepter* pThis);
	// @brief Listen Socket를 통해 들어오는 Accept를 처리
	void AccepterRun();

};