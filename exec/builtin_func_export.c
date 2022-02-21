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

void	helper_func(char **value)
{
	free(*value);
	*value = NULL;
}

int	env_param_update(char *args, int len, t_minishell *minishell)
{
	int		j;
	char	*param;
	char	*value;

	if (args)
	{
		j = 0;
		while (j < len && args[j] != '=')
			j++;
		param = ft_substr(args, 0, j);
		value = ft_substr(args, j, len - j);
		if (len == j)
			helper_func(&value);
		if (!(!(param) || !(value)) && get_env_id(minishell->envp, param, j))
			update_env(minishell->envp, value, param, j);
		else
			minishell->envp = realloc_env(minishell, param, value);
		free(param);
		if (value)
			free(value);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	builtin_export(char **args, t_minishell *minishell, int i)
{
	int		n;
	int		len;

	len = 0;
	g_glob.status = 0;
	n = count_arguments(args);
	if (!args)
		return (EXIT_FAILURE);
	else if (n == 1)
		env_print(minishell->envp);
	else if (n > 1)
	{
		while (i <= n)
		{
			len = ft_strlen(args[i]);
			if (!(wrong_export_arg(args[i], "export")))
				env_param_update(args[i], len, minishell);
			i++;
		}
	}
	return (g_glob.status);
}
