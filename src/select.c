#include "ft_select.h"

int             ft_select(int ac, char **av)
{
    t_select    *catalog;
    t_term      display;
	
//signal
	ft_bzero(&display, sizeof(t_term));
	catalog = NULL;
	ft_term_decribe(&display);
    fill_catalog(&catalog, ac, av);
	init_tty(&display);
	reset_tty(&display);
	close(display.fd);
	t_select *curs;
	curs = catalog;
	while (catalog->last == false)
	{
				curs = catalog;
				catalog = catalog->next;
				free(curs);
	}
	free(catalog);
    return (0);
}