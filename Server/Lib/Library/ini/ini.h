#pragma once

class CDB_ini
{
	friend class CIni;
private:
	// @brief DB / ID / PW
	std::string db_name;
	std::string db_id;
	std::string db_pw;
	// @brief DB의 IP 및 Port 정보
	std::string db_ip;
	int16		db_port;
	// @brief DB 연결 개수
	int16		db_connect;

private:
	void		SetName(std::string name)	{ db_name = name; }
	void		SetID(std::string id)		{ db_id = id; }
	void		SetPW(std::string pw)		{ db_pw = pw; }
	void		SetIP(std::string ip)		{ db_ip = ip; }
	void		SetPort(int16 port)			{ db_port = port; }
	void		SetCon(int16 connect)		{ db_connect = connect; }

public:
	std::string GetName()	{ return db_name; }
	std::string GetID()		{ return db_id; }
	std::string GetPW()		{ return db_pw; }
	std::string GetIP()		{ return db_ip; }
	int16		GetPort()	{ return db_port; }
	int16		GetCon()	{ return db_connect; }
};

class CServer_ini
{
	friend class CIni;
private:
	int16 app_id = 0;
	uint8 io_type = 0;
	uint8 server_type = 0;

	uint16 max_peer = 0;
	uint16 max_conn = 0;

	std::unordered_map<uint8, CDB_ini> db_info;

private:
	void		SetID(int16 id) { app_id = id; }
	void		SetIO(uint8 io) { io_type = io; }
	void		SetServerType(uint8 type) { server_type = type; }

	void		SetMaxPeer(uint16 max) { max_peer = max; }
	void		SetMaxConn(uint16 max) { max_conn = max; }

	void		SetDB(uint8 type, CDB_ini db) { db_info.insert({ type , db }); }

public:
	int16		GetID()			{ return app_id; }
	uint8		GetIO()			{ return io_type; }
	uint8		GetServerType() { return server_type; }

	uint16		GetMaxPeer() { return max_peer; }
	uint16		GetMaxConn() { return max_conn; }

	CDB_ini* GetDB(uint8 key)
	{
		std::unordered_map<uint8, CDB_ini>::iterator iter;
		iter = db_info.find(key);
		if (iter == db_info.end())
			return nullptr;

		return &iter->second;
	}
};

// @brief 서버별 초기 데이터를 세팅해줄 클래스
class CIni : public CSingleton<CIni>
{
private:
	CServer_ini* app = nullptr;

public:
	CIni();
	~CIni();

public:
	void		Init();

	CServer_ini*	GetApp()	{ return app; }
	CDB_ini*	GetDB()	{ return app->GetDB(1); }
};