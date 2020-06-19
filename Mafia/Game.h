#pragma once


#include <vector>
#include <Network.hpp>
#include "ServerCommunication.h"
#include <functional>
#include <list>
#include <iostream>
#include <queue>
#include <string>

class VoteCounter;
class Vote;
bool b_CompareVoteCount(VoteCounter* vFirst, VoteCounter* vSecond);

enum class PlayerClass
{
	Villager,
	Mafia,
	MafiaBoss,
	Blackmailer,
	Police,
	Guard,
	Jury,
	Destroyer
};

enum class DayAction
{
	Vote,
	Destroyer,
	BeMuted
};

enum class NightAction
{
	Nothing,
	Kill,
	Silence,
	Inspect,
	DayVote,
	Guard
};

enum class ServerReceive
{
	Hello = 0,
	NickNameChange = 1,
	CreateGame = 2,
	JoinGame = 3,
	LeaveGame = 4,
	LeaveServer = 5,
	MakeDayMove = 6,
	MakeNightMove = 7,
	Disconnect = 8
};

enum class ServerSend
{
	Hello = 0
};





class Player
{
public:
	Player();
	Player(int iId, sf::TcpSocket* socket);
	Player(int iId, PlayerClass ePlayerClass);

	PlayerClass e_Check();
	int i_GetId();
	int i_Murder();
	int i_Silence();
	int i_Destroy();
	int i_DayVote();

	sf::TcpSocket* s_GetTcpSocket();
	std::queue<sf::Packet*> qPacket;

	Vote* vo_DayVote();
	//NightVoteAction* nva_NightVote();
	
	void v_DoDayAction();
	void v_DoNightAction();

	void v_Print();
	int i_GetDecision();	
	void v_ChangeNick(std::string* ptrNewNick);

private:
	
	int iId;
	PlayerClass ePlayerClass;
	bool bIsDead;
	sf::TcpSocket* tcpSocket;
	std::string* sNickname;
};

class Vote
{
public:
	Vote();
	Vote(int iVoter, int iTarget);

	int i_GetVoter();
	int i_GetTarget();

private:
	int iPlayerId;
	int iPlayerTarget;
};

class VoteCounter
{
public:
	VoteCounter();
	VoteCounter(int iId);

	int i_GetTarget();
	void v_AddVote();
	int i_GetVotes();


	void v_PrintResult();
private:
	int iTargetId;
	int iTargetVotes;
};

class NightVoteAction
{
public:
	NightVoteAction(NightAction naAction, int iId);
private:
	NightAction naCommand;

	int iTargetId;
};

class NightCollector
{
public:
	NightCollector();
	NightCollector(int iRnd);

	void v_AddNightVote(NightVoteAction* nvAction);
private:
	std::vector<NightVoteAction*> vNightVotes;
	int iRound;
};

class RoundVoteCollector
{
public:
	RoundVoteCollector();
	RoundVoteCollector(int iRnd);
	void v_AddVote(Vote* vToAdd);
	void v_CountVotes();
	//int i_CheckVotes();

	void v_PrintVotes();

private:
	std::vector<Vote*> vVotes;
	std::vector<VoteCounter*> vVoteCounter;
	int iRound;
};



class GameGroup
{
public:
	GameGroup();
	GameGroup(int iId,int iHost,Player* ptrPlayer);

	void v_PlayRound();
	void v_PlayerJoin(Player* ptrPlayer);
	void v_PrintGroup();
	int i_GetID();

	void v_PlayGame();

	void v_CollectDayVotes(RoundVoteCollector* ptrCollector);
	void v_CollectNightVotes(RoundVoteCollector* ptrCollector);

private:
	int iGroupId;
	int iNextPlayerId;
	int iRound;
	int iHostId;

	bool bGameFinished;
	bool bDayRoundDone;
	bool bNightRoundDone;

	std::vector<Player*> vPlayers;
	std::vector<RoundVoteCollector*> vVoteCollector;
	

};

class ServerLobby
{
public:
	ServerLobby();
	void v_start(int iAction);
	void v_DoCommand(sf::Packet* ptrPacket,Player* ptrPlayer);
	void v_MakeGroup(int iId, int iHost, Player* ptrPlayer);
	void v_JoinGroup(sf::Packet* ptrPacket, Player* ptrPlayer);

	void v_Disconnect(sf::Packet* ptrPacket, Player* ptrPlayer);

	std::list<Player*>* GetPlayerList();
	
	void v_PrintGroups();

private:

	int iNextRoomNum;
	std::list<Player*> lPlayers;
	std::list<GameGroup*> vGameGroup;
};

void v_RunServer(int iPort, ServerLobby* srv_lobby);
void v_Debuger(ServerLobby* ptrLobby);


