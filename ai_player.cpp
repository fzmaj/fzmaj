#include "ai.h"
#include "ai_player.h"
#include "tools.h"
#include <iostream>
#include "stdio.h"
#include "stdlib.h"

using namespace FZMAJ_NS;
using namespace std;

AI_Player::AI_Player(FZMAJ *maj) : AI(maj)
{

}

AI_Player::~AI_Player() {}

void AI_Player::request(Bakyou *b)
{
    int i,j,p;
    int n_act, s_act;
    int argout;
    char str[128];
    const char chaname[4][24]={
    {" right-hand "},
    {" opposite   "},
    {" left-hand  "},
    {" myself     "}
    };
    printf("*************************\n");
    printf("Player recieved bakyou.\n");
    printf("*************************\n\n");

    // print bakyou

    printf("Game: %s %d kyoku %d honba %d residue\n",CHA_NAME[b->bafuu],b->kyoku+1,b->honba,b->residue);
    printf("Dora hyouji: ");
    for(i=0;i<b->dora_hyouji.size();++i)
        printf("%s ",b->dora_hyouji[i].pai_str.c_str());
    printf("   Dora: ");
    for(i=0;i<b->dora.size();++i)
        printf("%s ",tools->c2str(b->dora[i],0).c_str());
    printf("\n");

    // print river & naki

    for(j=0;j<4;++j){

    p=(j+1)%4;
    printf ("%s: %d\n",chaname[j],b->score[p]);
    printf ("            river:");
    for(i=0;i<b->river[p].size();++i)
        printf("%s(%d) ",b->river[p][i].river_pai.pai_str.c_str(),b->river[p][i].river_stat);
    printf("\n");
    printf ("            naki : ");
    for(i=0;i<b->naki[p].size();++i)
        if(b->naki[p][i].naki_type<2)
            printf("%s%s%s(%d) ",b->naki[p][i].naki_pai[0].pai_str.c_str(),
                                 b->naki[p][i].naki_pai[1].pai_str.c_str(),
                                 b->naki[p][i].naki_pai[2].pai_str.c_str(),
                                 b->naki[p][i].naki_type);
        else
            printf("%s%s%s(%d) ",b->naki[p][i].naki_pai[0].pai_str.c_str(),
                                 b->naki[p][i].naki_pai[1].pai_str.c_str(),
                                 b->naki[p][i].naki_pai[2].pai_str.c_str(),
                                 b->naki[p][i].naki_pai[3].pai_str.c_str(),
                                 b->naki[p][i].naki_type);
    printf("\n");
    }

    // print tehai

    printf("tehai:\n");

    for(i=0;i<b->tehai.size();++i)
        printf (" %2d ",i+1);
    printf("\n");
    for(i=0;i<b->tehai.size();++i)
        printf(" %s ",b->tehai[i].pai_str.c_str());
    printf("\n");


    // select act or sutehai

    if (b->game_status==STATUS_TSUMORU){
        for(i=0;i<NUM_ACT;++i)
            if(i!=1 && i!=2 && b->act_list[i]) {
                n_act += 1;
                printf(" %d : %s\n",i,act_name[i]);
            }
        printf("select act:");
        cin.getline(str,128);
        s_act = atoi(str);
        printf("player choose %d\n",s_act);
    } else if (b->game_status==STATUS_KIRU) {
        while(1){
        printf("select sutehai:");
        cin.getline(str,128);
        if(!strcmp(str,"q"))exit(1);
        argout = atoi(str);
        printf("\n");
        if (argout>0 && argout<=b->tehai.size()) break;
        printf("wrong number\n");
        }
        printf("player sutehai number=%d\n",argout);
        if(argout==b->tehai.size()) s_act=ACT_TSUMOGIRI;
        else s_act=ACT_TEKIRI;
        return_act(s_act,argout);
    }
}

