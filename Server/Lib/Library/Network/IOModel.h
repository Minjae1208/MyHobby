#pragma once

class CIOUnit;
class CRIOManager;
class CContext;
class CRIO_Context;

// @brief ����ϴ� IO Model�� ���� IO ���� Ŭ����
class CIOModel
{
protected:
	CIOUnit* unit = nullptr;
	CContext* accpet = nullptr;
	CContext* proc = nullptr;

public:
	CIOModel(CIOUnit* pUnit);
	virtual ~CIOModel() {};

public:
	// @brief **** ���� �߰��ϱ�
	virtual bool Create() = 0;
	// @brief **** ���� �߰��ϱ�
	//virtual bool Accept() = 0;
	// @brief **** ���� �߰��ϱ�
	virtual bool Recv()	  = 0;
	// @brief **** ���� �߰��ϱ�
	virtual bool Send()	  = 0;

	bool Proc();
};

// @brief **** ���� �߰��ϱ�
class CRIOModel : public CIOModel
{
private:
	CRIOManager* manager = nullptr;

	RIO_RQ rq;
	RIO_BUFFERID recv_buffid;
	RIO_BUFFERID send_buffid;

	CRIO_Context* recv_context = nullptr;
	CRIO_Context* send_context = nullptr;

public:
	CRIOModel(CIOUnit* pUnit, CRIOManager* pManager);
	virtual ~CRIOModel();

public:
	virtual bool Create();
	virtual bool Recv();
	virtual bool Send();
};

// @brief **** ���� �߰��ϱ�
class CIOCPModel : public CIOModel
{
private:

public:
	CIOCPModel(CIOUnit* pUnit);
	virtual ~CIOCPModel();

public:
	virtual bool Create();
	virtual bool Recv();
	virtual bool Send();

};

// @brief **** ���� �߰��ϱ�
class CIOCPModel_Ex : public CIOModel
{
private:

public:
	CIOCPModel_Ex(CIOUnit* pUnit);
	virtual ~CIOCPModel_Ex();

public:
	virtual bool Create() { return false; };
	virtual bool Recv();
	virtual bool Send();
};