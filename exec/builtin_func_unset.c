#include "../minishell.h"

char	**unset_env_param(t_minishell *minishell, int id)
{
	int		i;
	int		j;
	int		n;
	char	**new_env;
	i = 0;
	j = 0;
	n = count_array_lines(minishell->envp);
	if (!minishell->envp || !(new_env = ft_calloc(sizeof(char *), n)))
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

int		env_param_unset(char **args, t_minishell *minishell)
{
	int		i;
	char	*param;
	int		id;

	i = 0;
	while (args[++i])
	{
		param = ft_strjoin(args[i], "=");
		if ((id = get_env_id(minishell->envp, param, ft_strlen(param))))
			minishell->envp = unset_env_param(minishell, id);
		free(param);
	}
	return (0);
}

int		builtin_unset(char **args, t_minishell *minishell)
{
	printf("\033[33;1mbultin command unset\033[m\n");
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