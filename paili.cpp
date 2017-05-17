#include "paili.h"
#include "tools.h"
#include "defs.h"
#include "yaku.h"
#include <vector>

using namespace FZMAJ_NS;

Paili::Paili(FZMAJ *maj) : Pointers(maj)

{
	yaku = new Yaku(maj);
}


Paili::~Paili() {
	delete yaku;
}

void Paili::test(Bakyou *b)
{
	int i;
	int cnt;
	int iak;
	printf("*** paili test ***\n");
	bak = b;
	cnt = b->tehai.size();
	printf(" n_tehai = %d\n",cnt);
	if(cnt%3==0){
		printf(" wrong tehai number\n");
		return;
	}
	// print tehai
	for(i=0;i<b->tehai.size();++i)
		printf("%s ",b->tehai[i].pai_str.c_str());
	// print naki
	print_naki();

	if (cnt%3==2)
	{
		iak = test_agari_kata();
		printf("agari_kata = %d\n",iak);
	}
	agari(b);
}

void Paili::print_naki()
{
	int i;
	Bakyou *b = bak;
	if(!b->n_naki[0]){
		printf("\n");
		return;}
	printf(" naki: ");
	for(i=0;i<b->naki[0].size();++i) {
		if (b->naki[0][i].naki_type==NAKI_CHII || b->naki[0][i].naki_type==NAKI_PON)
			printf(" %s%s%s ",b->naki[0][i].naki_pai[0].pai_str.c_str(),
							  b->naki[0][i].naki_pai[1].pai_str.c_str(),
							  b->naki[0][i].naki_pai[2].pai_str.c_str());
		else if (b->naki[0][i].naki_type==NAKI_MINKAN)
			printf(" %s%s%s%s ",b->naki[0][i].naki_pai[0].pai_str.c_str(),
							    b->naki[0][i].naki_pai[1].pai_str.c_str(),
							    b->naki[0][i].naki_pai[2].pai_str.c_str(),
							    b->naki[0][i].naki_pai[3].pai_str.c_str());
		else if (b->naki[0][i].naki_type==NAKI_ANKAN)
			printf(" %s****%s ",b->naki[0][i].naki_pai[0].pai_str.c_str(),
							    b->naki[0][i].naki_pai[2].pai_str.c_str());
	}
	printf("\n");
}


int Paili::test_agari_kata()
{
  int cnt = tools->count34(bak->c34);
  printf("cnt=%d\n",cnt);

  if (cnt%3!=2)
    return -1;

  int *c=bak->c34;
  int j=(1<<c[27])|(1<<c[28])|(1<<c[29])|(1<<c[30])|(1<<c[31])|(1<<c[32])|(1<<c[33]);
  if (j>=0x10) return 0;
  // Kokushi musou
  if (((j&3)==2) && (c[0]*c[8]*c[9]*c[17]*c[18]*c[26]*c[27]*c[28]*c[29]*c[30]*c[31]*c[32]*c[33]==2)) return 1;
  // 7 tui tsu
  if (!(j&10) && (
    (c[ 0]==2)+(c[ 1]==2)+(c[ 2]==2)+(c[ 3]==2)+(c[ 4]==2)+(c[ 5]==2)+(c[ 6]==2)+(c[ 7]==2)+(c[ 8]==2)+
    (c[ 9]==2)+(c[10]==2)+(c[11]==2)+(c[12]==2)+(c[13]==2)+(c[14]==2)+(c[15]==2)+(c[16]==2)+(c[17]==2)+
    (c[18]==2)+(c[19]==2)+(c[20]==2)+(c[21]==2)+(c[22]==2)+(c[23]==2)+(c[24]==2)+(c[25]==2)+(c[26]==2)+
    (c[27]==2)+(c[28]==2)+(c[29]==2)+(c[30]==2)+(c[31]==2)+(c[32]==2)+(c[33]==2))==7) return 1;
  if (j&2) return 0;
  int n00 = c[ 0]+c[ 3]+c[ 6], n01 = c[ 1]+c[ 4]+c[ 7], n02 = c[ 2]+c[ 5]+c[ 8];
  int n10 = c[ 9]+c[12]+c[15], n11 = c[10]+c[13]+c[16], n12 = c[11]+c[14]+c[17];
  int n20 = c[18]+c[21]+c[24], n21 = c[19]+c[22]+c[25], n22 = c[20]+c[23]+c[26];
  int n0 = (n00+n01+n02)%3;
  if (n0==1) return 0;
  int n1 = (n10+n11+n12)%3;
  if (n1==1) return 0;
  int n2 = (n20+n21+n22)%3;
  if (n2==1) return 0;
  if ((n0==2)+(n1==2)+(n2==2)+
    (c[27]==2)+(c[28]==2)+(c[29]==2)+(c[30]==2)+(c[31]==2)+(c[32]==2)+(c[33]==2)!=1) return 0;
  int nn0=(n00*1+n01*2)%3, m0=cc2m(c, 0);
  int nn1=(n10*1+n11*2)%3, m1=cc2m(c, 9);
  int nn2=(n20*1+n21*2)%3, m2=cc2m(c,18);
  if (j&4) return !(n0|nn0|n1|nn1|n2|nn2) && is_mentsu(m0) && is_mentsu(m1) && is_mentsu(m2);
  if (n0==2) return !(n1|nn1|n2|nn2) && is_mentsu(m1) && is_mentsu(m2) && is_atama_mentsu(nn0,m0);
  if (n1==2) return !(n2|nn2|n0|nn0) && is_mentsu(m2) && is_mentsu(m0) && is_atama_mentsu(nn1,m1);
  if (n2==2) return !(n0|nn0|n1|nn1) && is_mentsu(m0) && is_mentsu(m1) && is_atama_mentsu(nn2,m2);
  return 0;
}

bool Paili::is_mentsu(int m)
{
  int a=(m&7), b=0, c=0;
  if (a==1 || a==4) b=c=1; else if (a==2) b=c=2;
  m>>=3, a=(m&7)-b;if (a<0) return false;b=c, c=0;if (a==1 || a==4) b+=1, c+=1; else if (a==2) b+=2, c+=2;
  m>>=3, a=(m&7)-b;if (a<0) return false;b=c, c=0;if (a==1 || a==4) b+=1, c+=1; else if (a==2) b+=2, c+=2;
  m>>=3, a=(m&7)-b;if (a<0) return false;b=c, c=0;if (a==1 || a==4) b+=1, c+=1; else if (a==2) b+=2, c+=2;
  m>>=3, a=(m&7)-b;if (a<0) return false;b=c, c=0;if (a==1 || a==4) b+=1, c+=1; else if (a==2) b+=2, c+=2;
  m>>=3, a=(m&7)-b;if (a<0) return false;b=c, c=0;if (a==1 || a==4) b+=1, c+=1; else if (a==2) b+=2, c+=2;
  m>>=3, a=(m&7)-b;if (a<0) return false;b=c, c=0;if (a==1 || a==4) b+=1, c+=1; else if (a==2) b+=2, c+=2;
  m>>=3, a=(m&7)-b;if (a!=0 && a!=3) return false;
  m>>=3, a=(m&7)-c;
  return a==0 || a==3;
}

bool Paili::is_atama_mentsu(int nn, int m)
{
  if (nn==0){
    if ((m&(7<< 6))>=(2<< 6) && is_mentsu(m-(2<< 6))) return true;
    if ((m&(7<<15))>=(2<<15) && is_mentsu(m-(2<<15))) return true;
    if ((m&(7<<24))>=(2<<24) && is_mentsu(m-(2<<24))) return true;
  }else if (nn==1){
    if ((m&(7<< 3))>=(2<< 3) && is_mentsu(m-(2<< 3))) return true;
    if ((m&(7<<12))>=(2<<12) && is_mentsu(m-(2<<12))) return true;
    if ((m&(7<<21))>=(2<<21) && is_mentsu(m-(2<<21))) return true;
  }else if (nn==2){
    if ((m&(7<< 0))>=(2<< 0) && is_mentsu(m-(2<< 0))) return true;
    if ((m&(7<< 9))>=(2<< 9) && is_mentsu(m-(2<< 9))) return true;
    if ((m&(7<<18))>=(2<<18) && is_mentsu(m-(2<<18))) return true;
  }
  return false;
}

int Paili::cc2m(int c[], int d)
{
  return (c[d+0]<< 0)|(c[d+1]<< 3)|(c[d+2]<< 6)|
         (c[d+3]<< 9)|(c[d+4]<<12)|(c[d+5]<<15)|
         (c[d+6]<<18)|(c[d+7]<<21)|(c[d+8]<<24);
}

void Paili::i_kotsu(int k)
	{c[k]-=3;++n_mentsu;++kotsu[k];++n_kotsu;}

void Paili::d_kotsu(int k)
	{c[k]+=3;--n_mentsu;--kotsu[k];--n_kotsu;}

void Paili::i_syuntsu(int k)
	{--c[k];--c[k+1];--c[k+2];++n_mentsu;++n_syuntsu;++syuntsu[k];}

void Paili::d_syuntsu(int k)
	{++c[k];++c[k+1];++c[k+2];--n_mentsu;--n_syuntsu;--syuntsu[k];}

void Paili::i_atama(int k)
	{c[k]-=2;atama=k;isatama=1;}

void Paili::d_atama(int k)
	{c[k]+=2;isatama=0;}

void Paili::remove_jihai()
{
	int i;
	for(i=27;i<34;++i){
		if (c[i]==2) i_atama(i);
		if (c[i]==3) i_kotsu(i);
	}
}

int Paili::agari(Bakyou* b)
{
	int i;
	int cnt;
	bak = b;
	for(i=0;i<34;++i)
		c[i]=bak->c34[i];
	cnt=bak->tehai.size();
	if (cnt+3*bak->n_naki[0]!=14) {printf("wrong agari\n");return -1;}

	// initialize agari

	n_mentsu = bak->n_naki[0];
	isatama = 0;

	fan = 0;
	fu = 0;
	score = 0;
	score_ko = 0;
	score_oya = 0;
	n_syuntsu = 0;
	n_kotsu = 0;
	atama = 0;

	pat.clear();
	n_pat = 0;

	for (i=0;i<34;++i) {
		kotsu[i]=0;
		syuntsu[i]=0;
		naki_kotsu[i]=0;
		naki_syuntsu[i]=0;
	}

	count_naki();
	toku_handan();

}

void Paili::toku_handan()
{

	int i,j,k;
	// Kokushi musou
	if (c[0]*c[8]*c[9]*c[17]*c[18]*c[26]*c[27]*c[28]*c[29]*c[30]*c[31]*c[32]*c[33]==2) {
		add_pat();
		pat[n_pat-1].is_kokushi = 1;
		pat[n_pat-1].is_yakuman = 1;
	}

	// Chiitoi
	for(i=0;i<34;++i)
		k+=c[i]==2;
	if(k==7){
		add_pat();
		pat[n_pat-1].is_chiitoi = 1;
	}
	 
	 remove_jihai();
	 run_tehai(0);
	 

	 printf("n_pat %d\n",n_pat);

	 // show pattern

	 for(i=0;i<n_pat;++i)
	 {
	 	printf("pat %d\n",i);
		printf("n_kotsu = %d, n_syuntsu = %d, atama = %d\n",pat[i].n_kotsu,pat[i].n_syuntsu,pat[i].atama);
	 	if(pat[i].n_kotsu)
			for(j=0;j<34;++j)
				if (pat[i].kotsu[j]) printf("%s%s%s ",tools->c2str(j,0).c_str(),
				tools->c2str(j,0).c_str(),tools->c2str(j,0).c_str());
		if(pat[i].n_syuntsu)
			for(j=0;j<34;++j)
				if (pat[i].syuntsu[j]) 
				for(k=0;k<pat[i].syuntsu[j];++k)
				printf("%s%s%s ",tools->c2str(j,0).c_str(),
				tools->c2str(j+1,0).c_str(),tools->c2str(j+2,0).c_str());
		printf("%s%s ",tools->c2str(pat[i].atama,0).c_str(),tools->c2str(pat[i].atama,0).c_str());
		print_naki();

		yaku->count_yaku(bak,pat[i]);

	 }

}

void Paili::add_pat()
{
	int i;
	Pattern tmp_pat;
	++n_pat;
	tmp_pat.n_syuntsu = n_syuntsu;
	tmp_pat.n_kotsu = n_kotsu; 
	tmp_pat.n_naki_syuntsu = n_naki_syuntsu;
	tmp_pat.n_naki_kotsu = n_naki_kotsu;
	tmp_pat.n_naki = bak->n_naki[0];
	tmp_pat.is_kokushi = 0;
	tmp_pat.is_chiitoi = 0;
	tmp_pat.is_yakuman = 0;
	tmp_pat.yakuman_baisu = 0;

	for(i=0;i<34;++i) {
		tmp_pat.kotsu[i]=kotsu[i];
		tmp_pat.syuntsu[i]=syuntsu[i];
		tmp_pat.naki_kotsu[i]=naki_kotsu[i];
		tmp_pat.naki_syuntsu[i]=naki_syuntsu[i];
	}
	tmp_pat.atama = atama;

	pat.push_back(tmp_pat);

}

void Paili::count_naki()
{
	int i;
	n_naki_syuntsu = 0;
	n_naki_kotsu = 0;
	n_ankan = 0;
	n_naki_kan = 0;
	
	for(i=0;i<bak->n_naki[0];++i)
	{
		if (bak->naki[0][i].naki_type == NAKI_CHII)
		{	++n_naki_syuntsu;++naki_syuntsu[bak->naki[0][i].naki_pai[0].pai_c];}
		else if (bak->naki[0][i].naki_type == NAKI_PON)
		{	++n_naki_kotsu;++naki_kotsu[bak->naki[0][i].naki_pai[0].pai_c];}
		else if (bak->naki[0][i].naki_type == NAKI_ANKAN)
		{	++n_ankan;++kotsu[bak->naki[0][i].naki_pai[0].pai_c];}
		else if (bak->naki[0][i].naki_type == NAKI_MINKAN || bak->naki[0][i].naki_type == NAKI_KAKAN)
		{	++n_naki_kan;++naki_kotsu[bak->naki[0][i].naki_pai[0].pai_c];}
	}
}

void Paili::run_tehai(int depth)
{
	for(;depth<27&&!c[depth];++depth);
	update_result();
	int i=depth;
	if(i>8)i-=9;
	if(i>8)i-=9;
	switch(c[depth]) {
	case 4: {
		i_kotsu(depth);
		if(i<7&&c[depth+1]&&c[depth+2]){
			i_syuntsu(depth);run_tehai(depth+1);d_syuntsu(depth);
		}
		d_kotsu(depth);
		if (!isatama) {
			i_atama(depth);
			if (i<7&&c[depth+1]&&c[depth+2]){
				i_syuntsu(depth);run_tehai(depth);d_syuntsu(depth);
			}
			d_atama(depth);
		}
		break;
	}
	case 3: {
		i_kotsu(depth);run_tehai(depth+1);d_kotsu(depth);
		if (!isatama) {
			i_atama(depth);
			if (i<7&&c[depth+1]&&c[depth+2]) {
				i_syuntsu(depth);run_tehai(depth+1);d_syuntsu(depth);
			}
			d_atama(depth);
		}
		if (i<7&&c[depth+1]>=2&&c[depth+2]>=2) {
			i_syuntsu(depth);i_syuntsu(depth);run_tehai(depth);d_syuntsu(depth);d_syuntsu(depth);
		}
		break;
	}
	case 2: {
		if (!isatama) {
			i_atama(depth);run_tehai(depth+1);d_atama(depth);
		}
		if (i<7&&c[depth+1]&&c[depth+2]) {
			i_syuntsu(depth);run_tehai(depth+1);d_syuntsu(depth);
		}
		break;
	}
	case 1: {
		if (i<7&&c[depth+1]&&c[depth+2]) {
			i_syuntsu(depth);run_tehai(depth+1);d_syuntsu(depth);
		}
		break;
	}
	}
}

void Paili::update_result()
{
	if ((n_mentsu==4) && isatama ) {
		add_pat();
	}
}
