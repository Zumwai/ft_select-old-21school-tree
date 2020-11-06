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
		if (curs->hidden == FALSE)
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
				if (curs->hidden == TRUE)
					curs = curs->next;
				if (curs)
				{
					print_vector(curs, max_len, col - tmp_col - 1);
					curs = curs->next;
				}
				tmp_col++;
			}
			ft_putchar('\n');
	}
}

int	ft_calc_draw(t_term *config, t_select *vector)
{
	int	max_len;
	int	num_vec;
	int	col;
	int	rows_taken;

	max_len = max_vector_length(vector) + 1;
	num_vec = count_vectors(vector);
	if (!num_vec)
		handle_errors("No more arguments left");
	printf("%d columns, %d num vector %d max len %d - rows", config->columns, num_vec, max_len, config->rows);
	col = config->columns / (max_len); //padding plus 1 to avoid division by zero
	rows_taken = num_vec / col;
	if (config->rows < rows_taken)
		handle_errors("Not enough rows\n");
	ft_draw(vector, max_len, col);
	return (col);
}