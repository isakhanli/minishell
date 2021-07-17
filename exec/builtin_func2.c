#include "../minishell.h"

int		builtin_cd(char **args, t_minishell *minishell)
{
	char	*value;

	value = NULL;
	(void)args;
	(void)minishell;
	printf("\033[33;1mbultin command cd\033[m\n");
	update_env(minishell, value);
	return (1);
}