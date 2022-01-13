#pragma once
#include <iostream>
#include <zmq_addon.hpp>
#include <future>
#include <map>

class GameLogic;
enum MessType{
	Patch,
	Invitation,
	InvitationAccepted,
	InvitationRejected,
	Join, // set own id in logic
	Connect, // request to connect with another player 
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
		static std::vector<std::vector<zmq::message_t> > ReceivedMessages;
		static void SendByIp(std::string ip, MessType type, void* data, size_t size);
		//static std::map<std::string, zmq::socket_t> invitedPlayers; //nie mo¿emy zamkn¹æ socketu przed dostarczeniem wiadomoœci, wiêc musimy je gdzieœ trzymaæ
		//GameLogic logic;
	public:
		//WebModule(GameLogic& logic) :logic(logic) {}
		static void Init(std::string ip);
		static void Stop();
		static void Invite(std::string ip);
		static void AcceptInvitation(std::string ip);
		static void Join(std::string ip, int playerId);
		static void SendById(int playerId, MessType type, void* data, size_t size);
		static std::vector<zmq::message_t> ReceiveMessage();
		WebModule() {  }
		bool update() { return false; }


	};
}

