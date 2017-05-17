#include "yaku.h"
#include "tools.h"

using namespace FZMAJ_NS;

Yaku::Yaku(FZMAJ *maj) : Pointers (maj) {
	
	yaku_fan[YAKU_REACH]			=  1;
	yaku_fan[YAKU_IPPATSU]			=  1;
	yaku_fan[YAKU_MENTSUMO]			=  1;
	yaku_fan[YAKU_TANYAO] 			=  1;
	yaku_fan[YAKU_PINFU]			=  1;
	yaku_fan[YAKU_IPPEI]			=  1;
	yaku_fan[YAKU_YAKUHAI_BAFUU]	=  1;
	yaku_fan[YAKU_YAKUHAI_JIFUU]	=  1;
	yaku_fan[YAKU_YAKUHAI_SANGEN]	=  1;
	yaku_fan[YAKU_RINSHAN]			=  1;
	yaku_fan[YAKU_CHANKAN]			=  1;
	yaku_fan[YAKU_HAITEI]			=  1;
	yaku_fan[YAKU_HOUTEI]			=  1;
	yaku_fan[YAKU_DORA]				=  1;
	yaku_fan[YAKU_URA]				=  1;
	yaku_fan[YAKU_AKA]				=  1;

	yaku_fan[YAKU_SANSHOKU]	 		=  2;
	yaku_fan[YAKU_IKKI]				=  2;
	yaku_fan[YAKU_HONCHAN]			=  2;
	yaku_fan[YAKU_CHIITOI]			=  2;
	yaku_fan[YAKU_TOITOI]			=  2;
	yaku_fan[YAKU_SANANKO] 			=  2;
	yaku_fan[YAKU_HONROU]			=  2;
	yaku_fan[YAKU_TONKO]			=  2;
	yaku_fan[YAKU_SANKANTSU]		=  2;
	yaku_fan[YAKU_SHOUSANGEN]		=  2;
	yaku_fan[YAKU_WREACH]			=  2;
	
	yaku_fan[YAKU_HONITSU]			=  3;
	yaku_fan[YAKU_JONCHAN]			=  3;
	yaku_fan[YAKU_RYANPEI]			=  3;
	
	yaku_fan[YAKU_CHINITSU]			=  6;

	yaku_fan[YAKU_KOKUSHI]			= 13;
	yaku_fan[YAKU_KOKUSHI_13]		= 13;
	yaku_fan[YAKU_SUANKO]			= 13;
	yaku_fan[YAKU_SUANKO_TANKI]		= 13;
	yaku_fan[YAKU_DASANGEN]			= 13;
	yaku_fan[YAKU_TSUIISOU]			= 13;
	yaku_fan[YAKU_SHOUSUSHI]		= 13;
	yaku_fan[YAKU_DASUSHI]			= 13;
	yaku_fan[YAKU_RYOUIISOU]		= 13;
	yaku_fan[YAKU_CHINROU]			= 13;
	yaku_fan[YAKU_SUKANTSU]		 	= 13;
	yaku_fan[YAKU_CHUUREN]			= 13;
	yaku_fan[YAKU_JONCHUUREN]		= 13;
	yaku_fan[YAKU_TENHOU]			= 13;
	yaku_fan[YAKU_CHIHOU]			= 13;


}

Yaku::~Yaku() {}


int Yaku::count_yaku(Bakyou *b, Pattern &p)
{
	int i;
	bak=b;
	pat=&p;
	printf("in count fan\n");

	for(i=0;i<46;++i)
		yaku[i]=0;
	
	if (is_reach()) yaku[YAKU_REACH]=yaku_fan[YAKU_REACH];

	if (is_ikki()) 
	printf("ikki\n");

	return 0;
}


int Yaku::is_reach()
{
	return bak->reach_jun[0];
}

int Yaku::is_ippatsu()
{
	return (bak->reach_jun[0]) && (bak->reach_jun[0]==bak->junmoku[0]);
}

int Yaku::is_mentsumo()
{
	return (bak->n_naki[0]==pat->n_ankan) && (bak->cur_pos==bak->pos_me);
}

int Yaku::is_tanyao()
{
	int i,j,k;
	int c[34];
	for(i=0;i<34;++i)
		c[i]=bak->c34[i];
	for(i=0;i<bak->n_naki[0];++i)
		for(j=0;j<3;++j) {
			k = bak->naki[0][i].naki_pai[j].pai_c;
			++c[k];
		}
	k = tools->count_19(c);
	return k==0;
}

int Yaku::is_pinfu()
{
	int i;
	if (bak->n_naki[0]) return 0;
	if (pat->n_syuntsu!=4) return 0;
	if (pat->atama==bak->bafuu+27 || pat->atama==bak->jifuu+27 || pat->atama>30) return 0;
	for (i=0;i<34;++i)
		if(pat->syuntsu[i])
			if((bak->cur_pai.pai_c==i && i%9!=6) || (bak->cur_pai.pai_c==i+2 && i%9!=0)) return 1;
	return 0;
}

int Yaku::is_ippei()
{
	return check_peikou()==1;
}

int Yaku::is_yakuhai_bafuu()
{
	int bafuu = bak->bafuu+27;
	return pat->kotsu[bafuu] || pat->naki_kotsu[bafuu];
}

int Yaku::is_yakuhai_jifuu()
{
	int jifuu = bak->jifuu+27;
	return pat->kotsu[jifuu] || pat->naki_kotsu[jifuu];
}

int Yaku::is_yakuhai_sangen()
{
	return pat->kotsu[31] + pat->kotsu[32] + pat->kotsu[33] + pat->naki_kotsu[31] + pat->naki_kotsu[32]
	 + pat->naki_kotsu[33];
}

int Yaku::is_chankan()
{
	return bak->game_status == STATUS_KAKAN;
}

int Yaku::is_rinshan()
{
	return bak->game_status == STATUS_RINSHAN;	
}

int Yaku::is_haitei()
{
	return bak->game_status == STATUS_TSUMORU && bak->pai_left==0;
}

int Yaku::is_houtei()
{
	return bak->game_status == STATUS_NAKI && bak->pai_left==0;
}

int Yaku::is_sanshoku()
{
	int i;
	for(i=0;i<7;++i)
		if( (pat->syuntsu[i] || pat->naki_syuntsu[i]) &&
		    (pat->syuntsu[i+9] || pat->naki_syuntsu[i+9]) &&
			(pat->syuntsu[i+18] || pat->naki_syuntsu[i+18]) )
			return 1;
	return 0;
}

int Yaku::is_ikki()
{
	return ((pat->syuntsu[ 0] || pat->naki_syuntsu[ 0]) &&
	        (pat->syuntsu[ 3] || pat->naki_syuntsu[ 3]) &&
			(pat->syuntsu[ 6] || pat->naki_syuntsu[ 6]) )
		|| ((pat->syuntsu[ 9] || pat->naki_syuntsu[ 9]) &&
		    (pat->syuntsu[12] || pat->naki_syuntsu[12]) &&
			(pat->syuntsu[15] || pat->naki_syuntsu[15]) )
		|| ((pat->syuntsu[18] || pat->naki_syuntsu[18]) &&
			(pat->syuntsu[21] || pat->naki_syuntsu[21]) &&
			(pat->syuntsu[24] || pat->naki_syuntsu[24]) );
}

int Yaku::is_honchan()
{
	if(!check_chanta()) return 0;	

	int i,nz;
	int *c = pat->c;

	nz = c[27]+c[28]+c[29]+c[30]+c[31]+c[32]+c[33];
	for(i=27;i<34;++i)
		nz += pat->naki_kotsu[i];
	return nz>0;
}

int Yaku::is_chiitoi()
{
	return pat->is_chiitoi;
}

int Yaku::is_toitoi()
{
	return (pat->n_naki_kotsu + pat->n_kotsu == 4);
}

int Yaku::is_sananko()
{
	return pat->n_kotsu == 3;
}

int Yaku::is_honrou()
{
	int k=0,i;
	int *c = pat->c;
}

int Yaku::is_tonko()
{

}

int Yaku::is_sankantsu()
{

}

int Yaku::is_shousangen()
{

}

int Yaku::is_wreach()
{

}

int Yaku::is_honitsu()
{

}

int Yaku::is_jonchan()
{

}

int Yaku::is_ryanpei()
{

}

int Yaku::is_chinitsu()
{

}

int Yaku::is_kokushi()
{

}

int Yaku::is_suanko()
{

}

int Yaku::is_dasangen()
{

}

int Yaku::is_tsuiisou()
{

}

int Yaku::is_shousushi()
{

}

int Yaku::is_dasushi()
{

}

int Yaku::is_ryouiisou()
{

}

int Yaku::is_chinrou()
{

}

int Yaku::is_sukantsu()
{

}

int Yaku::is_chouren()
{

}

int Yaku::is_junchouren()
{

}

int Yaku::is_tenhou()
{

}

int Yaku::is_chihou()
{

}

int Yaku::check_peikou()
{
	int peikou = 0, i;
	if (pat->n_syuntsu>=2)
		for(i=0;i<27;++i)
			peikou += (pat->syuntsu[i]>=2);
	return peikou;
}

int Yaku::check_chanta()
{
	int i;
	if(!tools->is_19z(pat->atama)) return 0;
	for(i=0;i<34;++i){
		if(pat->kotsu[i] || pat->naki_kotsu[i])
			if(!tools->is_19z(i)) return 0;
		if(pat->syuntsu[i])
			if((i!=0) && (i!=9) && (i!=18) && (i!=6) && (i!=15) && (i!=24)) return 0;
		if(pat->naki_syuntsu[i])
			if((i!=0) && (i!=9) && (i!=18) && (i!=6) && (i!=15) && (i!=24)) return 0;
	}
	return 1;
}
