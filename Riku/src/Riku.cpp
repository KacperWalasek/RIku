#include <ctime>
#include "GameLogic/GameLogic.h"
#include "Frontend/Frontend.h"
#include "Network/WebModule.h"
//https://learnopengl.com/Getting-started (CC-BY-NC) was used to help writing the code

int main() {
	srand(time(0));
	GameLogic logic("../assets", "../mini_assets");
	front::Config config;
	front::Frontend frontend(logic, config);
	Network::WebModule::Init();
	//webmodule.Invite();
	bool inGame = false;
	bool isHost = true;
	std::string enemyIp = "192.168.0.14";
	std::vector<std::string> invidedIps;
	if(isHost)
		Network::WebModule::Invite(enemyIp);
	while (!inGame)
	{
		m_message message = Network::WebModule::ReceiveMessageStruct();
		switch (message.type())
		{
		case MessType::Invitation:
			if (!isHost && !message.empty())
				Network::WebModule::AcceptInvitation(message.dataString());
			break;
		case MessType::InvitationAccepted:
			if (isHost)
				Network::WebModule::Join(message.dataString(), 1);
			break;
		default:
			break;
		}
		
	}
	bool exitProgram = false;
	while (!exitProgram)
	{
		logic.update();
		exitProgram = frontend.update();
	}
	return 0;
}
