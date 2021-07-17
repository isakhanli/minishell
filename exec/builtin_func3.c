#include "../minishell.h"

int		builtin_export(char **args)
{
(void)args;
printf("\033[33;1mbultin command export\033[m\n");
	return (1);
}

int		builtin_unset(char **args)
{
(void)args;
printf("\033[33;1mbultin command unset\033[m\n");
	return (1);
}
