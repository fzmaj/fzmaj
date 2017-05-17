#ifndef MAJ_POINTERS_H
#define MAJ_POINTERS_H

#include "fzmaj.h"
#include "defs.h"

namespace FZMAJ_NS {

#define FLERR __FILE__,__LINE__

#define MIN(A,B) ((A) < (B) ? (A) : (B))
#define MAX(A,B) ((A) > (B) ? (A) : (B))


class Pointers {

public:
	Pointers(FZMAJ *ptr) :
		maj(ptr),
		memory(ptr->memory),
		error(ptr->error),
		input(ptr->input),
		tools(ptr->tools),
		paili(ptr->paili),

		game(ptr->game),

		infile(ptr->infile),
		screen(ptr->screen),
		logfile(ptr->logfile) {}
	virtual ~Pointers() {}

protected:
	
	FZMAJ *maj;
	Memory *&memory;
	Error *&error;
	Input *&input;
	Tools *&tools;
	Paili *&paili;
	Game *&game;

	FILE *&infile;
	FILE *&logfile;
	FILE *&screen;
};

}

#endif
