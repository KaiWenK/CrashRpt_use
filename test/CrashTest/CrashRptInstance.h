#pragma once
#include <atlstr.h>

#ifdef _DEBUG
#pragma comment(lib, "CrashRptd.lib")
#else
#pragma comment(lib, "CrashRpt.lib")
#endif // _DEBUG

class CCrashRptInstance
{
public:
	CCrashRptInstance();
	virtual ~CCrashRptInstance();

protected:
	BOOL    InstallCrash();
	void    UnInstallCrash();
public:
	CString GetCrashSenderPath();




};

