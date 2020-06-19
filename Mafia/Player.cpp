#include "Game.h"
#include <iostream>


Player::Player()
{
	iId = -1;
	ePlayerClass = PlayerClass::Villager;
	bIsDead = false;
	sNickname = new std::string;
	*sNickname = "";

}

Player::Player(int iNewId, sf::TcpSocket* socket)
{
	iId = iNewId;
	ePlayerClass = PlayerClass::Villager;
	bIsDead = false;
	tcpSocket = socket;
	sNickname = new std::string;
	*sNickname = "";

}

Player::Player(int iNewId, PlayerClass eNewPlayerClass)
{
	iId = iNewId;
	ePlayerClass = eNewPlayerClass;
	bIsDead = false;
	sNickname = new std::string;
	*sNickname = "";
}

PlayerClass Player::e_Check()
{
	return ePlayerClass;
}

int Player::i_GetId()
{
	return iId;
}

int Player::i_Murder()
{
	std::cout << "Kogo chcesz zabic?\n";
	return i_GetDecision();
}

int Player::i_Silence()
{
	std::cout << "Kogo chcesz uciszyc?\n";
	return i_GetDecision();
}

int Player::i_Destroy()
{
	std::cout << "Kogo chcesz likwidowac?\n";
	return i_GetDecision();
}

int Player::i_DayVote()
{
	std::cout << "Na kogo chcesz zaglosowac?\n";
	return i_GetDecision();
}

sf::TcpSocket* Player::s_GetTcpSocket()
{
	return tcpSocket;
}

Vote* Player::vo_DayVote()
{
	Vote* vo_res = new Vote(iId, i_DayVote());
	return vo_res;
}

void Player::v_DoDayAction()
{
	int k;
	switch (ePlayerClass)
	{
	case PlayerClass::Destroyer:
		break;

	default:
		k = i_DayVote();
		break;

	}
}

void Player::v_DoNightAction()
{
	int k;
	switch (ePlayerClass)
	{
	case PlayerClass::MafiaBoss:
		k = i_Murder();
		break;
	case PlayerClass::Blackmailer:
		break;
	case PlayerClass::Guard:
		break;
	case PlayerClass::Jury:
		break;
	case PlayerClass::Police:
		break;
	default:
		break;
	}
}

void Player::v_Print()
{
	if(bIsDead)
		printf("Id: %d, Klasa: %d, Dead\n",iId,int(ePlayerClass));
	else
		printf("Id: %d, Klasa: %d, Alive\n", iId, int(ePlayerClass));
}

int Player::i_GetDecision()
{
	int iResult=0;
	std::cin >> iResult;
	return iResult;
}

void Player::v_ChangeNick(std::string* ptrNewNick)
{
	*sNickname = *ptrNewNick;
}