#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cstdio>

using namespace std;

#define DEBUG 1
#define DPRINT(str) if (DEBUG) { fprintf(stderr, str); fflush(0); }
#define DIPRINT(i) if (DEBUG) { sprintf(DTMP, "%d", i); fprintf(stderr, DTMP); fflush(0); }

char DTMP[1000];

vector<string> patterns;
vector<string> files;

int read_args(int argc, char *argv[], string *term) {
    int i;
    
    DPRINT("ARGC: "); DIPRINT(argc); DPRINT("\n");
    for (i = 1; i < argc; i += 2) {
        DPRINT("FOUND "); DPRINT(argv[i]); DPRINT("\n");
        
        if (argv[i][0] != '-') return 1; /* flagless parameter */
        else if (i + 1 == argc) return 2; /* unmatched -p */
        else if (argv[i+1][0] == '-') return 3; /* flag followed by flag */
        
        /* can assume there's a following non-flag term */
        if (!strcmp("-p", argv[i])) 
            patterns.push_back(string(argv[i+1]));
        else if (!strcmp("-f", argv[i]))
            files.push_back(string(argv[i+1]));
        else if (!strcmp("-t", argv[i])) {
            if ((*term) == "\n")
                (*term) = string(argv[i+1]);
            else
                return 4; /* multiple terminators */
        }
    }

    if (patterns.size() == 0 || files.size() == 0)
        return 9; /* didnt find anything */

    return 0;
}

int mygetline(ifstream *f, string *res, string *term) {
    char ch;
    res->clear();
    while (f->get(ch)) {
        res->push_back(ch);
        if (res->size() >= term->size() && res->substr(res->size() - term->size()) == (*term)) {
            res->erase(res->size() - term->size());
            return 0;
        }
    }
    if (!res->empty())
        return 0;
    return f->eof();
}

int main(int argc, char *argv[]) {
    string line;
    string term = "\n";
    int i;
    if ((i = read_args(argc, argv, &term)) != 0) {
        printf("Error %d. Please follow this format when using multigrep:\n\t./multigrep.out -p (PATTERN) -f (FILE) -t (TERMINATOR)\n", i);
        return 1;
    }
    if (DEBUG) {
        fprintf(stderr, "PATTERNS:\n");
        for (long unsigned int i = 0; i < patterns.size(); i++)
            fprintf(stderr, "\t%s\n", patterns[i].c_str());
        fprintf(stderr, "FILES:\n");
        for (long unsigned int i = 0; i < files.size(); i++)
            fprintf(stderr, "\t%s\n", files[i].c_str());
    }
    for (vector<string>::iterator fi = files.begin(); fi != files.end(); fi++) {
        ifstream f((*fi).c_str());
        if (!f.is_open())
            return 2; /* nonexistant file */
        while (mygetline(&f, &line, &term) == 0) { /* while able to read in line */
            /* handle that line */
            DPRINT("LINE "); DPRINT(line.c_str()); DPRINT("\n");
        }
        f.close();
    }

    return 0;
}