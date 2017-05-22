#ifndef MAJ_AI_H
#define MAJ_AI_H

#include "pointers.h"
#include <string>

namespace FZMAJ_NS {

class AI : protected Pointers {

public:

    int pos_me;
    char* style;

    AI(class FZMAJ *);
    virtual ~AI();

    virtual void request(Bakyou*) = 0;
    void return_act(int,int);

};

}
#endif
