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

void	builtin_exit(void)
{
	ft_putstr_fd("exit\n", 1);
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
