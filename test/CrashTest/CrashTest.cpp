// CrashTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

// ���Ա�����
class CBengkui
{
public:
	int GetInt(){ return 1; }
};


int _tmain(int argc, _TCHAR* argv[])
{
	CBengkui *p = new CBengkui();

	delete p;
	delete p;
	p->GetInt();
	return 0;
}



