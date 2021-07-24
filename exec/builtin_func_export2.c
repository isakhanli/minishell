#include "../include/minishell.h"

int	sort_env(char **arr)
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
	return (EXIT_SUCCESS);
}

char	**realloc_env(t_minishell *minishell, char *param, char *value)
{
	int		i;
	int		n;
	char	**new_env;

	i = 0;
	n = count_array_lines(minishell->envp);
	new_env = ft_calloc(sizeof(char *), n + 2);
	if (!minishell->envp || !new_env)
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

int	env_param_update(char *args, t_minishell *minishell)
{
	int		j;
	char	*param;
	char	*value;

	if (args)
	{
		j = 1;
		while (args[j] || args[j] != '=')
			j++;
		param = ft_substr(args, 0, j + 1);
		value = ft_substr(args, j + 1, ft_strlen(args) - j);
		printf("par = '%s', val = '%s', j = '%d'\n", param, value, j);
		if (!(param && value))
			return (1);
		if (get_env_id(minishell->envp, param, j + 1))
			update_env(minishell->envp, value, param, j + 1);
		else
			minishell->envp = realloc_env(minishell, param, value);
		free(param);
		free(value);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

void	handle_export_error(char *path)
{
	g_glob.g_status = 1;
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
}
