#include "ft_select.h"

void	reset_tty(t_term *saved)
{
	ft_putstr_fd(saved->clear_all, STDOUT_FILENO);
	ft_putstr_fd(saved->cursor_visible, saved->fd);
//	ft_putstr_fd(saved->cursor_home, saved->fd);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &(saved->old_tattr));
	tputs(tgetstr("ve", NULL), 1, ft_printnbr);
	tputs(tgetstr("te", NULL), 1, ft_printnbr);
}

t_select	*create_node(char  *vector)
{
	t_select	*new;
    struct stat buf;

	if (!(new = (t_select *)malloc(sizeof(t_select))))
				handle_errors("Malloc failed to allocate memory. Possibly too many arguments provided");
	new->len = ft_strlen(vector);
	new->name = vector;
	new->hidden = false;
	new->current = false;
	new->chosen = false;
	if (!lstat(vector, &buf))
		new->type = buf.st_mode;
	else
		new->type = 0;
	new->last = false;
	new->next = NULL;
	return (new);
}

void	print_vector(t_select *vector, int max, bool last)
{
	if (vector->hidden == true)
		return ;
	if (vector->current == true)
	{
		ft_putstr(tgetstr("mr", NULL));
		ft_putstr(vector->name);
		ft_putstr(tgetstr("me", NULL));
	}
	else
	{
		ft_putstr(vector->name);
	}
	if (last != false)
	{
		while (vector->len < max)
		{
			max--;
			ft_putchar(' ');
		}
		ft_putchar(' ');
	}
}

int		ft_printnbr(int nbr)
{
	return (write(STDERR_FILENO, &nbr, 1));
}