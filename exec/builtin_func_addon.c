#include "../include/minishell.h"

int	get_env_id(char **env, char *env_param, int len_param)
{
	int		id;
	int		i;

	id = 0;
	if (!env || !env_param || !len_param)
		return (0);
	while (env[id])
	{
		i = 0;
		while (env[id][i] != '=' || !env[id][i])
			i++;
		if (!(ft_strncmp(env[id], env_param, len_param)) && \
				(len_param) == i)
			return (id + 1);
		id++;
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
	id = get_env_id(env, env_param, len_param);
	if (id)
	{
		res = ft_substr(env[id - 1], len_param, \
			ft_strlen(env[id - 1]) - len_param);
		return (res);
	}
	return (NULL);
}

char	*get_env_value(char **env, char *env_param)
{
	int		id;
	char	*res;
	int		len_param;

	id = 0;
	res = NULL;
	if (!env || !env_param)
		return (NULL);
	len_param = ft_strlen(env_param);
	id = get_env_id(env, env_param, len_param);
	if (id)
	{
		res = ft_substr(env[id - 1], len_param, \
			ft_strlen(env[id - 1]) - len_param);
		return (res);
	}
	return (NULL);
}

int	update_env(char **env, char *new_value, char *arg, int size)
{
	int		i;
	int		j;

	if (!new_value || !arg || !env)
		return (0);
	i = -1;
	while (env[++i])
	{
		j = 0;
		while (env[i][j] != '=' || !env[i])
			j++;
		if (!(ft_strncmp(env[i], arg, size)) && size == j)
			 break ;
	}
	free(env[i]);
	env[i] = ft_strjoin(arg, new_value);
	return (1);
}
