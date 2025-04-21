#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "mg_structures.hpp"

using namespace std;

#define DEBUG 1
#define DPRINT(str) if (DEBUG) { fprintf(stderr, str); fflush(0); }
#define DIPRINT(i) if (DEBUG) { sprintf(DTMP, "%d", i); fprintf(stderr, DTMP); fflush(0); }
char DTMP[1000];

vector<string> files;
vector<mg_find> finds;
extern vector<mg_patt> patterns;
extern bool consider_caps;
extern vector<char> ignores;
extern bool line_numbers;
extern double fuzz;
extern bool parall_file;
extern bool parall_line;
extern bool parall_pattern;

int read_args(int argc, char *argv[], string *term) {
    int i, j;
    
    DPRINT("ARGC: "); DIPRINT(argc); DPRINT("\n");
    for (i = 1; i < argc; ) {        
        if (argv[i][0] != '-') return 1; /* flagless parameter */
        
        /* can assume there's a following non-flag term */
        if (!strcmp("-p", argv[i])) { 
            patterns.push_back(mg_patt(string(argv[i+1])));
            /* todo allow multiple patterns */
            i += 2;
        }
        else if (!strcmp("-f", argv[i])) {
            files.push_back(string(argv[i+1]));
            /* todo allow multiple files */
            i += 2;
        }
        else if (!strcmp("-t", argv[i])) {
            if ((*term) == "\n")
                (*term) = string(argv[i+1]);
            else
                return 4; /* multiple terminators */
            /* todo allow multiple terminators? probably not */
            i += 2;
        }
        else if (!strcmp("-i", argv[i])) {
            /* todo fix this super unrobust */
            ignores.push_back(argv[i+1][0]);
            /* todo allow multiple ignores */
            i += 2;
        }
        else if (!strcmp("-c", argv[i])) {
            consider_caps = false;
            i += 1;
        }
        else if (!strcmp("-n", argv[i])) {
            line_numbers = true;
            i += 1;
        }
        else if (!strcmp("-z", argv[i])) {
            fuzz = atof(argv[i+1]);
            i += 2;
        }
        else if (!strcmp("-o", argv[i])) {
            j = atoi(argv[i+1]);
            if (j == 1)
                parall_file = true;
            if (j == 2)
                parall_line = true;
            if (j == 3)
                parall_pattern = true;
            if (DEBUG) {
                printf("pattern %d\nline %d\nfile %d\n", parall_pattern, parall_line, parall_file);
            }
            i += 2;
        }
    }

    if (DEBUG) {
        cout << "files: ";
        for (unsigned int j = 0; j < files.size(); j++)
            cout << files[j] << " | ";
        cout << endl << "patterns: ";
        for (unsigned int j = 0; j < patterns.size(); j++)
            cout << patterns[j] << " | ";
        cout << endl << "ignores: ";
        for (unsigned int j = 0; j < ignores.size(); j++)
            cout << ignores[j] << " | ";
        cout << endl;
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
    long unsigned int i;
    if ((i = read_args(argc, argv, &term)) != 0) {
        printf("Error %ld. Please follow this format when using multigrep:\n\t./multigrep.out -p (PATTERN) -f (FILE) -t (TERMINATOR)\n", i);
        return 1;
    }
    for (vector<string>::iterator fi = files.begin(); fi != files.end(); fi++) {
        ifstream f((*fi).c_str());
        if (!f.is_open())
            return 2; /* nonexistant file */
        i = 0;
        while (mygetline(&f, &line, &term) == 0) { /* while able to read in line */
            i++; /* incr line counter */
            /* handle that line */
            for (vector<mg_patt>::iterator pat = patterns.begin(); pat != patterns.end(); pat++) {
                if (pat->match(line)) 
                    finds.push_back(mg_find(line, *fi, i));
            }
        }
        f.close();
    }
    /* display finds */
    for (i = 0; i < finds.size(); i++)
        cout << finds[i] << endl;

    return 0;
}