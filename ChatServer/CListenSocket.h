#pragma once
#include <afxsock.h>
class CListenSocket :
	public CSocket
{
public:
	CListenSocket();
	~CListenSocket();
	virtual void OnAccept(int nErrorCode);
};

