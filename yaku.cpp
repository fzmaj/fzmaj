#include "yaku.h"
#include "tools.h"

using namespace FZMAJ_NS;

Yaku::Yaku(FZMAJ *maj) : Pointers (maj) {
    
    yaku_fan[YAKU_REACH]            =  1;
    yaku_fan[YAKU_IPPATSU]          =  1;
    yaku_fan[YAKU_MENTSUMO]         =  1;
    yaku_fan[YAKU_TANYAO]           =  1;
    yaku_fan[YAKU_PINFU]            =  1;
    yaku_fan[YAKU_IPPEI]            =  1;
    yaku_fan[YAKU_YAKUHAI_BAFUU]    =  1;
    yaku_fan[YAKU_YAKUHAI_JIFUU]    =  1;
    yaku_fan[YAKU_YAKUHAI_SANGEN]   =  1;
    yaku_fan[YAKU_RINSHAN]          =  1;
    yaku_fan[YAKU_CHANKAN]          =  1;
    yaku_fan[YAKU_HAITEI]           =  1;
    yaku_fan[YAKU_HOUTEI]           =  1;
    yaku_fan[YAKU_DORA]             =  1;
    yaku_fan[YAKU_URA]              =  1;
    yaku_fan[YAKU_AKA]              =  1;

    yaku_fan[YAKU_SANSHOKU]         =  2;
    yaku_fan[YAKU_IKKI]             =  2;
    yaku_fan[YAKU_HONCHAN]          =  2;
    yaku_fan[YAKU_CHIITOI]          =  2;
    yaku_fan[YAKU_TOITOI]           =  2;
    yaku_fan[YAKU_SANANKO]          =  2;
    yaku_fan[YAKU_HONROU]           =  2;
    yaku_fan[YAKU_TONKO]            =  2;
    yaku_fan[YAKU_SANKANTSU]        =  2;
    yaku_fan[YAKU_SHOUSANGEN]       =  2;
    yaku_fan[YAKU_WREACH]           =  2;
    
    yaku_fan[YAKU_HONITSU]          =  3;
    yaku_fan[YAKU_JONCHAN]          =  3;
    yaku_fan[YAKU_RYANPEI]          =  3;
    
    yaku_fan[YAKU_CHINITSU]         =  6;

    yaku_fan[YAKU_KOKUSHI]          = 13;
    yaku_fan[YAKU_KOKUSHI_13]       = 13;
    yaku_fan[YAKU_SUANKO]           = 13;
    yaku_fan[YAKU_SUANKO_TANKI]     = 13;
    yaku_fan[YAKU_DASANGEN]         = 13;
    yaku_fan[YAKU_TSUIISOU]         = 13;
    yaku_fan[YAKU_SHOUSUSHI]        = 13;
    yaku_fan[YAKU_DASUSHI]          = 13;
    yaku_fan[YAKU_RYOUIISOU]        = 13;
    yaku_fan[YAKU_CHINROU]          = 13;
    yaku_fan[YAKU_SUKANTSU]         = 13;
    yaku_fan[YAKU_CHUUREN]          = 13;
    yaku_fan[YAKU_JONCHUUREN]       = 13;
    yaku_fan[YAKU_TENHOU]           = 13;
    yaku_fan[YAKU_CHIHOU]           = 13;


}

Yaku::~Yaku() {}


int Yaku::count_yaku(Bakyou *b, Pattern &p)
{
    int i;
    int tmp_fan;
    bak=b;
    pat=&p;

    for(i=0;i<46;++i)
        yaku[i]=0;
    
    if (is_reach()) yaku[YAKU_REACH]=yaku_fan[YAKU_REACH];
    
    if (is_ippatsu()) yaku[YAKU_IPPATSU]=yaku_fan[YAKU_IPPATSU];

    if (is_mentsumo()) yaku[YAKU_MENTSUMO]=yaku_fan[YAKU_MENTSUMO];

    if (is_tanyao()) yaku[YAKU_TANYAO]=yaku_fan[YAKU_TANYAO];

    if (is_pinfu()) yaku[YAKU_PINFU]=yaku_fan[YAKU_PINFU];

    if (is_ippei()) {yaku[YAKU_IPPEI]=yaku_fan[YAKU_IPPEI];
        if (bak->n_naki[0]!=pat->n_ankan) --yaku[YAKU_IPPEI];}

    if (is_yakuhai_bafuu()) yaku[YAKU_YAKUHAI_BAFUU]=yaku_fan[YAKU_YAKUHAI_BAFUU];

    if (is_yakuhai_jifuu()) yaku[YAKU_YAKUHAI_JIFUU]=yaku_fan[YAKU_YAKUHAI_JIFUU];
    
    if (is_yakuhai_sangen()) yaku[YAKU_YAKUHAI_SANGEN] += is_yakuhai_sangen();
    
    if (is_rinshan()) yaku[YAKU_RINSHAN]=yaku_fan[YAKU_RINSHAN];

    if (is_chankan()) yaku[YAKU_CHANKAN]=yaku_fan[YAKU_CHANKAN];

    if (is_haitei()) yaku[YAKU_HAITEI]=yaku_fan[YAKU_HAITEI];

    if (is_houtei()) yaku[YAKU_HOUTEI]=yaku_fan[YAKU_HOUTEI];

    if (is_sanshoku()) {yaku[YAKU_SANSHOKU]=yaku_fan[YAKU_SANSHOKU];
        if (bak->n_naki[0]!=pat->n_ankan) --yaku[YAKU_SANSHOKU];}

    if (is_ikki()) {yaku[YAKU_IKKI]=yaku_fan[YAKU_IKKI];
        if (bak->n_naki[0]!=pat->n_ankan) --yaku[YAKU_IKKI];}

    if (is_honchan()) {yaku[YAKU_HONCHAN]=yaku_fan[YAKU_HONCHAN];
        if (bak->n_naki[0]!=pat->n_ankan) --yaku[YAKU_HONCHAN];}

    if (is_chiitoi()) yaku[YAKU_CHIITOI]=yaku_fan[YAKU_CHIITOI];

    if (is_toitoi()) yaku[YAKU_TOITOI]=yaku_fan[YAKU_TOITOI];

    if (is_sananko()) yaku[YAKU_SANANKO]=yaku_fan[YAKU_SANANKO];

    if (is_honrou()) yaku[YAKU_HONROU]=yaku_fan[YAKU_HONROU];

    if (is_tonko()) yaku[YAKU_TONKO]=yaku_fan[YAKU_TONKO];

    if (is_sankantsu()) yaku[YAKU_SANKANTSU]=yaku_fan[YAKU_SANKANTSU];

    if (is_shousangen()) yaku[YAKU_SHOUSANGEN]=yaku_fan[YAKU_SHOUSANGEN];

    if (is_wreach()) yaku[YAKU_WREACH]=yaku_fan[YAKU_WREACH];

    if (is_honitsu()) {yaku[YAKU_HONITSU]=yaku_fan[YAKU_HONITSU];
        if (bak->n_naki[0]!=pat->n_ankan) --yaku[YAKU_HONITSU];}

    if (is_jonchan()) {yaku[YAKU_JONCHAN]=yaku_fan[YAKU_JONCHAN];
        if (bak->n_naki[0]!=pat->n_ankan) --yaku[YAKU_JONCHAN];}

    if (is_ryanpei()) yaku[YAKU_RYANPEI]=yaku_fan[YAKU_RYANPEI];

    if (is_chinitsu()) {yaku[YAKU_CHINITSU]=yaku_fan[YAKU_CHINITSU];
        if (bak->n_naki[0]!=pat->n_ankan) --yaku[YAKU_CHINITSU];}

    if (is_kokushi()) {yaku[YAKU_KOKUSHI]=yaku_fan[YAKU_KOKUSHI];
        pat->is_yakuman = 1; ++pat->yakuman_baisu;}

    if (is_kokushi_13()) {yaku[YAKU_KOKUSHI_13]=yaku_fan[YAKU_KOKUSHI_13];
        pat->is_yakuman = 1; ++pat->yakuman_baisu;}

    if (is_suanko()) {yaku[YAKU_SUANKO]=yaku_fan[YAKU_SUANKO];
        pat->is_yakuman = 1; ++pat->yakuman_baisu;}

    if (is_suanko_tanki()) {yaku[YAKU_SUANKO_TANKI]=yaku_fan[YAKU_SUANKO_TANKI];
        pat->is_yakuman = 1; ++pat->yakuman_baisu;}

    if (is_dasangen()) {yaku[YAKU_DASANGEN]=yaku_fan[YAKU_DASANGEN];
        pat->is_yakuman = 1; ++pat->yakuman_baisu;}

    if (is_tsuiisou()) {yaku[YAKU_TSUIISOU]=yaku_fan[YAKU_TSUIISOU];
        pat->is_yakuman = 1; ++pat->yakuman_baisu;}

    if (is_shousushi()) {yaku[YAKU_SHOUSUSHI]=yaku_fan[YAKU_SHOUSUSHI];
        pat->is_yakuman = 1; ++pat->yakuman_baisu;}

    if (is_dasushi()) {yaku[YAKU_DASUSHI]=yaku_fan[YAKU_DASUSHI];
        pat->is_yakuman = 1; ++pat->yakuman_baisu;}

    if (is_ryouiisou()) {yaku[YAKU_RYOUIISOU]=yaku_fan[YAKU_RYOUIISOU];
        pat->is_yakuman = 1; ++pat->yakuman_baisu;}

    if (is_chinrou()) {yaku[YAKU_CHINROU]=yaku_fan[YAKU_CHINROU];
        pat->is_yakuman = 1; ++pat->yakuman_baisu;}

    if (is_sukantsu()) {yaku[YAKU_SUKANTSU]=yaku_fan[YAKU_SUKANTSU];
        pat->is_yakuman = 1; ++pat->yakuman_baisu;}

    for (i=0;i<46;++i)
        if (yaku[i]) 
            if ((yaku[i]<13 && pat->yakuman_baisu==0) || yaku[i]>=13)
               printf("  %20s   %d fan\n",YAKU_NAME[i],yaku[i]);
        
    return 0;
}


int Yaku::is_reach()
{
    return bak->reach_jun[0]>1;
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
    for(i=0;i<34;++i)
        if(c[i] && !tools->is_19z(i)) return 0;
    return c[27]+c[28]+c[29]+c[30]+c[31]+c[32]+c[33]>0;
}

int Yaku::is_tonko()
{
    int i;
    for(i=0;i<9;++i)
        if ( (pat->kotsu[i]    || pat->naki_kotsu[i])    + 
             (pat->kotsu[i+9]  || pat->naki_kotsu[i+9])  +
             (pat->kotsu[i+18] || pat->naki_kotsu[i+19]) ==3)
            return 1;
    return 0;
}

int Yaku::is_sankantsu()
{
    return pat->n_kan==3;
}

int Yaku::is_shousangen()
{
    int i,k=0;
    for(i=31;i<34;++i)
        if (pat->kotsu[i] || pat->naki_kotsu[i]) ++k;
    return k==2 && (pat->atama==31 || pat->atama==32 || pat->atama==33);
}

int Yaku::is_wreach()
{
    return bak->reach_jun[0]==1;
}

int Yaku::is_honitsu()
{
    int i,j,nz,k;
    int *c = pat->c;
    nz=c[27]+c[28]+c[29]+c[30]+c[31]+c[32]+c[33];
    k=(bak->tehai[0].pai_c)/9;
    for(i=1;i<bak->tehai.size();++i)
        if (bak->tehai[i].pai_c<27 && bak->tehai[i].pai_c/9!=k) return 0;
    for(i=0;i<bak->n_naki[0];++i)
        for(j=0;j<3;++j)
            if(bak->naki[0][i].naki_pai[j].pai_c/9!=k) return 0;
    return nz>1;
}

int Yaku::is_jonchan()
{

    if(!check_chanta()) return 0;   
    int i,nz;
    int *c = pat->c;
    nz = c[27]+c[28]+c[29]+c[30]+c[31]+c[32]+c[33];
    return nz==0;
}

int Yaku::is_ryanpei()
{
    return check_peikou()==2;
}

int Yaku::is_chinitsu()
{
    int i,j,nz,k;
    int *c = pat->c;
    nz=c[27]+c[28]+c[29]+c[30]+c[31]+c[32]+c[33];
    k=(bak->tehai[0].pai_c)/9;
    for(i=1;i<bak->tehai.size();++i)
        if (bak->tehai[i].pai_c/9!=k) return 0;
    for(i=0;i<bak->n_naki[0];++i)
        for(j=0;j<3;++j)
            if(bak->naki[0][i].naki_pai[j].pai_c/9!=k) return 0;
    return nz==0;
}

int Yaku::is_kokushi()
{
    return pat->is_kokushi && pat->c[bak->cur_pai.pai_c]==1;
}

int Yaku::is_kokushi_13()
{
    return pat->is_kokushi && pat->c[bak->cur_pai.pai_c]==2;
}

int Yaku::is_suanko()
{
    return pat->n_kotsu==4 && pat->atama!=bak->cur_pai.pai_c;
}

int Yaku::is_suanko_tanki()
{
    return pat->n_kotsu==4 && pat->atama==bak->cur_pai.pai_c;
}

int Yaku::is_dasangen()
{
    return pat->c[31]>=3 && pat->c[32]>=3 && pat->c[33]>=3;
}

int Yaku::is_tsuiisou()
{
    int i,k=0;
    for(i=0;i<27;++i)
        k+=pat->c[i];
    return k==0;
}

int Yaku::is_shousushi()
{
    int *c = pat->c;
    return (c[27]>=3)+(c[28]>=3)+(c[29]>=3)+(c[30]>=3)==3 && 
    (pat->atama=27 || pat->atama==28 || pat->atama==29 || pat->atama==30);
}

int Yaku::is_dasushi()
{
    int *c = pat->c;
    return c[27]>=3 && c[28]>=3 && c[29]>=3 && c[30]>=3;
}

int Yaku::is_ryouiisou()
{
    int *c = pat->c;
    return c[19]+c[20]+c[21]+c[23]+c[25]+c[32]==tools->count34(c);
}

int Yaku::is_chinrou()
{
    int *c = pat->c;
    return c[0]+c[8]+c[9]+c[17]+c[18]+c[26]==tools->count34(c);
}

int Yaku::is_sukantsu()
{
    return pat->n_kan==4;
}

int Yaku::is_chouren()
{
    if(bak->n_naki[0])return 0;
    int i,k;
    int *c = pat->c;
    for(i=0;i<2;++i)
        if ( c[0+i*9]>=3 && c[1+i*9]>=1 && c[2+i*9]>=1 && c[3+i*9]>=1 && c[4+i*9]>=1 &&
             c[5+i*9]>=1 && c[6+i*9]>=1 && c[7+i*9]>=1 && c[8+i*9]>=3)
        {
            k=bak->cur_pai.pai_c;
            if(k%9==0 || k%9==8) return c[k]==3;
            else return c[k]==1;
        }
    return 0;
}

int Yaku::is_junchouren()
{
    if(bak->n_naki[0])return 0;
    int i,k;
    int *c = pat->c;
    for(i=0;i<2;++i)
        if ( c[0+i*9]>=3 && c[1+i*9]>=1 && c[2+i*9]>=1 && c[3+i*9]>=1 && c[4+i*9]>=1 &&
             c[5+i*9]>=1 && c[6+i*9]>=1 && c[7+i*9]>=1 && c[8+i*9]>=3)
        {
            k=bak->cur_pai.pai_c;
            if(k%9==0 || k%9==8) return c[k]==4;
            else return c[k]==2;
        }
    return 0;
}

int Yaku::is_tenhou()
{
    return bak->junmoku[0]==1 && bak->cur_pos == bak->pos_me;
}

int Yaku::is_chihou()
{
    return bak->junmoku[0]==1 && bak->cur_pos != bak->pos_me;
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
