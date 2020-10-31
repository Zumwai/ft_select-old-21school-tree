#include "ft_select.h"

void    handle_errors(char *str)
{
    ft_putstr_fd("ft_select: ", 2);
    ft_putstr_fd(str, 2);
    exit(1);
}