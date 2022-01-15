#pragma once
#include <string>
#include <windows.h>
#include <cstdlib>
#include <commctrl.h>
#include <winsock.h>
#include <cstring>
#pragma comment(lib,"WS2_32")

class NetworkUtils 
{
	static DWORD GetLocalIpAddress();
	static std::string ConvertIP(DWORD ip);
	
public:
	static std::string getIpAddress();
	
};