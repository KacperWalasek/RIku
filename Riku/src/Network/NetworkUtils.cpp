#include "NetworkUtils.h"

DWORD NetworkUtils::GetLocalIpAddress()
{
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(wVersionRequested, &wsaData) != 0)
		return 0;
	char local[255] = { 0 };
	gethostname(local, sizeof(local));
	hostent* ph = gethostbyname(local);
	if (ph == NULL)
		return 0;
	in_addr addr;
	memcpy(&addr, ph->h_addr_list[0], sizeof(in_addr));
	DWORD dwIP = MAKEIPADDRESS(addr.S_un.S_un_b.s_b1, addr.S_un.S_un_b.s_b2, addr.S_un.S_un_b.s_b3, addr.S_un.S_un_b.s_b4);
	return dwIP;
}

std::string NetworkUtils::ConvertIP(DWORD ip)
{
	unsigned char a, b, c, d;
	d = ip & 0xFF;
	c = (ip >> 8) & 0xFF;
	b = (ip >> 16) & 0xFF;
	a = (ip >> 24) & 0xFF;

	std::string conv = std::to_string(a) + "." + std::to_string(b) + "." + std::to_string(c) + "." + std::to_string(d);
	return conv;
}

std::string NetworkUtils::getIpAddress()
{
	DWORD ip = GetLocalIpAddress();
	return ConvertIP(ip);
}
