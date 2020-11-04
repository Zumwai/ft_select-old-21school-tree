#include "ft_select.h"

static int		max_vector_length(t_select *vector)
{
	t_select	*curs;
	int			tmp;
	int			max;

	max = 3;
	curs = vector;
	while (curs)
	{
		tmp = ft_strlen(curs->name);
		if (tmp > max)
			max = tmp;
		curs = curs->next;
	}
	return (max);
}

static int		count_vectors(t_select *vector)
{
	int		res;
	t_select	*curs;

	curs = vector;
	res = 1;
	while (curs)
	{
		res++;
		curs = curs->next;
	}
	return (res);
}

static void ft_draw(t_select *vector, int max_len, int col)
{
	t_select	*curs;
	int			tmp_col;

	tmp_col = 0;
	curs = vector;
	while (curs)
	{
			tmp_col = 0;
			while (tmp_col < col)
			{
				if (!curs)
					break;
				ft_putstr(curs->name);
				ft_putstr("  ");
				curs = curs->next;
				tmp_col++;
			}
			ft_putchar('\n');
	}
}

static int	ft_calc_draw(t_term *config, t_select *vector)
{
	int	max_len;
	int	num_vec;
	int	col;
	int	rows_taken;

	max_len = max_vector_length(vector);
	num_vec = count_vectors(vector);
	col = config->columns / max_len;
	rows_taken = num_vec / col;
	if (config->rows < rows_taken)
		handle_errors("Not enough rows\n");
	ft_draw(vector, max_len, col);
	return (1);
}

void	ft_loop(t_term *config, t_select *vector)
{
	int		i;
	int		flag = 0;
	t_select	*curs;

	i = 0;
	curs = vector;
	while (1)
	{
		tputs(config->clear, 1, ft_printnbr);
		//if (!flag)
		ft_calc_draw(config, vector);
		//break ;
	}

}