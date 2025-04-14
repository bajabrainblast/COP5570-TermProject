demo:
    to show caps ignore correctness, run the following commands
    ./multigrep.out -f lorem -p "The"
    ./multigrep.out -f lorem -p "The" -c

    to show ignore character correctness, run the following commands
    ./multigrep.out -f lorem -p "masterbuilder"
    ./multigrep.out -f lorem -p "masterbuilder" -i "-"