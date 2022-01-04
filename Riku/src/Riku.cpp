#include <ctime>
#include "GameLogic/GameLogic.h"
#include "Frontend/Frontend.h"

//https://learnopengl.com/Getting-started (CC-BY-NC) was used to help writing the code

int main() {
	srand(time(0));
	GameLogic logic("../assets");
	front::Config config;
	front::Frontend frontend(logic, config);

	bool exitProgram = false;
	while (!exitProgram)
	{
		logic.update();
		exitProgram = frontend.update();
	}
	return 0;
}
