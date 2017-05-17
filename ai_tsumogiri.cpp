#include "ai.h"
#include "ai_tsumogiri.h"

using namespace FZMAJ_NS;

AI_Tsumogiri::AI_Tsumogiri(FZMAJ *maj) : AI(maj)
{

}

AI_Tsumogiri::~AI_Tsumogiri() {}

void AI_Tsumogiri::request(Bakyou *bak)
{
	return_act(bak->default_act,bak->default_argout);
}
