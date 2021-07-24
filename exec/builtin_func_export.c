#include "../include/minishell.h"

int	print_env_arr(char **arr)
{
	int		i;
	int		j;
	char	*param;
	char	*value;

	i = -1;
	if (!arr)
		return (EXIT_FAILURE);
	sort_env(arr);
	while (arr[++i])
	{
		j = 0;
		while (arr[i][j] != '=')
			j++;
		param = ft_substr(arr[i], 0, j);
		value = ft_substr(arr[i], j + 1, ft_strlen(arr[i]) - (j + 1));
		printf("declare -x %s=\"%s\"\n", param, value);
		free(param);
		free(value);
	}
	return (EXIT_SUCCESS);
}

int	env_print(char **env)
{
	int		i;
	int		n;
	char	**arr;

	i = 0;
	if (!env)
		return (EXIT_FAILURE);
	n = count_array_lines(env);
	arr = ft_calloc(sizeof(char *), n + 1);
	if (!arr)
		return (1);
	while (i < n)
	{
		arr[i] = ft_strdup(env[i]);
		i++;
	}
	arr[i] = NULL;
	print_env_arr(arr);
	free_arr(arr);
	return (EXIT_SUCCESS);
}

int	wrong_export_arg(char *arg)
{
	int		i;

	if (!arg || !arg[0])
		return (EXIT_FAILURE);
	else if (arg[0] == '=')
	{
		handle_export_error(arg);
		return (EXIT_FAILURE);
	}
	else if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (EXIT_FAILURE);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isprint(arg[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	builtin_export(char **args, t_minishell *minishell)
{
	int		i;
	int		n;

	i = 0;
	n = count_arguments(args);
	if (!args)
		return (EXIT_FAILURE);
	else if (n == 1)
		env_print(minishell->envp);
	else if (n > 1)
	{
		while (args[++i])
			if (!wrong_export_arg(args[i]))
				env_param_update(args[i], minishell);
	}
	return (EXIT_SUCCESS);
}
