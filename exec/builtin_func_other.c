#include "../include/minishell.h"

int	builtin_env(char **args)
{
	int		i;

	i = -1;
	g_glob.g_status = 0;
	while (args[++i])
	{
		ft_putstr_fd(args[i], 1);
		ft_putchar_fd('\n', 1);
	}
	return (g_glob.g_status);
}

int	builtin_exit(char **args)
{
	int		n;

	g_glob.g_status = 0;
	n = count_arguments(args);
	if (n > 2)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_glob.g_status = 1;	
	}
	else if (n == 2)
	{
		ft_putstr_fd("exit\n", 2);
		g_glob.g_status = atoi(args[1]);
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
	}
	exit(g_glob.g_status);
}

int	builtin_pwd(int i)
{
	char	pwd[1024];

	g_glob.g_status = i;
	getcwd(pwd, 256);
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	return (g_glob.g_status);
}

int	builtin_echo(char **args, int i, int flag_n)
{
	int		space;

	space = 0;
	g_glob.g_status = 0;
	if (!args)
	{
		g_glob.g_status = 1;
		return (g_glob.g_status);
	}
	if (args[1] && !(ft_strncmp(args[1], "-n", 2)) && ft_strlen(args[1]) == 2)
		flag_n = ++i;
	while (args[++i] != NULL)
	{
		if (space)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(args[i], 1);
		space++;
	}
	if (flag_n && args[2] != NULL)
		ft_putchar_fd('\%', 1);
	if (!(flag_n && args[2] == NULL))
		ft_putchar_fd('\n', 1);
	return (g_glob.g_status);
}
