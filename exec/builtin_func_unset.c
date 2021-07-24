#include "../include/minishell.h"

char	**unset_env_param(t_minishell *minishell, int id)
{
	int		i;
	int		j;
	int		n;
	char	**new_env;

	i = 0;
	j = 0;
	n = count_array_lines(minishell->envp);
	new_env = ft_calloc(sizeof(char *), n);
	if (!minishell->envp || !new_env)
		return (NULL);
	while (i < n - 1)
	{
		if (i == id - 1)
			j++;
		new_env[i] = ft_strdup(minishell->envp[j]);
		i++;
		j++;
	}
	new_env[i] = NULL;
	free_arr(minishell->envp);
	return (new_env);
}

int	env_param_unset(char **args, t_minishell *minishell)
{
	int		i;
	char	*param;
	int		id;
	int		len;

	i = 0;
	len = ft_strlen(param);
	while (args[++i])
	{
		param = ft_strjoin(args[i], "=");
		id = get_env_id(minishell->envp, param, len);
		if (id)
			minishell->envp = unset_env_param(minishell, id);
		free(param);
	}
	return (0);
}

int	builtin_unset(char **args, t_minishell *minishell)
{
	int		i;
	int		n;

	i = 0;
	n = count_arguments(args);
	if (!args || n == 1)
		return (1);
	else if (n > 1)
		env_param_unset(args, minishell);
	else
		return (1);
	return (0);
}
