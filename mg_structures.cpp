#include "mg_structures.hpp"
#include <regex>

std::vector<mg_patt> patterns;
bool consider_caps = true;
std::vector<char> ignores;
bool line_numbers = false;
double fuzz = 0;
bool parall_file = false;
bool parall_line = false;
bool parall_pattern = false;

/* ----- helpers ----- */
std::string mytolower(std::string *s) {
    std::string res = "";
    for (unsigned int i = 0; i < s->size(); i++)
        res.push_back(std::tolower((*s)[i]));
    return res;
}
std::string myignore(std::string *s) {
    std::string res = "";
    for (unsigned int i = 0; i < s->size(); i++) {
        unsigned int j;
        for (j = 1; j < ignores.size()+1; j++) {
            if (((*s)[i]) == ignores[j-1]) {
                j = 0;
                break;  /* if find an ignored char, set j to sentinel */
            }
        }
        if (j != 0)
            res.push_back((*s)[i]);
    }
    return res;
}

/* ----- mg find ----- */
mg_find::mg_find(std::string l, std::string f, int c) {
    line = l;
    file = f;
    linenum = c;
}
std::ostream& operator<<(std::ostream &os, const mg_find &mgf) {
    os << mgf.file;
    if (mgf.linenum != -1) 
        os << ":" << std::setw(4) << mgf.linenum; 
    os << " | " << mgf.line;
    return os;
}

/* ----- mg pattern ----- */
mg_patt::mg_patt() {
    original = "default";
    subpatterns.clear();
}
mg_patt::mg_patt(std::string s) {
    original = s;
    subpatterns.clear();
    /* todo populate subpatterns */
    subpatterns.push_back(s);
}
int mg_patt::match(std::string line) {
    /*
    std::string tline, tpatt;
    tline = !consider_caps ? mytolower(&line) : line; // if not considering caps, lowercase the line. else use normal line
    tline = myignore(&tline); // remove any ignored characters
    for (std::vector<std::string>::iterator x = subpatterns.begin(); x != subpatterns.end(); x++) {
        tpatt = !consider_caps ? mytolower(&(*x)) : (*x); // if not considering caps, lowercase the pattern. else use normal pattern
        if (tline.find(tpatt) != std::string::npos)
            return 1;
    }
*/
    std::regex pattern(original);
    std::smatch match_term;
    if (std::regex_search(line,match_term,pattern)) {
        std::cout << line << std::endl;
    }
    return 0;
}
std::ostream& operator<<(std::ostream &os, const mg_patt &mgp) {
    std::vector<std::string>::const_iterator x = mgp.subpatterns.begin();
    if (x != mgp.subpatterns.end()) {
        os << (*x);
        for (x++; x != mgp.subpatterns.end(); x++)
            os << " | " << *x;
    }
    return os;
}
