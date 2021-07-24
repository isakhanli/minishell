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
	if (chdir(path) == 0 && getcwd(dir, 256) && \
			update_env(minishell->envp, dir, "PWD=", 4) && \
			update_env(minishell->envp, pwd, "OLDPWD=", 7))
	{
		free(pwd);
		g_glob.g_status = 0;
		return (0);
	}
	else
		handle_cd_error(path, errno);
	free(pwd);
	return (1);
}

int	builtin_cd(char **args, t_minishell *minishell)
{
	char	*pwd;
	char	*path;
	char	dir[256];

	pwd = get_env_value(minishell->envp, "PWD");
	if (pwd)
	{
		if (!args[1] || !ft_strncmp(args[1], "-", 1))
			path = get_env_value(minishell->envp, "HOME");
		else if (!ft_strncmp(args[1], "", 1))
			path = pwd;
		else
			path = args[1];
		if (!try_chdir(path, dir, pwd, minishell))
			return (0);
	}
	return (1);
}
