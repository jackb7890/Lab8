#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>

#ifndef fnameFinder
#define fnameFinder
using namespace std;

/*function... might want it in some class?*/
int getdir (string dir, vector<string> &files);
#endif
