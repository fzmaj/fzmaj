#include "stdio.h"
#include "stdlib.h"
#include "game.h"
#include "ai.h"
#include "style_ai.h"
#include "error.h"
#include "memory.h"
#include "tools.h"

#include "random_mars.h"
#include <functional>
#include <algorithm>


#define DEBUG_GAME 1

using namespace std;
using namespace FZMAJ_NS;

Game::Game(FZMAJ *maj) : Pointers(maj) {
	// allocate memory and initialize varibles
	int i;
	random = NULL;
	for(i=0;i<4;++i)
		ai[i] = NULL;


	ai_map = new std::map<std::string,AICreator>();

	tehai.resize(4);
	river.resize(4);
	naki.resize(4);

	req_bak.river.resize(4);
	req_bak.naki.resize(4);
	req_bak.dora.clear();
	req_bak.ura.clear();
	req_bak.tehai.clear();

	for(i=0;i<NUM_ACT;++i)
		req_bak.act_list[i]=0;

#define AI_CLASS
#define AIStyle(key,Class) \
  (*ai_map)[#key] = &ai_creator<Class>;
#include "style_ai.h"
#undef AIStyle
#undef AI_CLASS

	create_ai("player", 0);
	create_ai("tsumogiri",1);
	create_ai("tsumogiri",2);
	create_ai("tsumogiri",3);
}

Game::~Game(){
	delete ai_map;
	for (int i=0;i<4;++i)
		delete ai[i];

}

void Game::game_start(long s)
{
	int i;
	game_info.seed = s;
	random = new RanMars(maj,s);

	for(i=0;i<4;++i)
		if (ai[i]) printf("ai %d is %s.\n",i,ai[i]->style);
		else {printf("ai %d is empty.\n",i);
		error->all(FLERR, "not enough ai");}

	game_loop();

}

void Game::game_loop()
{

	initialize();
	start_kyoku();

	tsumoru();
	request_ai(cur_pos);
}

int Game::start_kyoku()
{
	int i;

	// 1. clear status

	for(i=0;i<4;++i){
		junmoku[i]=0;

	}
	game_status = STATUS_IDLE;
	ura_check = 0;

	printf("start %s %d kyoku\n",CHA_NAME[game_info.bafuu], game_info.kyoku+1);

	// 2. shuffle
	
	for(i=0;i<4;++i){
		tehai[i].clear();
		river[i].clear();
		naki[i].clear();
	}
	rand_int(136,yama);
	pai_ptr = 0;
	clear_dora();
	add_dora();

	// 2. fapai 13*4

	draw();

	for(i=0;i<4;++i){
		sort_tehai(i);
		debug_print_tehai(i);
	}

	// 3. set oya

	cur_pos = oya;
}

int Game::initialize()
{
	int i;

	// 1. select oya and position

	rand_int(4,game_info.ai_pos);
	game_info.hajioya = game_info.ai_pos[0];
	rand_int(4,game_info.ai_pos);
	
	// 2. set original score

	for(i=0;i<4;++i)
	{
		game_info.score[i] = 25000;
	}

	// 3. clear game info

	game_info.kyoku = 0;
	game_info.bafuu = 0;
	game_info.honba = 0;
	game_info.residue = 0;
	oya = game_info.hajioya;
	for(i=0;i<136;++i)
		game_info.is_aka[i]=0;
	game_info.is_aka[16]=1;
	game_info.is_aka[52]=1;
	game_info.is_aka[88]=1;

	if (screen) fprintf(screen, "Game initialization done.\n");
	if (screen) fprintf(screen, "seed = %d\n",game_info.seed);
	return 1;
}

void Game::tsumoru()
{
	set_pai(&tsumo_pai,pai_ptr);
	tehai[cur_pos].push_back(tsumo_pai);
	++pai_ptr;
	game_status = STATUS_TSUMORU;
	printf ("pos %d (ai %d) mo %s\n",cur_pos,game_info.ai_pos[cur_pos],tsumo_pai.pai_str.c_str());
}

void Game::set_bakyou(int pos)
{
	int i,p;
	Bakyou *b = &req_bak;

	b->bafuu = game_info.bafuu;
	b->jifuu = (b->bafuu+pos-oya)%4;
	b->kyoku = game_info.kyoku;
	b->honba = game_info.honba;
	b->residue = game_info.residue;

	b->oya = oya;

	b->n_dora = n_dora;
	b->ura_check = ura_check;
	
	b->dora = dora;
	if (ura_check)
		b->ura = ura;
	b->dora_hyouji = dora_hyouji;
	b->pai_ptr = pai_ptr;
	b->pai_left = dead_ptr - pai_ptr;

	b->tehai = tehai[pos];

	for (i=0;i<4;++i) {
		p = (i-pos+4)%4;
		b->score[i] = game_info.score[p];
		b->rank[i] = game_info.rank[p];
		b->river[i] = river[p];
		b->naki[i] = naki[p];
	}

	for(i=0;i<34;++i)
		b->c34[i]=0;
	for(i=0;i<tehai[pos].size();++i)
		++b->c34[tehai[pos][i].pai_c];

	b->n_tehai=tools->count34(b->c34);
}

void Game::count_c(int pos)
{
	int i;
	for(i=0;i<34;++i)
		tehai_c[pos][i]=0;
	for(i=0;i<tehai[pos].size();++i)
		++tehai_c[pos][tehai[pos][i].pai_c];
}

int Game::ankan_able(int pos)
{
	if (pai_ptr+1>=dead_ptr) return 0;
	return tehai_c[pos][tsumo_pai.pai_c]==3;
}

int Game::kakan_able(int pos)
{
	int i,k;
	k=0;
	for(i=0;i<naki[pos].size();++i)
		if (naki[pos][i].naki_type==0 && naki[pos][i].naki_pai[0].pai_c==tsumo_pai.pai_c){
			k=1;
			break;}
	return k;
}

int Game::nagashi_able(int pos)
{
	if (junmoku[pos]!=0) return 0;
	 tools->count_19(tehai_c[pos])>=9;
}

void Game::request_ai(int pos)
{
	int i,ask;
	req_pos = pos;
	Bakyou *b = &req_bak;
	set_bakyou(pos);

	for(i=0;i<NUM_ACT;++i)
		act_list[i]=0;

	if(pos==cur_pos){
		if (game_status==STATUS_TSUMORU){
			ask = 0;	
			if (ankan_able(pos)) {act_list[ACT_ANKAN]=1; b->act_list[ACT_ANKAN]=1;ask=1;}
			if (kakan_able(pos)) {act_list[ACT_KAKAN]=1; b->act_list[ACT_KAKAN]=1;ask=1;}
			if (nagashi_able(pos)) {act_list[ACT_NAGASHI_99]=1; b->act_list[ACT_NAGASHI_99]=1;ask=1;}
			if (ask){
				b->game_status = game_status;
				act_list[ACT_CANCEL]=1;
				b->act_list[ACT_CANCEL]=1;
				default_act=ACT_CANCEL;
				default_argout=0;
				b->default_act=default_act;
				b->default_argout=default_argout;
				ai[game_info.ai_pos[pos]]->request(b);
			} else {
				game_status=STATUS_KIRU;
			}
		}

		if (game_status==STATUS_KIRU){
			b->act_list[ACT_TSUMOGIRI]=1;
			b->act_list[ACT_TEKIRI]=1;
			act_list[ACT_TSUMOGIRI]=1;
			act_list[ACT_TEKIRI]=1;
			b->game_status = game_status;
			b->default_act = default_act = ACT_TSUMOGIRI;
			b->default_argout = default_argout = b->tehai.size();
			ai[game_info.ai_pos[pos]]->request(b);
		}
	}

}

void Game::rand_int(int n, int res[])
{
	int i,j,tmpi;
	double a[n], tmpd;
	for(i=0;i<n;++i) {
		res[i]=i;
		a[i]=random->uniform();
	}

	for(i=0;i<n-1;++i){
		for(j=0;j<n-i-1;++j){
			if(a[j]>a[j+1]){
				tmpd=a[j];
				a[j]=a[j+1];
				a[j+1]=tmpd;
				
				tmpi=res[j];
				res[j]=res[j+1];
				res[j+1]=tmpi;
			}
		}
	}
}

void Game::draw()
{
	int i,j,k,p,c0;
	Pai pai_tmp;

	for (i=0;i<3;++i)
		for(j=0;j<4;++j){
			p=(j+oya)%4;
			for(k=0;k<4;++k){
				c0 = yama[pai_ptr+k];
				set_pai(&pai_tmp,c0);
				tehai[p].push_back(pai_tmp);
			}
			pai_ptr += 4;
		}
	for (i=0;i<4;++i){
		p = (i+oya)%4;
		c0 = yama[pai_ptr+i];
		set_pai(&pai_tmp,c0);
		tehai[p].push_back(pai_tmp);
	}
	pai_ptr += 4;
}

void Game::deal_act(int act, int argout)
{
	// check illegal act

	if (act_list[act]==0) {

		printf("ai %d act illegal. Act default\n");
	}
}

void Game::set_pai(Pai* pai, int idx)
{
	pai->pai_id = idx;
	pai->pai_c = idx>>2;
	pai->pai_aka = game_info.is_aka[idx];
	pai->pai_str = tools->c2str(pai->pai_c,pai->pai_aka);
}

int Game::set_dora(int id)
{
	int c,d;
	c=id>>2;
	if (c>=31) d=(c-30)%3+31;
	else if (c>=27) d=(c-26)%4+27;
	else if (c>=18) d=(c-17)%9+18;
	else if (c>=9) d=(c-8)%9+9;
	else d=(c+1)%9;
	return d;
}

void Game::clear_dora()
{
	n_dora = 0;
	dora.clear();
	ura.clear();
	dora_hyouji.clear();
	dead_ptr = 122;
}

void Game::add_dora()
{
	int d,dh,u,uh;
	Pai pai_tmp;
	++n_dora;
	dh = yama[132-n_dora*2];
	uh = yama[133-n_dora*2];
	d=set_dora(dh);
	u=set_dora(uh);
	set_pai(&pai_tmp,dh);
	dora_hyouji.push_back(pai_tmp);
	dora.push_back(d);
	ura.push_back(u);
	--dead_ptr;
}

bool sort_by_id(const Pai& p1, const Pai& p2) { return p1.pai_id < p2.pai_id;}

void Game::sort_tehai(int pos)
{
	sort(tehai[pos].begin(),tehai[pos].end(),sort_by_id);
}

void Game::debug_print_tehai(int pos)
{
	printf ("tehai %d: " , pos);
	for (int i=0;i<tehai[pos].size();++i)
		printf(" %s ",tools->c2str(tehai[pos][i].pai_c,tehai[pos][i].pai_aka).c_str());
	printf("\n");
}

void Game::create_ai(const char *style, int pos)
{
    if (pos>3) error->all(FLERR,"AI position should be 0~3");
	if (ai[pos]) delete ai[pos];
	ai[pos] = new_ai(style);
	ai[pos]->pos_me = pos;
	int n = strlen(style)+1;
	ai[pos]->style = new char[n];
	strcpy(ai[pos]->style, style);
}

AI *Game::new_ai(const char *style)
{
	if (!strcmp(style, "none")) return NULL;
	if (ai_map->find(style) != ai_map->end()) {
		AICreator ai_creator = (*ai_map)[style];
		return ai_creator(maj);
	}

	error->all(FLERR, "Invalid ai style");
	return NULL;
}

template <typename T>
AI *Game::ai_creator(FZMAJ *maj)
{
	return new T(maj);
}


