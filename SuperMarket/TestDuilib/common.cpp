#include "common.h"

string UnicodeToANSI(const CDuiString& str)
{
	char* pElementText;
	int TextLen = WideCharToMultiByte(CP_ACP, 0, str.GetData(), -1, NULL, 0, NULL, NULL);
	pElementText = new char[TextLen + 1];
	memset((void*)pElementText, 0, sizeof(char)* (TextLen + 1));
	WideCharToMultiByte(CP_ACP, 0, str.GetData(), -1, pElementText, TextLen, NULL, NULL);
	string strText;
	strText = pElementText;
	delete[] pElementText;
	return strText;
}

CDuiString ANSIToUnicode(const string& str)
{
	size_t len = 0;
	len = str.length();
	int unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	
	wchar_t *pUnicode = new  wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1)*sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, (LPWSTR)pUnicode, unicodeLen);
	CDuiString rt(pUnicode);
	delete pUnicode;
	return rt;
}