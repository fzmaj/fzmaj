#ifndef MAJ_RANMARS_H
#define MAJ_RANMARS_H

#include "pointers.h"

namespace FZMAJ_NS {

class RanMars : protected Pointers {
 public:
  RanMars(class FZMAJ *, int);
  ~RanMars();
  double uniform();
  double gaussian();

 private:
  int save;
  double second;
  double *u;
  int i97,j97;
  double c,cd,cm;
};

}

#endif
