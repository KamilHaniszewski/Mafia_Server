#include "Game.h"



GameGroup::GameGroup()
{
	iGroupId = 0;
	iNextPlayerId = 1;
	iRound = 0;
	iHostId = -1;

	bDayRoundDone = false;
	bNightRoundDone = false;
	bGameFinished = false;
}

GameGroup::GameGroup(int iNewId,int iHost,Player* ptrPlayer)
{
	iGroupId = iNewId;
	iNextPlayerId = 0;
	iRound = 0;
	iHostId = iHost;
	vPlayers.push_back(ptrPlayer);

	bDayRoundDone = false;
	bNightRoundDone = false;
	bGameFinished = false;
}

void GameGroup::v_PlayRound()
{
	RoundVoteCollector* vVotes = new RoundVoteCollector(iRound);

	for (std::vector<Player*>::iterator it = vPlayers.begin(); it != vPlayers.end(); it++)
	{
		Player *pPlayer = *it;
		vVotes->v_AddVote(pPlayer->vo_DayVote());
		//pPlayer->v_DoDayAction();
	}
	vVotes->v_CountVotes();
	vVotes->v_PrintVotes();

	for (std::vector<Player*>::iterator it = vPlayers.begin(); it != vPlayers.end(); it++)
	{
		Player* pPlayer = *it;
		pPlayer->v_DoNightAction();
	}
}

void GameGroup::v_PlayerJoin(Player* ptrPlayer)
{
	
	ptrPlayer->v_Print();
	vPlayers.push_back(ptrPlayer);
}

void GameGroup::v_PrintGroup()
{
	printf("----Lobby nr:  %3d-----\n",iGroupId);
	for (int i = 0; i < vPlayers.size(); i++)
	{
		vPlayers[i]->v_Print();
	}
	printf("----------------------\n");
}

int GameGroup::i_GetID()
{
	return iGroupId;
}

void v_PlayGame()
{
}

