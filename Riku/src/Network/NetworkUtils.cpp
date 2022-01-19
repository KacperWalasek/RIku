#include "NetworkUtils.h"
#ifdef _WIN32
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
#else
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>

bool checkFlags(unsigned int flags) {
	if(!(flags&IFF_UP) || !(flags&IFF_BROADCAST) || !(flags&IFF_RUNNING) || (flags&IFF_LOOPBACK))
		return false;
	return true;
}

std::string NetworkUtils::getIpAddress()
{
	ifaddrs* ips;
	if(::getifaddrs(&ips)!= 0)
		return "";
	ifaddrs* ips_tmp = ips;
	std::string local_ip;
	//const std::string interface = "wlo1";
	while (ips_tmp) {
		/*if (interface == ips_tmp->ifa_name)*/
		if(checkFlags(ips_tmp->ifa_flags)){
			if (ips_tmp->ifa_addr->sa_family == AF_INET) {
				local_ip = inet_ntoa((reinterpret_cast<sockaddr_in*>(ips_tmp->ifa_addr))
							->sin_addr);
				break;
			}
		}
		ips_tmp = ips_tmp->ifa_next;
	}
	freeifaddrs(ips);
	return local_ip;
}
#endif
