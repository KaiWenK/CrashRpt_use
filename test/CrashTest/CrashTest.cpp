// CrashTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

// 测试崩溃类
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



