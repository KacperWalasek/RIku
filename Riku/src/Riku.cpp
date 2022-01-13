#include <ctime>
#include "GameLogic/GameLogic.h"
#include "Frontend/Frontend.h"
#include "Network/WebModule.h"

//https://learnopengl.com/Getting-started (CC-BY-NC) was used to help writing the code

int main() {
	Network::WebModule::Init("192.168.0.80");
	Network::WebModule::Invite("192.168.0.81");
	//Network::WebModule::Send("Heloli");
	//Network::WebModule::Send(MessType::Patch, "Siema Eniu");
	//Network::WebModule::SendPatch();
	int a;
	std::cin >> a;
	auto m =Network::WebModule::ReceiveMessage();
	//std::cout << m[0].to_string();
	//for (int i = 0; i < Network::WebModule::ReceivedMessages.size(); i++)
	//{
	//	for (int j = 0; j < Network::WebModule::ReceivedMessages[i].size(); j++)
	//		std::cout << Network::WebModule::ReceivedMessages[i][j].to_string() << "  ";
	//	std::cout << std::endl;
	//}
	std::cin >> a;
	Network::WebModule::Stop();
	return 0;
	srand(time(0));
	GameLogic logic;
	front::Config config;
	front::Frontend frontend(logic, config);

	bool exitProgram = false;
	while (!exitProgram)
	{
		exitProgram = frontend.update();
	}
	return 0;
}
