#include "ft_select.h"

int             main(int ac, char **av)
{
    //signals
    if (ac < 2)
        handle_errors("usage: at least one argument required\n");
    ft_select(ac - 1, av + 1);
   // close(fd);
    return (0);
}
