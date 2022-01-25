#pragma once
#include <string>
#ifdef _WIN32
#include <windows.h>
#include <commctrl.h>
#include <winsock.h>
#else
#endif
#include <cstdlib>
#include <cstring>
#pragma comment(lib,"WS2_32")

class NetworkUtils 
{
#ifdef _WIN32
	static DWORD GetLocalIpAddress();
	static std::string ConvertIP(DWORD ip);
#endif
	
public:
	static std::string getIpAddress();
	
};