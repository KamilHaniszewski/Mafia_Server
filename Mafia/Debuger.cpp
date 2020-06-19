#include "Game.h"
#include <Windows.h>

void v_Debuger(ServerLobby* ptrServer)
{
	while (true)
	{
		//std::cout << "Elo\n";
		ptrServer->v_PrintGroups();
		Sleep(5000);
	}
	
}