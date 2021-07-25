#include "../include/minishell.h"

int	count_arguments(char **args)
{
	int		i;

	i = 0;
	if (!args)
		return (0);
	while (args[i] != NULL)
		i++;
	return (i);
}

char	*minimize_arg(char *arg)
{
	int		i;
	char	*str;

	i = -1;
	str = ft_strdup(arg);
	while (arg[++i])
		str[i] = ft_tolower(arg[i]);
	return (str);
}

int	handle_builtin(char **args, t_minishell *minishell, int len)
{
	int		result;
	char	*bcmd;

	result = 0;
	bcmd = minimize_arg(args[0]);
	len = ft_strlen(bcmd);
	if (!ft_strncmp(bcmd, "echo", len) && len == 4)
		result = builtin_echo(args, 0, 0);
	else if (!ft_strncmp(bcmd, "cd", len) && len == 2)
		result = builtin_cd(args, minishell);
	else if (!ft_strncmp(bcmd, "pwd", len) && len == 3)
		result = builtin_pwd(0);
	else if (!ft_strncmp(bcmd, "export", len) && len == 6)
		result = builtin_export(args, minishell, 1);
	else if (!ft_strncmp(bcmd, "unset", len) && len == 5)
		result = builtin_unset(args, minishell);
	else if (!ft_strncmp(bcmd, "env", len) && len == 3)
		result = builtin_env(minishell->envp);
	else if (!ft_strncmp(bcmd, "exit", len) && len == 4)
		result = builtin_exit(args);
	free(bcmd);
	return (result);
}
