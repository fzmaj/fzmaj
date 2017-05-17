#ifndef MAJ_TOOLS_H
#define MAJ_TOOLS_H

#include "pointers.h"
#include "string.h"
#include <vector>
#include "defs.h"

namespace FZMAJ_NS {

class Tools : protected Pointers {
public:

	Tools(FZMAJ *maj);
	~Tools();

    string c2str(int,int);
	int str2c(string,int&);
    Pai str2pai(char *, Bakyou *);
	Pai create_pai_from_c(int,int);

/*
    void pai2c34(vector<Pai>, int[]);
*/
    int count34(int[]);

	int count_19(int[]);
	int is_19z(int );

};

}

#endif
