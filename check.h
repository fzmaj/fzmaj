#ifdef COMMAND_CLASS

CommandStyle(check,Check)

#else

#ifndef MAJ_CHECK_H
#define MAJ_CHECK_H

#include "pointers.h"

namespace FZMAJ_NS {

class Check : protected Pointers {
	public:
		Check(class FZMAJ *);
		void command(int, char **);
    protected:
        void set_empty_bakyou();
		void help();
        Bakyou bak;
};

}

#endif
#endif
