#pragma once
#include <afxsock.h>
class CClientSocket :
	public CSocket
{
public:
	CClientSocket();
	~CClientSocket();
	virtual void OnReceive(int nErrorCode);
};

