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
	char	*tmp1;
//printf("path = '%s'\n", path);
	if (chdir(path) == 0)// && getcwd(dir, 256))
	{
		tmp1 = ft_strjoin("=", dir);
		update_env(minishell->envp, tmp1, "OLDPWD", 6);
		free(tmp1);
		getcwd(dir, 1024);
		tmp1 = ft_strjoin("=", dir);
		update_env(minishell->envp, tmp1, "PWD", 3);
		free(tmp1);
		return (0);
	}
	else
		handle_cd_error(path, errno);
	//free(path);
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



int	builtin_cd(char **args, t_minishell *minishell)//, int i)
{
	int		i;
	char	*path;
	char	*tmp;
	char	*tmp_path;

	char	dir[1024];
	char	*home;

	i = 1;
	g_glob.status = 0;
	getcwd(dir, 1024);
	home = get_pwd(minishell->envp, "HOME", 0);
	tmp_path = args[1];
	if (((!ft_strncmp(args[1], "-", 1) || !ft_strncmp(args[1], "~", 1)) && ft_strlen(args[1]) == 1) || !args[1][0])
		try_chdir(home, dir, minishell);
	else
	{
		if (!ft_strncmp(args[1], "~/", 2) && ft_strlen(path) > 1)
		{
			while (args[1][++i])
				;
			tmp = ft_substr(args[1], 1, i);
			path = ft_strjoin(home, tmp);
			free(tmp);
		}
		else
			path = ft_strdup(args[1]);
		try_chdir(path, dir, minishell);
		free(path);
	}
	free(home);
	return (g_glob.status);
}
