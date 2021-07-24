#include "../include/minishell.h"

int	builtin_env(char **args)
{
	int		i;

	i = -1;
	while (args[++i])
	{
		ft_putstr_fd(args[i], 1);
		ft_putchar_fd('\n', 1);
	}
	return (EXIT_SUCCESS);
}

int	builtin_exit(char **args)
{
	int		n;

	n = count_arguments(args);
	if (n > 2)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		exit(EXIT_FAILURE);	
	}
	else if (n == 2)
	{
		ft_putstr_fd("exit\n", 2);
		exit(atoi(args[1]));
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		exit(g_glob.g_status);
	}
	exit(EXIT_SUCCESS);
}

int	builtin_pwd(char **env)
{
	int		i;
	char	*str;
	char	*str_compare;

	i = 0;
	str_compare = "PWD";
	while (env[i])
	{
		if (!(ft_strncmp(env[i], str_compare, 3)))
		{
			str = ft_substr(env[i], 4, ft_strlen(env[i]) - 4);
			ft_putstr_fd(str, 1);
			ft_putchar_fd('\n', 1);
			free(str);
			 break ;
		}
		i++;
	}
	return (0);
}

int	builtin_echo(char **args)
{
	int		i;
	int		flag;
	int		space;

	i = 0;
	flag = 0;
	space = 0;
	if (args[1] && !(ft_strncmp(args[1], "-n", 2)) && ft_strlen(args[1]) == 2)
		flag = ++i;
	while (args[++i] != NULL)
	{
		if (space)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(args[i], 1);
		space++;
	}
	if (flag && args[2] != NULL)
		ft_putchar_fd('\%', 1);
	if (!(flag && args[2] == NULL))
		ft_putchar_fd('\n', 1);
	return (1);
}
