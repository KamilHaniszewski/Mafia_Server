#include "Game.h"

Vote::Vote()
{
	iPlayerId = -1;
	iPlayerTarget = -1;
}

Vote::Vote(int iVoter, int iTarget)
{
	iPlayerId = iVoter;
	iPlayerTarget = iTarget;
}

int Vote::i_GetVoter()
{
	return iPlayerId;
}

int Vote::i_GetTarget()
{
	return iPlayerTarget;
}

VoteCounter::VoteCounter()
{
	iTargetId = -1;
	iTargetVotes = 0;
}

VoteCounter::VoteCounter(int iId)
{
	iTargetId = iId;
	iTargetVotes = 0;
}

int VoteCounter::i_GetTarget()
{
	return iTargetId;
}

void VoteCounter::v_AddVote()
{
	iTargetVotes++;
}

int VoteCounter::i_GetVotes()
{
	return iTargetVotes;
}

void VoteCounter::v_PrintResult()
{
	printf("Gracz o id %d, dostal %d glosow.\n", iTargetId, iTargetVotes);
}

bool b_CompareVoteCount(VoteCounter* vFirst, VoteCounter* vSecond)
{
	return vFirst->i_GetVotes() < vSecond->i_GetVotes();
}

NightCollector::NightCollector()
{
	iRound = 0;
}

NightCollector::NightCollector(int iRnd)
{
	iRound = iRnd;
}

void NightCollector::v_AddNightVote(NightVoteAction* nvAction)
{
	vNightVotes.push_back(nvAction);
}

NightVoteAction::NightVoteAction(NightAction naAction, int iId)
{
	naCommand = naAction;
	iTargetId = iId;
}

