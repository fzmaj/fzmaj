#ifndef MAJ_DEFS_H
#define MAJ_DEFS_H

#define PI 3.1415926535897932384626

#define mio "old"

#include <vector>
#include <string>

using namespace std;

struct Pai {
  string pai_str;
  int pai_id; //136
  int pai_c; //34
  int pai_aka; // 1 for aka, 0 for others
};

struct Naki {
  int naki_type; // 0: pon  1: chii  2: ankan  3: minkan  4: kakan
  Pai naki_pai[4];
  int naki_id; //  which pai is naki pai
  int naki_from;  // naki from where, 0 for ankan
  int naki_num; // number of naki pai
};

struct River {
  Pai river_pai;
  int river_junmoku;
  int river_stat;
};

enum NAKI_TYPE {
	
	NAKI_PON =0,
	NAKI_CHII,
	NAKI_ANKAN,
	NAKI_MINKAN,
	NAKI_KAKAN
};

enum ACT {

  ACT_CANCEL = 0,          
  ACT_TSUMOGIRI,          
  ACT_TEKIRI,            
  ACT_AGARI_TSUMO,
  ACT_AGARI_RON,
  ACT_CHII,
  ACT_PON,
  ACT_MINKAN,
  ACT_ANKAN,
  ACT_KAKAN,
  ACT_REACH,
  ACT_NAGASHI_99,
  ACT_ADMIN_QUIT,
  NUM_ACT

};

const char act_name[NUM_ACT][32]=
{
	{"cancel"},
	{"tsumogiri"},
	{"tekiri"},
	{"agari_tsumo"},
	{"agari_ron"},
	{"chii"},
	{"pon"},
	{"minkan"},
	{"ankan"},
	{"kakan"},
	{"reach"},
	{"nagashi_99"},
	{"quit"}
};

enum GAME_STATUS {

	STATUS_IDLE = 0,
	STATUS_TSUMORU,
	STATUS_KIRU,
	STATUS_NAKI,
	STATUS_KAKAN,
	STATUS_RINSHAN,

	NUM_STATUS
};

struct Bakyou {

  int bafuu;
  int jifuu;
  int kyoku;
  int honba;
  int residue;
  int oya;
  int score[4];
  int rank[4];

  int n_dora;
  vector<int> dora;
  int ura_check;
  vector<int> ura;
  vector<Pai> dora_hyouji;
  int pai_ptr;
  int pai_left;

  vector<Pai> tehai;

  int n_tehai;
  int c34[34];

  vector< vector<River> > river;
  vector< vector<Naki> > naki;
  int n_naki[4];

  int junmoku[4];
  int reach_jun[4];
  int furiten;

  Pai cur_pai;
  int cur_pos;
  int pos_me;

  int act_list[NUM_ACT];

  int default_act;
  int default_argout;
  int game_status;

};

struct Pattern {

  int c[34];
  int cc[34];
  int score;
  int score_oya;
  int score_ko;

  int fan, fan_nodora;
  int fu,fu_tmp;
  int yaku[46];

  int is_chiitoi;
  int is_kokushi;

  int is_yakuman;
  int yakuman_baisu;

  int n_naki;
  int n_kan;
  int n_ankan;
  int n_syuntsu;
  int n_kotsu;
  int n_naki_syuntsu;
  int n_naki_kotsu;
  int syuntsu[34];
  int kotsu[34];
  int naki_syuntsu[34];
  int naki_kotsu[34];
  int atama;

};

const char CHA_NAME[4][4]={
	{"Ton"},
	{"Nan"},
	{"Sya"},
	{"Pei"}
};


#endif
