#include "../include/minishell.h"

void	handle_cd_error(char *path, int err)
{
	g_glob.status = 1;
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(err), 2);
	ft_putchar_fd('\n', 2);
}

int	try_chdir(char *path, char *dir, t_minishell *minishell)
{
	char	*tmp;

	if (chdir(path) == 0)
	{
		tmp = ft_strjoin("=", dir);
		update_env(minishell->envp, tmp, "OLDPWD", 6);
		free(tmp);
		getcwd(dir, 1024);
		tmp = ft_strjoin("=", dir);
		update_env(minishell->envp, tmp, "PWD", 3);
		free(tmp);
		return (0);
	}
	else
		handle_cd_error(path, errno);
	return (g_glob.status);
}

char	*get_pwd(char **env, char *env_param, int id)
{
	char	*res;

	res = NULL;
	if (!env || !env_param)
		return (NULL);
	id = get_env_id(env, env_param, 4);
	if (id)
	{
		res = ft_substr(env[id - 1], 5, ft_strlen(env[id - 1]) - 5);
		return (res);
	}
	return (NULL);
}

char	*take_cd_arg(char *str, char *home)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 1;
	if ((!ft_strncmp(str, "~/", 2) && ft_strlen(str) > 1))
	{
		while (str[i])
			i++;
		tmp = ft_substr(str, 1, i - 1);
		path = ft_strjoin(home, tmp);
		free(tmp);
	}
	else
		path = ft_strdup(str);
	return (path);
}

int	builtin_cd(char **args, t_minishell *minishell)
{
	char	*path;
	char	dir[1024];
	char	*home;

	g_glob.status = 0;
	getcwd(dir, 1024);
	home = get_pwd(minishell->envp, "HOME", 0);
	if (!args[1] || ((!ft_strncmp(args[1], "-", 1)
				|| !ft_strncmp(args[1], "~", 1)) && ft_strlen(args[1]) == 1))
		try_chdir(home, dir, minishell);
	else
	{
		path = take_cd_arg(args[1], home);
		try_chdir(path, dir, minishell);
		free(path);
	}
	free(home);
	return (g_glob.status);
}
