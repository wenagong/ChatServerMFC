#pragma once
#include <afxsock.h>
class CListenSocket :
	public CSocket
{
public:
	CListenSocket();
	~CListenSocket();
};

