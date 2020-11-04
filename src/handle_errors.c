#include "ft_select.h"

void    handle_errors(char *str)
{
    ft_putstr_fd("ft_select: ", STDERR_FILENO);
    ft_putstr_fd(str, STDERR_FILENO);
    exit(1);
}