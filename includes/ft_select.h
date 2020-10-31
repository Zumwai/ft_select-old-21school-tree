#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <signal.h>
# include <stdbool.h>

typedef struct		s_select
{
	char			*name;
	bool			hidden;
	bool			current;
	bool			chosen;
	bool			last;
	struct s_select *next;
	struct s_select *prev;
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

#endif
