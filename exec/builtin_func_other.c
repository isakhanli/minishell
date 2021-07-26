#include "../include/minishell.h"

int builtin_env(char **args)
{
	int     i;
	i = -1;
	g_glob.status = 0;
	while (args[++i])
	{
		ft_putstr_fd(args[i], 1);
		ft_putchar_fd('\n', 1);
	}
	return (g_glob.status);
}

int check_exit_arg(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (i == 0 && (str[0] == '+' || str[0] == '-'))
			i++;
		if (!ft_isdigit(str[i]))
			return (255);
	}
	 if ((str[0] != '-' && ft_strlen(str) > 19)
	 	|| (str[0] == '-' && ft_strlen(str) > 20) )
	 {
	  ft_putstr_fd("minishell: exit: ", 2);
	  ft_putstr_fd(str, 2);
	  ft_putstr_fd(": numeric argument required\n", 2);
	  return (255);
	 }
	 if (str[0] != '-' && ft_strlen(str) == 19)
	 {
	 	if (ft_strncmp(str, "9223372036854775807", 19) > 0)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (255);
		}
	 }
	if (str[0] != '-' && ft_strlen(str) == 20)
	{
		if (ft_strncmp(str, "-9223372036854775808", 20) > 0)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (255);
		}
	}
	return (ft_atoi(str));
}

int builtin_exit(char **args)
{
	int     n;
	g_glob.status = 0;
	n = count_arguments(args);
	if (n > 2)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_glob.status = 1;
		return (g_glob.status);
	}
	else if (n == 2)
	{
		ft_putstr_fd("exit\n", 2);
		g_glob.status = check_exit_arg(args[1]);
	}
	else
		ft_putstr_fd("exit\n", 2);
	exit(g_glob.status);
}
int builtin_pwd(int i)
{
	char    pwd[1024];
	g_glob.status = i;
	getcwd(pwd, 1024);
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	return (g_glob.status);
}
int builtin_echo(char **args, int i, int flag_n)
{
	int     space;
	space = 0;
	g_glob.status = 0;
	if (!args)
	{
		g_glob.status = 1;
		return (g_glob.status);
	}
	while (args[i] != NULL && !(ft_strncmp(args[i], "-n", 2)) && ft_strlen(args[i]) == 2)
		flag_n = ++i;
	while (args[i] != NULL)
	{
		if (space)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(args[i], 1);
		space++;
		i++;
	}
	if (!(flag_n))
		ft_putchar_fd('\n', 1);
	return (g_glob.status);
}