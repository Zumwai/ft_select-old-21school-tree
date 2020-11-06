#include "ft_select.h"

static void		interrogate_term(t_term *conf)
{
	conf->columns = tgetnum("co");
	conf->rows = tgetnum("li");
	conf->standout = tgetstr("so", NULL);
	conf->normal = tgetstr("se", NULL);
	conf->clear = tgetstr("cl", NULL);
	conf->cursor_begin = tgetstr("te", NULL);
	conf->cursor_move = tgetstr("cm", NULL);
	conf->cursor_visible = tgetstr("ve", NULL);
	conf->cursor_home = tgetstr("ho", NULL);
	conf->cursor_half = tgetstr("hd", NULL);
	conf->cursor_down = tgetstr("do", NULL);
	conf->cursor_key_d = tgetstr("kd", NULL);
	conf->cursor_key_l = tgetstr("kl", NULL);
	conf->cursor_key_r = tgetstr("kr", NULL);
	conf->cursor_key_u = tgetstr("ku", NULL);
	conf->underlining = tgetstr("us", NULL);
	conf->cursor_hide = tgetstr("vi", NULL);
	conf->cursor_end = tgetstr("te", NULL);
	conf->cursor_start = tgetstr("ti", NULL);
	conf->end_modes = tgetstr("me", NULL);
	conf->clear_all = tgetstr("cd", NULL);
	conf->reverse = tgetstr("mr", NULL);
	conf->allow_move = tgetflag("ms");
}


static void      ft_term_decribe(t_term *config)
{
    char    *term_type;
    int     result;

	config->fd = open(ttyname(STDIN_FILENO), O_RDWR); //O_NOCTTY
	if (!isatty(config->fd))
		handle_errors("Not a terminal");
    config->tty_type = getenv("TERM");
    if (!config->tty_type)
        handle_errors("Specify a terminal type with setenv\n");
    result = tgetent(NULL, config->tty_type);
    if (result < 0)
        handle_errors("Could not access the termcap data base\n");
    if (!result)
        handle_errors("Terminal type is not defined\n");
}

static void     fill_catalog(t_select **catalog, int ac, char **av)
{
	t_select	*curs;
	t_select	*head;
	int         index;

    index = 0;

	curs = create_node(av[index++]);
	curs->current = true;
	curs->prev = NULL;
	(*catalog) = curs;
    while (index < ac)
    {
		curs->next = create_node(av[index]);
		curs->next->prev = curs;
		curs = curs->next;
        index++;
    }
	//(*catalog)->prev = new;
	//new->next = (*catalog);
	curs->last = true;
}

void	init_tty(t_term *config)
{
	tcgetattr(STDIN_FILENO, &(config->tattr));
	tcgetattr(STDIN_FILENO, &(config->old_tattr));
	config->tattr.c_lflag &= ~(ICANON | ECHO);
//	config->tattr.c_oflag &= ~(OPOST);
	config->tattr.c_cc[VMIN] = 1;
	//tattr.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &(config->tattr));
	tputs(tgetstr("ti", NULL), 1, ft_printnbr);
	tputs(tgetstr("vi", NULL), 1, ft_printnbr);
}

int             ft_select(int ac, char **av)
{
    t_select    *catalog;
    t_term      display;
	
//signal
	ft_bzero(&display, sizeof(t_term));
	catalog = NULL;
	ft_term_decribe(&display);
	interrogate_term(&display);
//	ft_putstr_fd(display.clear, display.fd);
	ft_putstr_fd(display.cursor_hide, display.fd);
    fill_catalog(&catalog, ac, av);
	init_tty(&display);
//	printf("%d - columns, %d - rows\n", display.columns, display.rows);
	ft_loop(&display, catalog);
	reset_tty(&display);
	close(display.fd);
	t_select *curs;
	curs = catalog;
	while (catalog)
	{
		curs = catalog;
		catalog = catalog->next;
		free(curs);
	}
    return (0);
}