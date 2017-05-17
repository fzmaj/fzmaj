#ifndef MAJ_GAME_H
#define MAJ_GAME_H

#include "pointers.h"
#include <vector>
#include <string>
#include <map>
#include "string.h"

//#define GAME_DEBUG

using namespace std;

namespace FZMAJ_NS {

struct GameInfo {
	long seed;
	int score[4];
	int rank[4];

	int bafuu;
	int kyoku;
	int honba;
	int residue;

	int hajioya;

	int ai_pos[4];
	int is_aka[136];
};

class Game : protected Pointers {
public:


	Game(class FZMAJ *);
	~Game();

	class AI *ai[4];
	char *ai_style;
	typedef AI *(*AICreator)(FZMAJ *);
	void create_ai(const char*, int);
	std::map<std::string,AICreator> *ai_map;
	class AI *new_ai(const char *);

	void game_start(long);

	void deal_act(int, int);

	GameInfo game_info;

private:

	void game_loop();

	int initialize();
	int start_kyoku();
	void tsumoru();
	void request_ai(int);


	void rand_int(int, int[]);
	void set_pai(Pai*, int idx);
	int set_dora(int);
	void clear_dora();
	void add_dora();
	void draw();

	void set_bakyou(int pos);

	void sort_tehai(int pos);

	int tsumo_able(int pos);
	int ron_able(int pos);
	int chii_able(int pos);
	int pon_able(int pos);
	int minkan_able(int pos);
	int ankan_able(int pos);
	int kakan_able(int pos);
	int reach_able(int pos);
	int nagashi_able(int pos);
	
	int default_act;
	int default_argout;

	void debug_print_tehai(int pos);

	class RanMars *random;
	struct Bakyou req_bak;

	void count_c(int pos);

	int cur_pos;
	int req_pos;
	int game_status;

protected: // AI BU NENG ZUO BI


	int yama[136];

	vector< vector<Pai> > tehai;
	vector< vector<River> > river;
	vector< vector<Naki> > naki;

	int tehai_c[4][34];

	int oya;
	int pai_ptr;
	int dead_ptr;
	int n_dora;

	int ura_check;

	int junmoku[4];

	int act_list[NUM_ACT];

	vector<int> dora;

	vector<int> ura;
	vector<Pai> dora_hyouji;

	Pai tsumo_pai;

	template <typename T> static AI *ai_creator(FZMAJ *);

};

}

#endif
