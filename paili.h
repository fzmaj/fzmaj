#ifndef MAJ_PAILI_H
#define MAJ_PAILI_H

#include "pointers.h"
#include "defs.h"

namespace FZMAJ_NS {

class Paili : protected Pointers {

public:

  Paili(class FZMAJ *);
  ~Paili();


  void test(Bakyou*);

  int agari(Bakyou*);

private:
  void print_naki();
  class Yaku *yaku;

protected:
  Bakyou *bak;

  int test_agari_kata();


  bool is_mentsu(int);
  bool is_atama_mentsu(int,int);
  int cc2m(int[],int);

  int fan;
  int fu;
  int score;
  int score_ko;
  int score_oya;
  int agari_yaku[46];

  int n_syuntsu;
  int n_kotsu;
  int n_mentsu;
  int atama;
  int isatama;
  int kotsu[34];
  int syuntsu[34];
  int naki_kotsu[34];
  int naki_syuntsu[34];
  int n_naki_syuntsu;
  int n_naki_kotsu;
  int n_ankan;
  int n_naki_kan;

  vector<Pattern> pat;
  int n_pat;

  void d_kotsu(int k);
  void i_kotsu(int k);
  void d_syuntsu(int k);
  void i_syuntsu(int k);
  void d_atama(int k);
  void i_atama(int k);

  void remove_jihai();
  void toku_handan();
  void run_tehai(int);
  void update_result();
  void add_pat();
  void count_naki();

  int c[34];


};

}


#endif



