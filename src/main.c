#include "ft_select.h"

static void		ft_fill_termios(t_term **config)
{
	tcgetattr(STDIN_FILENO, &((*config)->old_tty));

}

static void      ft_term_decribe(t_term *config)
{
	struct termios	tty;
    char    *term_type;
    int     result;

    term_type = getenv("TERM");
    if (!term_type)
        handle_errors("Specify a terminal type with setenv\n");
    result = tgetent(NULL, term_type);
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
	//tattr.c_lflag &= ~(ICANON|ECHO);
	tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
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
	//reset_tty(&display);
    return (0);
}

int             main(int ac, char **av)
{
    //signals
    if (ac < 2)
        handle_errors("usage: at least one argument required\n");
    ft_select(ac - 2, av + 1);
   // close(fd);
    return (0);
}
