#pragma once

// @biref  Accepter Ŭ����
class CAccepter
{
private:
	std::thread worker;
public:
	CAccepter();
	~CAccepter();

public:
	// @brief Accetper ���� �Լ�
	void StartAccepter();
	// @brief Accepter �Լ��� ������� ������ ���� �Լ�
	static void WorkerRun(CAccepter* pThis);
	// @brief Listen Socket�� ���� ������ Accept�� ó��
	void AccepterRun();

};