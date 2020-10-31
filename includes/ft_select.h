#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <termcap.h>
# include <signal.h>
# include <stdbool.h>
# include "libft.h"

typedef struct		s_select
{
	char			*name;
	int				len;
	bool			hidden;
	bool			current;
	bool			chosen;
	bool			last;
}					t_select;

typedef struct		s_term
{
	struct termios	old_tty;
	int				fd;

	/* data */
}					t_term;

typedef	struct s_sig
{
	int				sig_num;
	void			(*f)(int);
};

void	handle_errors(char *str);

#endif
