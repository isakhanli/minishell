#include "../include/minishell.h"

void	handle_cd_error(char *path, int err)
{
	g_glob.g_status = 1;
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(err), 2);
	ft_putchar_fd('\n', 2);
}

int	try_chdir(char *path, char *dir, char *pwd, t_minishell *minishell)
{
	char	*tmp1;

	if (chdir(path) == 0 && getcwd(dir, 256))
	{
		tmp1 = ft_strjoin("=", dir);
		update_env(minishell->envp, tmp1, "PWD", 3);
		update_env(minishell->envp, pwd, "OLDPWD", 6);
		free(pwd);
		free(tmp1);
		return (0);
	}
	else
		handle_cd_error(path, errno);
	free(pwd);
	return (g_glob.g_status);
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

int	builtin_cd(char **args, t_minishell *minishell)
{
	char	*pwd;
	char	*path;
	char	dir[256];

	g_glob.g_status = 0;
	pwd = get_env_value(minishell->envp, "PWD");
	if (pwd)
	{
		if (!args[1] || !ft_strncmp(args[1], "-", 1))
			path = get_pwd(minishell->envp, "HOME", 0);
		else if (!ft_strncmp(args[1], "", 1))
			path = pwd;
		else
			path = args[1];
		if (!try_chdir(path, dir, pwd, minishell))
			return (0);
	}
	return (g_glob.g_status);
}
