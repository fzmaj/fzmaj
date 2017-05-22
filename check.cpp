#include "check.h"
#include "input.h"
#include "error.h"
#include "memory.h"
#include "tools.h"
#include "paili.h"
#include "game.h"

using namespace FZMAJ_NS;

Check::Check(FZMAJ *maj) : Pointers(maj) {}

void Check::command(int narg, char **arg)
{
  Pai last_pai;
  Naki tmp_naki;

  int start, ci,aka;
  int c_tot[34];
  int pat;
  int i,j,k;
  pat=0;
  start = 0;
  set_empty_bakyou();

  while(start<narg){

  printf("arg %d : %s\n",start, arg[start]);

	// 1. help
  if (!strcmp(arg[start],"-help")){
  	help();
	break;

	// 2. chii
  } else if (!strcmp(arg[start],"-chii")) {
    ++start;
	if (start>=narg) {
	  printf("wrong input\n");
	  return;
	} else {
	  printf("chii %s\n",arg[start]);
	  ci = tools->str2c(arg[start],aka);
	  if (ci==-1 || ci>=27 || ci%9==7 || ci%9==8) {printf("wrong input\n");return;}

	  tmp_naki.naki_type = NAKI_CHII;
	  tmp_naki.naki_from = 3;
	  tmp_naki.naki_id = 0;

	  tmp_naki.naki_pai[0] = tools->create_pai_from_c(ci,aka);
	  tmp_naki.naki_pai[1] = tools->create_pai_from_c(ci+1,0);
	  tmp_naki.naki_pai[2] = tools->create_pai_from_c(ci+2,0);
	  tmp_naki.naki_num=3;
	  ++bak.n_naki[0];
	  bak.naki[0].push_back(tmp_naki);
	}

	// 3. pon
  } else if (!strcmp(arg[start],"-pon")){
  	++start;
	if (start>=narg) {
		printf("wrong input\n");
		return;
	} else {
  	  printf("pon %s\n",arg[start]);
	  ci = tools->str2c(arg[start],aka);
	  if (ci==-1) {printf("wrong input -1\n");return;}

	  tmp_naki.naki_type = NAKI_PON;
	  tmp_naki.naki_from = 3;
	  tmp_naki.naki_id = 0;

	  tmp_naki.naki_pai[0] = tools->create_pai_from_c(ci,aka);
	  tmp_naki.naki_pai[1] = tools->create_pai_from_c(ci,0);
	  tmp_naki.naki_pai[2] = tools->create_pai_from_c(ci,0);
	  tmp_naki.naki_num=3;

	  ++bak.n_naki[0];
	  bak.naki[0].push_back(tmp_naki);
	}

	// 4. ankan
  } else if (!strcmp(arg[start],"-ankan")){
	++start;
	if (start>=narg) {
		printf("wrong input\n");
		return;
	} else {
		printf("ankan %s\n",arg[start]);
		ci = tools->str2c(arg[start],aka);
		if (ci==-1) {printf("wrong input\n");return;}

		tmp_naki.naki_type = NAKI_ANKAN;
		tmp_naki.naki_from = 3;
		tmp_naki.naki_id = 0;
		
		tmp_naki.naki_pai[0] = tools->create_pai_from_c(ci,aka);
		tmp_naki.naki_pai[1] = tools->create_pai_from_c(ci,0);
		tmp_naki.naki_pai[2] = tools->create_pai_from_c(ci,0);
		tmp_naki.naki_pai[3] = tools->create_pai_from_c(ci,0);
	    tmp_naki.naki_num=4;

		++bak.n_naki[0];
		bak.naki[0].push_back(tmp_naki);
	}

	// 5. minkan

  } else if (!strcmp(arg[start],"-minkan")){

	++start;
	if (start>=narg) {
		printf("wrong input\n");
		return;
	} else {
		printf("minkan %s\n",arg[start]);
		ci = tools->str2c(arg[start],aka);
		if (ci==-1) {printf("wrong input\n");return;}

		tmp_naki.naki_type = NAKI_MINKAN;
		tmp_naki.naki_from = 3;
		tmp_naki.naki_id = 0;

		tmp_naki.naki_pai[0] = tools->create_pai_from_c(ci,aka);
		tmp_naki.naki_pai[1] = tools->create_pai_from_c(ci,0);
		tmp_naki.naki_pai[2] = tools->create_pai_from_c(ci,0);
		tmp_naki.naki_pai[3] = tools->create_pai_from_c(ci,0);
	    tmp_naki.naki_num=4;
		
		++bak.n_naki[0];
		bak.naki[0].push_back(tmp_naki);
	}

	// 6. reach

  } else if (!strcmp(arg[start],"-reach")) {
  	bak.reach_jun[0]=2;

	// 7. double reach
  } else if (!strcmp(arg[start],"-wreach")) {
  	bak.reach_jun[0]=1;

	// 8. ippatsu 
  } else if (!strcmp(arg[start],"-ippatsu")) {
  	bak.junmoku[0]=bak.reach_jun[0];

	// 9. ron

	// 10. dora set

	// 11. ura set

	// last. tehai
  } else {
  	if(pat==0) {
   	  last_pai = tools->str2pai(arg[start],&bak);
      pat=1;
	} else {
		printf("wrong input\n");
		return;
	}
  }
  ++start;
  }

	// check reasonable tehai and naki


  for(i=0;i<34;++i)
  	c_tot[i]=bak.c34[i];
  for(i=0;i<bak.n_naki[0];++i)
  	for(j=0;j<bak.naki[0][i].naki_num;++j)
	{
	  k=bak.naki[0][i].naki_pai[j].pai_c;
	  ++c_tot[k];
	  if(c_tot[k]>4) {printf("too many same pai in naki\n");return;}
	}
  if (tools->count34(c_tot)>14) {printf("too many pais\n");return;}


  if (start==narg)
  	paili->test(&bak);
}

void Check::set_empty_bakyou()
{
	int i;

	bak.bafuu = 0;
	bak.jifuu = 2;
	bak.kyoku = 0;
	bak.honba = 0;
	bak.residue = 0;
	bak.oya = 0;

	bak.n_dora = 0;
	bak.dora.clear();
	bak.ura_check = 0;
	bak.ura.clear();
	bak.dora_hyouji.clear();
	
	bak.pai_ptr = 23;
	bak.pai_left = 99;
	bak.tehai.clear();

	bak.n_tehai=0;
	
	for(i=0;i<34;++i)
		bak.c34[i]=0;

	bak.river.resize(4);
	bak.naki.resize(4);

	for(i=0;i<4;++i) {
		bak.score[i] = 25000;
		bak.rank[i] = i;
		bak.n_naki[i]=0;
		bak.junmoku[i]=0;
        bak.reach_jun[i]=0;
		bak.river[i].clear();
		bak.naki[i].clear();

	}
    bak.cur_pos = 0;
    bak.pos_me = 0;
}

void Check::help()
{
	printf("I am help.\n");
}
