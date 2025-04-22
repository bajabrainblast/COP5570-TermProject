#ifndef MG_STRUCTURES
#define MG_STRUCTURES

#include <string>
#include <vector>
#include <iostream>
#include <cctype>
#include <iomanip>

class mg_find;
class mg_patt;

class mg_find {
    public:
        mg_find(std::string l = "default_line", std::string f = "default_file", int c = -1);
        friend std::ostream& operator<<(std::ostream &os, const mg_find &mgf);
    private:
        std::string line;
        std::string file;
        int linenum;
};

class mg_patt {
    public:
        mg_patt();
        mg_patt(std::string s);
        int match(std::string line);
        int match_mpi(std::string line);
        int match_mpi_first_line(std::string line);
        friend std::ostream& operator<<(std::ostream &os, const mg_patt &mgp);
    private:
        std::string original;
        std::vector<std::string> subpatterns;
};

#endif
