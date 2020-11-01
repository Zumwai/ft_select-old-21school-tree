#include "ft_select.h"

static void		ft_fill_termios(t_term **config)
{
	tcgetattr(STDIN_FILENO, &((*config)->old_tty));
	(*config)->fd = open(ttyname(STDIN_FILENO), O_RDWR | O_NOCTTY);

}

static void      ft_term_decribe(t_term *config)
{
	struct termios	tty;
    char    *term_type;
    int     result;

    config->tty_type = getenv("TERM");
    if (!config->tty_type)
        handle_errors("Specify a terminal type with setenv\n");
    result = tgetent(NULL, config->tty_type);
    if (result < 0)
        handle_errors("Could not access the termcap data base\n");
    if (!result)
        handle_errors("Terminal type is not defined\n");
	ft_fill_termios(&config);
}

static void     fill_catalog(t_select **catalog, int ac, char **av)
{
	t_select	*new;
	int         index;
    struct stat buf;

    index = 0;
    while (index < ac)
    {
		if (!(new = (t_select *)malloc(sizeof(t_select))))
				handle_errors("Malloc failed to allocate memory. Possibly too many arguments provided");
        new->len = ft_strlen(av[index]);
        new->name = av[index];
        new->hidden = false;
        new->current = false;
        new->chosen = false;
        if (!lstat(av[index], &buf))
			new->type = buf.st_mode;
		else
			handle_errors("lstat failed to recognize type of the file\n");
		new->last = false;
		new->next = NULL;
		if (*catalog)
		{
			(*catalog)->next = new;
			new->prev = (*catalog);
		}
		else
			(*catalog) = new;
        index++;
    }
	(*catalog)->prev = new;
	new->next = (*catalog);
	new->last = true;
}

void	reset_tty(t_term *saved)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &(saved->old_tty));
}

void	init_tty(t_term *config)
{
	struct termios tattr;
	
	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag &= ~(ICANON|ECHO);
	tattr.c_oflag &= ~(OPOST);
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	tcsetattr (STDIN_FILENO, TCSANOW, &tattr);
}

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

int             main(int ac, char **av)
{
    //signals
    if (ac < 2)
        handle_errors("usage: at least one argument required\n");
    ft_select(ac - 1, av + 1);
   // close(fd);
    return (0);
}
