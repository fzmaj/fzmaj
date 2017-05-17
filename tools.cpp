#include "tools.h"
#include "stdlib.h"
#include "string.h"
#include "error.h"
#include "game.h"
#include "defs.h"

#include <string>

using namespace FZMAJ_NS;
using namespace std;


Tools::Tools(FZMAJ *maj) : Pointers(maj) {}

Tools::~Tools(){}

string Tools::c2str(int cp, int aka)
{
  string sth = "";
  char tp;
  if (cp>=9) {cp -= 9; tp = 'p';}
  else tp='m';
  if (cp>=9) {cp -= 9; tp = 's';}
  if (cp>=9) {cp -= 9; tp = 'z';}
  if (aka) sth += '0';
  else sth += ('1'+cp);
  sth += tp;
  return sth;
}

Pai Tools::create_pai_from_c(int c, int aka)
{
	Pai tmp_pai;
	tmp_pai.pai_c = c;
	if (aka==0 && c%9==4) tmp_pai.pai_id = c<<2 +1;
	else tmp_pai.pai_id = c<<2;
	tmp_pai.pai_aka = aka;
	tmp_pai.pai_str = c2str(c,aka);
	return tmp_pai;
}

int Tools::str2c(string str, int& aka)
{
	int t,p;
	aka=0;
	if(str.length()!=2) return -1;
	if(str[1]=='z') p=27;
	else if (str[1]=='s') p=18;
	else if (str[1]=='p') p=9;
	else if (str[1]=='m') p=0;
	else return -1;
	if(str[1]!='z' && str[0]=='0'){t=4; aka=1;}
	else
	t = (str[0]-'1');
	if (str[1]=='z')
	if (t<0 || t>6) return -1;
	else
	if (t<0 || t>8) return -1;
	
	return t+p;
}

Pai Tools::str2pai(char *spai,Bakyou *b)
{
  Pai tmp_pai,last_pai;
  int i,j, e=-1, l, t, last, lastaka=0;
  int p_base,p,cnt;
  int h[3] = {0,0,0};
  int c[34];
  b->tehai.clear();
  for (i=0;i<34;++i){
    c[i]=0;
	b->c34[i]=0;
  }
  l = strlen(spai);
  for(i=l-1;i>=0;i--) {
    if      (spai[i]=='m') e=0;
    else if (spai[i]=='p') e=1;
    else if (spai[i]=='s') e=2;
    else if (spai[i]=='z') e=3;
    else if (spai[i]>='0' && spai[i]<='9') {
      if (e==-1) error->all(FLERR,"Bad String");
      t=spai[i]-'0';
      if (t==0) {
        if (e>=3) error->all(FLERR, "BAD String");
        if (h[e]==0) {
          ++h[e];t=5;
          if (i==l-2)
            lastaka=1;
        }
        else error->all(FLERR, "Too many 0 in string");
      }
      if (t==5 && h[e]==0 && c[t*9+1]==3) error->all(FLERR,"no aka bug");
      t+=e*9-1;
      if (t>33) error->all(FLERR,"Illegal string");
      if (c[t]<4) ++c[t]; else error->all(FLERR,"too many same pai");
      if (i==l-2) last=t;
    }
  }

  cnt=count34(c);
  printf("number tehai = %d\n",cnt);
  last_pai.pai_c = last;
  last_pai.pai_aka = lastaka;
  last_pai.pai_str = c2str(last,lastaka);
  last_pai.pai_id = last*4 + c[last] - 1;
  if (last%9==4)
    if (lastaka) last_pai.pai_id = last*4;
    else last_pai.pai_id = last_pai.pai_id - h[last/9] + 1;
  for (i=0;i<34;++i){
  	b->c34[i]=c[i];
    p_base = i<<2;
    if (i%9==4 && h[i/9]==0) ++p_base;   // skip aka
    for (j=0;j<c[i];++j)
    {
      p = p_base + j;
      tmp_pai.pai_id = p;
      tmp_pai.pai_c = i;
      tmp_pai.pai_aka = game->game_info.is_aka[p];
      tmp_pai.pai_str = c2str(i,tmp_pai.pai_aka);
      if (tmp_pai.pai_id!=last_pai.pai_id || cnt%3!=2)
        b->tehai.push_back(tmp_pai);
    }
  }
  if (b->tehai.size()>14) error->all(FLERR, "Too many tehai.");
  b->cur_pai = last_pai;
  if (cnt%3==2)
  	b->tehai.push_back(last_pai);
  return last_pai;
}

int Tools::count34(int c34[])
{
  int cnt = 0;
  for(int i=0;i<34;++i)
    cnt += c34[i];
  return cnt;
}

int Tools::count_19(int c[])
{
	return (c[0]>0)+(c[8]>0)+(c[9]>0)+(c[17]>0)+(c[18]>0)+(c[26]>0)+(c[27]>0)+
	       (c[28]>0)+(c[29]>0)+(c[30]>0)+(c[31]>0)+(c[32]>0)+(c[33]>0);
}

int Tools::is_19z(int k)
{
	return (k==0)+(k==8)+(k==9)+(k==17)+(k==18)+(k==26)+(k==27)+
			(k==28)+(k==29)+(k==30)+(k==31)+(k==32)+(k==33);
}
