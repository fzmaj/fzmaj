#include "ai.h"
#include "stdio.h"
#include "game.h"
#include "memory.h"

using namespace FZMAJ_NS;

AI::AI(FZMAJ *maj) : Pointers(maj)
{
  
}

AI::~AI() 
{
}

void AI::return_act(int act, int argout)
{
	game->deal_act(act,argout);
}
