#include "Game.h"

RoundVoteCollector::RoundVoteCollector()
{
	iRound = 0;
}

RoundVoteCollector::RoundVoteCollector(int iRnd)
{
	iRound = iRnd;
}

void RoundVoteCollector::v_AddVote(Vote* vToAdd)
{
	vVotes.push_back(vToAdd);
}

void RoundVoteCollector::v_CountVotes()
{
	int iRes = 0;
	for (std::vector<Vote*>::iterator it = vVotes.begin(); it != vVotes.end(); it++)
	{
		Vote* vVote = *it;
		vVoteCounter.push_back(new VoteCounter(vVote->i_GetVoter()));

	}
	for (std::vector<Vote*>::iterator it = vVotes.begin(); it != vVotes.end(); it++)
	{
		Vote* vVote = *it;

		for (std::vector<VoteCounter*>::iterator itt = vVoteCounter.begin(); itt != vVoteCounter.end(); itt++)
		{
			VoteCounter* vCounter = *itt;
			if (vVote->i_GetTarget() == vCounter->i_GetTarget())
			{
				vCounter->v_AddVote();
			}

		}
	}
}

void RoundVoteCollector::v_PrintVotes()
{
	for (std::vector<VoteCounter*>::iterator it = vVoteCounter.begin(); it != vVoteCounter.end(); it++)
	{
		VoteCounter* vVote = *it;
		vVote->v_PrintResult();
	}
}

int i_CheckVotes()
{
	return 0;
}

