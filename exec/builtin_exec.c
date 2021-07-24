#include "../include/minishell.h"

int		count_arguments(char **args)
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

int		handle_builtin(char **args, t_minishell *minishell)
{
	char	*bcmd;
	int		bcmd_len;

	bcmd = minimize_arg(args[0]);
	bcmd_len = ft_strlen(bcmd);
	if (!ft_strncmp(bcmd, "echo", bcmd_len) && bcmd_len == 4) // +-
		builtin_echo(args);
	else if (!ft_strncmp(bcmd, "cd", bcmd_len) && bcmd_len == 2) // -
	{
		free(bcmd);
		return (builtin_cd(args, minishell));
	}
	else if (!ft_strncmp(bcmd, "pwd", bcmd_len) && bcmd_len == 3) // +
	{
		free(bcmd);
		return builtin_pwd(minishell->envp);
	}
	else if (!ft_strncmp(bcmd, "export", bcmd_len) && bcmd_len == 6) //-
		builtin_export(args, minishell);
	else if (!ft_strncmp(bcmd, "unset", bcmd_len) && bcmd_len == 5) // -
		builtin_unset(args, minishell);
	else if (!ft_strncmp(bcmd, "env", bcmd_len) && bcmd_len == 3) // +-
		builtin_env(minishell->envp);
	else if (!ft_strncmp(bcmd, "exit", bcmd_len) && bcmd_len == 4) // +
		builtin_exit();
	else
	{
		free(bcmd);
		return (0);
	}
	free(bcmd);
	return (1);
}