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
# include <sys/types.h>
# include <sys/stat.h>
# include <curses.h>
# include <fcntl.h>

typedef struct		s_select
{
	char			*name;
	int				len;
	int				type;
	bool			hidden;
	bool			current;
	bool			chosen;
	bool			last;
	struct s_select	*next;
	struct s_select	*prev;
}					t_select;

typedef struct		s_term
{
	char			*tty_type;
	struct termios	old_tty;
	int				fd;
	int				columns;	//co
	int				rows;		//li
	char			*standout;	//so
	char			*normal;	//se
	char			*clear;		//cl
	char			*cursor_move; //cm
	char			*cursor_visible; // ve
	char			*cursor_home;	//ho
	char			*cursor_half; //hd
	char			*cursor_down; //do
	char			*cursor_key_d; //kd
	char			*cursor_key_l; //kl
	char			*cursor_key_r; //kr
	char			*cursor_key_u; //ku
	char			*underlining; //us
	char			*end_cursor; //te
	char			*start_cursor; //ti
	char			*end_modes; //me
	char			*clear_all; //cd
	char			*reverse; //mr
	bool			allow_move; //ms
}					t_term;

typedef	struct s_sig
{
	int				sig_num;
	void			(*f)(int);
}				t_sig;

void	handle_errors(char *str);

#endif
