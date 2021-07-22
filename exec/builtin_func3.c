#include "../minishell.h"

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
/*
int	sort_env(char **arr)
{
	int		i;
	int		j;
	int 	count;
	char	*tmp;

	i = -1;
	j = -1;
	count = 0;
	while (arr[++i])
		count++;
	while (++j < count)
	{
		i = 0;
		while (arr[++i])
		(
			if ((ft_strncmp(arr[i - 1][0], arr[i][0], 1)) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[i - 1];
				arr[i - 1] = tmp;
				free(tmp);
			}
		)
	}
	return (1);
}
*/
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

int		print_arr(char **arr)
{
	int		i;
	int		j;
	char	*param;
	char	*value;

	i = -1;
	if (!arr)// && !(sort_env(arr)))
		return (0);
	while (arr[++i])
	{
		j = 0;
		while (arr[i][j] != '=')
			j++;
		param = ft_substr(arr[i], 0, j);
		//value = ft_substr(arr[i], j + 1, ft_strlen(arr[i]) - (j + 1));
		//printf("param = %s\n", param);
		value = get_env_value(arr, param);
		printf("declare -x %s=\"%s\"\n", param, value);
		free(param);
		free(value);
	}
	return (1);
}

char	**realloc_env(t_minishell *minishell, char *param, char *value)
{
	int		i;
	char	**new_env;

	i = 0;
	if (!minishell->envp || !(new_env = ft_calloc(sizeof(char *), count_array_lines(minishell->envp) + 2)))
		return (NULL);
	while (i < count_array_lines(minishell->envp))
	{
		new_env[i] = ft_strdup(minishell->envp[i]);
		printf("%d: %s - %s\n", i, new_env[i], minishell->envp[i]);
		i++;
	}
	new_env[i] = ft_strjoin(param, value);
		printf("%d: %s\n", i, new_env[i]);
	new_env[i + 1] = NULL;
	//	printf("%d: %s - %s\n", i, new_env[i], env[i]);
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
		printf("args[i] = %s\n", args[i]);
		param = ft_substr(args[i], 0, j + 1);
		value = ft_substr(args[i], j + 1, ft_strlen(args[i]) - j);
		//value = get_env_value(args, param);
		printf("param: %s, value: %s, j: %d\n", param, value, j);
		//update_env(minishell->envp, dir, "PWD=", 4);
		if (get_env_id(minishell->envp, param, j + 1))
			update_env(minishell->envp, value, param, j + 1);
		else
		{
			minishell->envp = realloc_env(minishell, param, value);
			//update_env(env, value, param, j + 1);
		}
		free(param);
		free(value);
	}
	return (1);
}

int		check_export_arg(char *arg)
{
	int		i;

	i = 0;
	if (!arg || !arg[0])
		return (0);
	while (arg[++i])
		if (arg[i] && arg[i] == '=')
			return (1);
	return (0);
}

int		builtin_export(char **args, t_minishell *minishell)
{
printf("\033[33;1mbultin command export\033[m\n");
	int		i;
	
	i = 0;
	if (!args[1] || count_arguments(args) == 1)
		print_arr(minishell->envp);
	else if (count_arguments(args) > 1)
	{
		while (args[++i])
			if (!(check_export_arg(args[i])))	
				return (0);
		env_param_update(args, minishell);
	}
	else
		return (0);
	return (1);
}




int		builtin_unset(char **args)
{
(void)args;
printf("\033[33;1mbultin command unset\033[m\n");
	return (1);
}
