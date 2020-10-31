#include "ft_select.h"

int     ft_select(int ac, char **av)
{
    t_select    catalog[ac - 1];
    t_term      display;


    return (0);
}

int	main(int ac, char **av)
{
    int         fd;
    t_select    *catalog;
    //signals
    if (ac < 2)
    {
       // ft_putstr_fd("ft_select: usage: at least one argument required", 2);
        return (1);
    }
    else if (ft_select(ac - 1, av))
        return (1);
   // close(fd);
    return (0);
}
