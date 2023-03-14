very old linux select implementation.
1 main
    a) check for ac
    b) check for empty args(empty string) check_empty_argc
    c) signal handlers
    d) init struct with data(num of args, rows, cols, fitst, last,)
    e) init term data: 
        1) check for getenv("TERM")
        2) check for tgetent("termname")
        3) save termios struct twice. 0 fd. 
        4) ICANON and ECHO flas int termios struct
        5) VMIN and VTIME termios struct
        6) set terminal params(termios) 
