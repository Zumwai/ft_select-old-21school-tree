#include "ft_select.h"

static void		ft_fill_termios(t_term **config)
{
	tcgetattr(STDIN_FILENO, &((*config)->old_tty));
	(*config)->fd = open(ttyname(STDIN_FILENO), O_RDWR | O_NOCTTY);
}

static void		interrogate_term(t_term *conf)
{
	conf->columns = tgetnum("co");
	conf->rows = tgetnum("li");
	conf->standout = tgetstr("so", NULL);
	conf->normal = tgetstr("se", NULL);
	conf->clear = tgetstr("cl", NULL);
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
	conf->end_cursor = tgetstr("te", NULL);
	conf->start_cursor = tgetstr("ti", NULL);
	conf->end_modes = tgetstr("me", NULL);
	conf->clear_all = tgetstr("cd", NULL);
	conf->reverse = tgetstr("mr", NULL);
	conf->allow_move = tgetflag("ms");
}

static void      ft_term_decribe(t_term *config)
{
	struct termios	tty;
    char    *term_type;
    int     result;

	if (!isatty(STDIN_FILENO))
		handle_errors("Not a terminal");
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
	interrogate_term(config);
	ft_putstr_fd(config->clear, config->fd);
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
