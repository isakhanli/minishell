#include "../minishell.h"

int		sort_env(char **arr)
{
	int		i;
	int		j;
	char	*tmp;

	if (!arr)
		return (1);
	j = 0;
	while (arr[j + 1])
	{
		i = j + 1;
		while (arr[i])
		{
			if (ft_strncmp(arr[i], arr[j], ft_strlen(arr[i])) < 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			i++;
		}
		j++;
	}
	return (0);
}

char	*get_env_param(char **env, char *env_param)
{
	int		id;
	char	*res;
	int		len_param;
	
	id = 0;
	res = NULL;
	if (!env || !env_param)
		return (NULL);
	len_param = ft_strlen(env_param) + 1;
	if ((id = get_env_id(env, env_param, len_param)))
	{
		res = ft_substr(env[id - 1], len_param, ft_strlen(env[id - 1]) - len_param);
		return (res);
	}
	return (NULL);
}

int		print_env_arr(char **arr)
{
	int		i;
	int		j;
	char	*param;
	char	*value;

	i = -1;
	if (!arr)
		return (1);
	sort_env(arr);
//	printarr(arr);
	while (arr[++i])
	{
		j = 0;
		while (arr[i][j] != '=')
			j++;
		param = ft_substr(arr[i], 0, j);
		value = get_env_value(arr, param);
		printf("declare -x %s=\"%s\"\n", param, value);
		free(param);
		free(value);
	}
	return (0);
}

int		env_print(char **env)
{
	int		i;
	int		n;
	char	**arr;

	i = 0;
	if (!env)
		return (1);
	n = count_array_lines(env);
	if (!(arr = ft_calloc(sizeof(char *), n + 1)))
		return (1);
	while (i < n)
	{
		arr[i] = ft_strdup(env[i]);
		i++;
	}
	arr[i] = NULL;
	print_env_arr(arr);
	free_arr(arr);
	return (0);
}

char	**realloc_env(t_minishell *minishell, char *param, char *value)
{
	int		i;
	int		n;
	char	**new_env;

	i = 0;
	n = count_array_lines(minishell->envp);
	if (!minishell->envp || !(new_env = ft_calloc(sizeof(char *), n + 2)))
		return (NULL);
	while (i < n)
	{
		new_env[i] = ft_strdup(minishell->envp[i]);
		i++;
	}
	new_env[i] = ft_strjoin(param, value);
	new_env[i + 1] = NULL;
	free_arr(minishell->envp);
	return (new_env);
}

int		env_param_update(char **args, t_minishell *minishell)
{
	int		i;
	int		j;
	char	*param;
	char	*value;

	i = 0;
	while (args[++i])
	{
		j = 1;
		while (args[i][j] != '=')
			j++;

		if (!((param = ft_substr(args[i], 0, j + 1)) && \
		 		(value = ft_substr(args[i], j + 1, ft_strlen(args[i]) - j))))
		//param = ft_substr(args[i], 0, j + 1);
		//value = ft_substr(args[i], j + 1, ft_strlen(args[i]) - (j + 1));
		//printf("param=%s, value=%s, len=%zu, j=%d\n", param, value, ft_strlen(args[i]), j);
			return (1);
		if (get_env_id(minishell->envp, param, j + 1))
			update_env(minishell->envp, value, param, j + 1);
		else
			minishell->envp = realloc_env(minishell, param, value);
		free(param);
		free(value);
	}
	return (0);
}

int		wrong_export_arg(char *arg)
{
	int		i;

	if (!arg || !arg[0])// || !ft_isalpha(arg[0]))
		return (1);
	i = 1;
	while (arg[i])
	{
		if ((ft_isprint(arg[i]) && !ft_isalpha(arg[0])) || arg[i] == '=')//
			// && ft_isalpha(arg[0]))
			return (0);
		i++;
	}
	return (1);
}

int		builtin_export(char **args, t_minishell *minishell)
{
printf("\033[33;1mbultin command export\033[m\n");
	int		i;
	int		n;
	
	i = 0;
	n = count_arguments(args);
	if (!args)
		return (1);
	if (n == 1) //!args[1] || 
		env_print(minishell->envp);
	else if (n > 1)
	{
		while (args[++i])
			if (wrong_export_arg(args[i]))
				return (1);
		env_param_update(args, minishell);
	}
	else
		return (1);
	return (0);
}