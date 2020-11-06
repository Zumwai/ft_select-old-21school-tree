#include "ft_select.h"



void	key_right(t_select **vector)
{
	t_select	*curs;
	t_select	*head;

	curs = (*vector);
	head = curs;
	while (curs)
	{
		if (curs->current == false)
			curs = curs->next;
		else
		{
			curs->current = false;
			if (curs->next)
				curs->next->current = true;
			else
				head->current = true;
			break ;
		}
	}
}
/*
void	key_backspace(t_select **vector)
{
	t_select	*curs;

	curs = (*vector);
	while (curs)
	{
		if (curs->current == true)
		{
			if (curs->next)
				curs->next->current = true;
			else if (curs->prev)
				curs->prev->current = true;
			else
				break ;
			curs->current = false;
			curs->hidden = true;
			break ;
		}
		else
		{
			curs = curs->next;
		}
		
	}
}
*/
void	key_backspace(t_select **vector)
{
	t_select	*curs;

	curs = (*vector);
	while (curs)
	{
		if (curs->current == true)
		{
			if (curs->next)
				curs->next->current = true;
			else if (curs->prev)
				curs->prev->current = true;
			else
				handle_errors("no more arguments left");
			curs->hidden = TRUE;
			break ;
		}
		curs = curs->next;
	}
}

void	key_left(t_select **vector)
{
	t_select	*curs;
	t_select	*head;

	curs = (*vector);
	head = curs;
	while (curs)
	{
		if (curs->current == false)
			curs = curs->next;
		else
		{
			curs->current = false;
			if (curs->prev)
				curs->prev->current = true;
			else
			{
				while (curs->last == false)
					curs = curs->next;
				curs->current = true;
			}
			break ;
		}
	}
}

void	key_down(t_select **vector, int col)
{
	t_select	*curs;
	t_select	*tmp;
	int		i;

	i = 0;
	curs = (*vector);
	while (curs)
	{
		if (curs->current == true)
		{
			tmp = curs;
			break ;
		}
		curs = curs->next;
	}
	while (curs && i < col)
	{
		if (curs->hidden == FALSE)
			i++;
		curs = curs->next;
	}
	if (i == col)
	{
		curs->current = true;
		tmp->current = false;
	}
}
void placehold(t_select *vector, int col)
{
	int		key;
	int		ret;

	while (1){
		key = 0;
		ret = 0;
		if ((ret = read(STDIN_FILENO, &key, sizeof(key))))
		{
			printf("%d - key\n", key);
			if (key == 4414235)
			{
				tgoto("vasya", 40, 0);
				ft_putchar('r');
				key_right(&vector);
				return ;
			}
			else if (key == 127)
			{
				ft_putchar('b');
				key_backspace(&vector);
				break ;
			}
			else if (key == 4479771)
			{
				ft_putchar('l');
				key_left(&vector);
				break ;
			}
			else if (key == 4348699)
			{
				ft_putchar('d');
				key_down(&vector, col);
				break ;
			}
			else if (key == 4283163)
			{
				//key_up(&vector, col);
				break ;
			}
		}
	}
	ft_putchar('x');
}

void	ft_loop(t_term *config, t_select *vector)
{
	int		i;
	int		flag = 0;
	t_select	*curs;
	int		key;
	int		ret;
	int		col;

	i = 0;
	key = 0;
	ret = 0;
	curs = vector;
	while (1)
	{
		tputs(config->clear, 1, ft_printnbr);
		//if (!flag)
		col = ft_calc_draw(config, vector);
		if (col == 1)
			handle_errors("alarm");
		printf("%d", ret);
	//	if ((ret = read(STDIN_FILENO, &key, sizeof(int))))
	//		key_right(&vector);
		placehold(vector, col);
		ret++;
	}

}