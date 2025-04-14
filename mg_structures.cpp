#include "mg_structures.hpp"

/* ----- mg find ----- */
mg_find::mg_find() {
    line = "default";
    file = "default";
}
mg_find::mg_find(std::string l, std::string f) {
    line = l;
    file = f;
}
std::ostream& operator<<(std::ostream &os, const mg_find &mgf) {
    os << mgf.file << " | " << mgf.line;
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
    for (std::vector<std::string>::iterator x = subpatterns.begin(); x != subpatterns.end(); x++) {
        if (line.find((*x)) != std::string::npos)
            return 1;
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