#include "ft_select.h"

static int      ft_term_decribe(void)
{
    char    buf[2048];
    char    *term_type;
    int     result;

    term_type = getenv("TERM");
    if (!term_type)
        handle_errors("\nSpecify a terminal type with setenv\n");
    result = tgetent(buf, "TERM");
    if (result < 0)
        handle_errors("Could not access the termcap data base\n");
    if (!result)
        handle_errors("Terminal type is not defined\n");
}


static void     fill_catalog(t_select *catalog, int ac, char **av)
{
	int     index;

    index = 0;
    while (index < ac)
    {
        catalog[index].len = ft_strlen(av[i]);
        catalog[index].name = av[i];
        catalog[index].hidden = false;
        catalog[index].current = false;
        catalog[index].chosen = false;
        if (index + 1 == ac)
            catalog[index].last = true;
        else
            catalog[index].last = false;
        index++;
    }
}


int             ft_select(int ac, char **av)
{
    t_select    catalog[ac - 1];
    t_term      display;

    fill_catalog(catalog, ac);
    return (0);
}

int             main(int ac, char **av)
{
    //signals
    if (ac < 2)
        handle_errors("usage: at least one argument required\n");
    ft_select(ac - 1, av);
   // close(fd);
    return (0);
}
