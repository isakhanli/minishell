#include "../include/minishell.h"

void printarr(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

char	*get_path(char **envp)
{
	int		i;
	char	*temp;

	temp = NULL;
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			temp = ft_strdup(envp[i] + 5);
			if (!temp)
				return (NULL);
			break ;
		}
		i++;
	}
	return (temp);
}

char	*get_binned(char *str, char **path_array, int *flag)
{
	int			i;
	char		*temp;
	char		*slashed;
	struct stat	info;

	i = -1;
	while (path_array[++i])
	{
		slashed = ft_strjoin(path_array[i], "/");
		if (!slashed)
			return (NULL);
		temp = ft_strjoin(slashed, str);
		if (!temp)
			return (NULL);
		if (!(lstat(temp, &info)))
		{
			*flag = 1;
			free(slashed);
			return (temp);
		}
		free(slashed);
		free(temp);
	}
	return (str);
}

char	*add_path(char *str, char **envp, char *path)
{
	char	*binned;
	char	**path_array;
	int		flag;

	flag = 0;
	path = get_path(envp);
	path_array = ft_split(path, ':');
	if (!path_array)
		return (NULL);
	binned = get_binned(str, path_array, &flag);
	if (!binned)
		return (NULL);
	free_arr(path_array);
	free(path);
	if (flag)
		free(str);
	return (binned);
}

int	check_bin(char *str)
{
	while (*str)
	{
		if (*str == '/')
			return (1);
		str++;
	}
	return (0);
}

int	binarize(t_minishell *minishell, t_command *command)
{
	char	*path;

	path = get_path(minishell->envp);
	command->cmd = ft_strdup(command->arg[0]);
	if (command->arg[0] != NULL && !check_bin(command->arg[0])
		&& path)
	{
		command->arg[0] = add_path(command->arg[0], minishell->envp, path);
	}
	if (path)
		free(path);
	return (1);
}
