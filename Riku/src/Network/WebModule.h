#pragma once
#include <iostream>
#include <zmq_addon.hpp>
#include <future>
#include <map>

enum MessType {
	Patch, // type, patch?
	Invitation, // type, ip
	InvitationAccepted, //type, ip
	InvitationRejected,
	Join, // type, id, ip // set own id in logic
	JoinAccepted, // type, id, ip
	AddPlayer, // type, id, ip // request to connect with another player 
};

struct m_message {
private:
	std::vector<zmq::message_t> messParts;
public:
	m_message(std::vector<zmq::message_t> mess){
		messParts = std::vector<zmq::message_t>(std::move(mess));
	}

	zmq::message_t& operator[](int idx) {
		return messParts[idx];
	}
	bool empty() {
		return messParts.empty();
	}
	MessType type() {
		return *messParts[0].data<MessType>();
	}
	std::string dataString() {
		return *messParts[1].data<std::string>();
	}
};

namespace Network {
	class WebModule
	{
	private:
		static std::string myIp;
		static std::string port;
		static zmq::context_t context;
		static std::future<void> listenerThread;
		static std::map<int, zmq::socket_t> players;
		static std::map<int, std::string> playersIps;
		static std::vector<std::vector<zmq::message_t> > ReceivedMessages;		
		static std::map<std::string, zmq::socket_t> invitedPlayers;
	public:
		static void Init(std::string ip);
		static void Stop();
		static void CloseInviteSockets();
		static void Invite(std::string ip);
		static void AcceptInvitation(std::string ip);
		static void Join(std::string ip, int playerId);
		static void SendById(int playerId, MessType type, void* data = nullptr, size_t size = 0, void* data2 = nullptr, size_t size2 = 0);
		static void SendByIp(std::string ip, MessType type, void* data = nullptr, size_t size = 0, void* data2 = nullptr, size_t size2 = 0);
		static std::vector<zmq::message_t> ReceiveMessage();
		static m_message ReceiveMessageStruct();
	};
}

