#include "../minishell.h"

/*
char	*split_path(char *path)
{
	int		i;
	int		n;
	char	*current_dir;

	i = -1;
	n = 0;
	while (path[++i])
		if (path[i] == '/')
			n = i;
	current_dir = ft_substr(path, 4, n);
	return (current_dir);
}

char	*make_path(char *path, char *folder)
{
	int		i;
	int		n;
	char	*new_dir;
	char	*tmp;

	i = -1;
	n = 0;
	while (path[++i])
		if (path[i] == '/')
			n = i;
	if (folder == )
	tmp = ft_substr(path, 1, n + 1);
	new_dir = ft_strjoin(tmp);
	free(tmp);
	return (new_dir);
}
*/
int		update_env(char **env, char *new_value, char *arg, int size)
{
	int		i;

	if (!new_value || !arg || !env)
		return (0);
	i = -1;
	while (env[++i])
		if (!(ft_strncmp(env[i], arg, size)))
			break;
	free(env[i]);
	env[i] = ft_strjoin(arg, new_value);
	return (1);
}

int		get_env_id(char **env, char *env_param, int len_param)
{
	int		id;

	id = 0;
	if (!env || !env_param || !len_param)
		return (0);
	while (env[id] != NULL)
	{
		if (!(ft_strncmp(env[id], env_param, len_param - 1)))
			return (id + 1);
		id++;
	}
	return (0);
}

char	*get_env_value(char **env, char *env_param)
{
	int		id;
	char	*res;
	int		len_param;
	char	*tmp_param;
	
	id = 0;
	res = NULL;
	if (!env || !env_param)
		return (NULL);
	len_param = ft_strlen(env_param) + 1;
	tmp_param = ft_strjoin(env_param, "=");
	if ((id = get_env_id(env, tmp_param, len_param + 1)))
	{
		res = ft_substr(env[id - 1], len_param, ft_strlen(env[id - 1]) - len_param);
		//printf("res = %s\n", res);
		free(tmp_param);
		return (res);
	}
	free(tmp_param);
	return (NULL);
}

void	handle_cd_error(char *path, int err)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(strerror(err), 2);
	ft_putchar_fd('\n', 1);;
}

int		builtin_cd(char **args, t_minishell *minishell)
{
	printf("\033[33;1mbultin command cd\033[m\n");
	char	*pwd;
	char	*path;
	char	dir[256];

	if ((pwd = get_env_value(minishell->envp, "PWD")))
	{
		if (!args[1] || !ft_strncmp(args[1], "-", 1))
			path = get_env_value(minishell->envp, "HOME");
		else if (!ft_strncmp(args[1], "", 1))
			path = pwd;
		else
			path = args[1];
		if (chdir(path) == 0 && getcwd(dir, 256) && \
				update_env(minishell->envp, dir, "PWD=", 4) && \
				update_env(minishell->envp, pwd, "OLDPWD=", 7))
		{
			free(pwd);
			return (1);
		}
		else
			handle_cd_error(path, errno);
		free(pwd);
	}
	return (0);
}