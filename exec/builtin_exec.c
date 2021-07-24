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
	char	*bcmd;

	bcmd = minimize_arg(args[0]);
	len = ft_strlen(bcmd);
	if (!ft_strncmp(bcmd, "echo", len) && len == 4)
		builtin_echo(args);
<<<<<<< HEAD
	else if (!ft_strncmp(bcmd, "cd", len) && len == 2)
		return (builtin_cd(args, minishell));
	else if (!ft_strncmp(bcmd, "pwd", len) && len == 3)
		return (builtin_pwd(minishell->envp));
	else if (!ft_strncmp(bcmd, "export", len) && len == 6)
=======
>>>>>>> e51c0e62b37531ca155930a04a01173806674387
		builtin_export(args, minishell);
	else if (!ft_strncmp(bcmd, "unset", len) && len == 5)
		builtin_unset(args, minishell);
	else if (!ft_strncmp(bcmd, "env", len) && len == 3)
		builtin_env(minishell->envp);
	else if (!ft_strncmp(bcmd, "exit", len) && len == 4)
		builtin_exit(args);
	else
	{
		free(bcmd);
		return (0);
	}
	free(bcmd);
	return (1);
}
