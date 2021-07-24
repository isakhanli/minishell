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
