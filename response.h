const char* VERSION = "0.0.2";
const char* HELP = "Pathfinder provides a set of portable filesystem utilities.\n"
"\n"
"  Usage:\n"
"    pf -h                       get the text you are currently reading\n"
"    pf -h <command>             get info of a particular command (e.g. pf -h s)\n"
"    pf -v                       get version number\n"
"    pf <command> <flags...>     run command\n"
"\n";

const char* HELP_LOCATE = "Locate up to <max_matches> files matching <target> by <mode>(-f: filename || -x: extension) in <search_path>\n"
"\n"
"  Usage:\n"
"    pf l <target> <search_path> <max_matches> <mode>\n"
"\n"
"  Example:\n"
"    pf l .cpp ~/Desktop 256 -x\n";
const char* HELP_SPLICE = "Splice at directory--Under construction!"; // TODO: complete this help texts