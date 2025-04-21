flags:
    -p {PATTERN}        |   specify word / regex searching for here
    -f {FILE}           |   specify files to search in here
    -t {TERMINATOR}     |   specify terminating character for lines (default \n)
    -i {IGNORECHAR}     |   specify characters to ignore
    -c                  |   disable capitalization check
    -n                  |   enable line numbers
    -z {FUZZPERCENT}    |   specify fuzz level. .75 would allow "wood" to match search "dood".
    -o {OPTLEVEL}       |   specify parallelization level. 1 parallelizes by file, 2 by line, and 3 by pattern. 
demo:
    to show caps ignore correctness, run the following commands
    ./multigrep.out -f lorem -p "The"
    ./multigrep.out -f lorem -p "The" -c

    to show ignore character correctness, run the following commands
    ./multigrep.out -f lorem -p "masterbuilder"
    ./multigrep.out -f lorem -p "masterbuilder" -i "-"