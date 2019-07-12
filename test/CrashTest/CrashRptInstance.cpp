#include "stdafx.h"
#include "CrashRptInstance.h"
#include "CrashRpt.h"

// 当前版本
#define  _VERSION_     "0.0.0.0"

CCrashRptInstance::CCrashRptInstance()
{
	InstallCrash();
}


CCrashRptInstance::~CCrashRptInstance()
{
	UnInstallCrash();
}

BOOL CCrashRptInstance::InstallCrash()
{
	TCHAR szEmailSubject[512];
	TCHAR szSenderPath[MAX_PATH];
	TCHAR szVersion[50];

	memset(szEmailSubject, 0, sizeof(szEmailSubject));
	memset(szSenderPath, 0, sizeof(szSenderPath));
	memset(szVersion, 0, sizeof(szVersion));
	_stprintf_s(szSenderPath, _T("%s"), GetCrashSenderPath());

	_stprintf_s(szVersion, _T("%f"), _VERSION_);

	CR_INSTALL_INFO info;
	memset(&info, 0, sizeof(CR_INSTALL_INFO));
	info.cb = sizeof(CR_INSTALL_INFO);
	info.pszAppName = _T("pbq");
	info.pszAppVersion = szVersion;
	info.pszUrl = _T("http://www.purang.com");
	info.dwFlags = (CR_INST_ALL_POSSIBLE_HANDLERS);
	info.pszPrivacyPolicyURL = _T("http://www.purang.com");
#ifdef _DEBUG
	info.pszEmailTo = _T("1298074546@qq.com");
#else
	// dump文件接收方邮箱账号
	info.pszEmailTo = _T("xiongwenkai@qq.com");
#endif
	// 协议优先级
	info.uPriorities[CR_SMTP] = 1;
	info.uPriorities[CR_SMAPI] = 2;
	info.uPriorities[CR_HTTP] = 3;

	// 发送邮件主题
	int nLen = _stprintf_s(szEmailSubject, _T("pbq %s Error Report"), szVersion);
	if (-1 != nLen && nLen < sizeof(szEmailSubject) / sizeof(TCHAR))
	{
		szEmailSubject[nLen] = _T('\0');
		info.pszEmailSubject = szEmailSubject;
	}

	// 邮件服务器代理地址
	info.pszSmtpProxy = _T("mail.purang.com");

	// dump文件发送者邮箱账号以及密码
	info.pszSmtpLogin = _T("purang_pbqsender@purang.com");
	info.pszSmtpPassword = _T("pbqsender@123");

	info.pszCrashSenderPath = szSenderPath;
	info.pszEmailText = NULL;
	info.pfnCrashCallback = NULL;    // 回调函数

	int nResult = crInstall(&info);
	if (EXIT_SUCCESS != nResult)
	{
		TCHAR szBuf[256];
		crGetLastErrorMsg(szBuf, 256);
		MessageBox(NULL, szBuf, _T("pbq Error"), MB_OK);
		return false;
	}

	crAddScreenshot2(CR_AS_MAIN_WINDOW | CR_AS_USE_JPEG_FORMAT, 95);

	return true;
}

void CCrashRptInstance::UnInstallCrash()
{
	crUninstall();
}

CString CCrashRptInstance::GetCrashSenderPath()
{
	//获取当前路径
	TCHAR szCurPath[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, szCurPath, MAX_PATH);
#ifdef _UNICODE
	WCHAR *pLastSlash = wcsrchr(szCurPath, _T('\\'));
	szCurPath[pLastSlash - szCurPath + 1] = _T('\0');
#else
	char *pLastSlash = strrchr(szCurPath, _T('\\'));
	szCurPath[pLastSlash - szCurPath + 1] = '\0';
#endif

	return CString(szCurPath);
}
