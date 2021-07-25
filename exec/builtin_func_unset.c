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

int	env_param_unset(char *args, t_minishell *minishell)
{
	int		i;
	int		id;
	int		len;

	i = 0;
	id = 0;
	if (args)
	{
		len = ft_strlen(args);
		id = get_env_id(minishell->envp, args, len);
		if (id)
			minishell->envp = unset_env_param(minishell, id);
	}
	return (EXIT_SUCCESS);
}

int	builtin_unset(char **args, t_minishell *minishell)
{
	int		i;
	int		n;

	i = 0;
	g_glob.status = 0;
	n = count_arguments(args);
	if (!args || n == 1)
		return (EXIT_FAILURE);
	else if (n > 1)
	{
		while (args[++i])
			if (!(wrong_unset_arg(args[i], "unset")))
				env_param_unset(args[i], minishell);
	}
	return (g_glob.status);
}
