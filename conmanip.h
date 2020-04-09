//escape sequences for console manipulators

#include <string> 
using namespace std;

//text editors
string red = "\033[0;31m";
string bold = "\x1B[1m";
string def_txt = "\x1B[0m";

//clear screen
string clrscrn = "\033[2J\033[1;1H";
