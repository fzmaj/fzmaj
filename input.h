#ifndef MAJ_INPUT_H
#define MAJ_INPUT_H

#include "stdio.h"
#include "pointers.h"
#include <string>
#include <map>

namespace FZMAJ_NS {

class Input : protected Pointers {
public:
	int narg;
	char **arg;

	Input(class FZMAJ *, int, char**);
	~Input();

	void file();
	void file(const char *);

	typedef void (*CommandCreator) (FZMAJ *, int, char**);
	typedef std::map<std::string,CommandCreator> CommandCreatorMap;
	CommandCreatorMap *command_map;
private:
	char *command;
	int maxarg;
	char *line, *copy, *work;
	int maxline, maxcopy, maxwork;
	int nfile;



	void parse();
	char *nextword(char *, char **);
	void reallocate(char *&, int &,int);
	int execute_command();

	void run_test(); // FZMAJ Commands
	void q(); // Quit
	void ai_style();


	class RanMars *rantest;

protected:
	template <typename T> static void command_creator(FZMAJ *, int, char**);

};

}

#endif
