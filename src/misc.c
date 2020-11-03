#include "ft_select.h"

void	reset_tty(t_term *saved)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &(saved->old_tty));
}

void		ft_fill_termios(t_term **config)
{
	tcgetattr(STDIN_FILENO, &((*config)->old_tty));
	(*config)->fd = open(ttyname(STDIN_FILENO), O_RDWR | O_NOCTTY);
}