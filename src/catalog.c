#include "ft_select.h"

void     fill_catalog(t_select **catalog, int ac, char **av)
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