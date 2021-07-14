#include "../minishell.h"

char *add_bin(char *str)
{
	char *temp = "/bin/";
	char *binned;
	binned = ft_strjoin(temp, str);
	return binned;

}

char	*get_path(char **envp)
{
	int i;
	char *temp;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
		{
			temp = ft_strdup(envp[i] + 5);
		}
		i++;
	}
	return temp;
}

char *get_binned(char *str, char **path_array)
{
	int i;
	struct stat info;
	char *temp;
	char *slashed;

	i = 0;
	while (path_array[i])
	{
		slashed = ft_strjoin(path_array[i], "/");
		temp = ft_strjoin(slashed, str);
		if (!(lstat(temp, &info)))
			return temp;
		i++;
		free(slashed);
		free(temp);
	}
	return  str;
}

char *add_path(char *str, char **envp)
{
	char *binned;
	char *path;
	char **path_array;

	path = get_path(envp);
	path_array = ft_split(path, ':');

	binned = get_binned(str, path_array);
	return binned;

}

int check_bin(char *str)
{
	if (str[0] == '/' && str[1] == 'b' && str[2] == 'i'
		&& str[3] == 'n' && str[4] == '/')
		return 1;
	return 0;
}

int binarize(t_minishell *minishell, t_command *command)
{

	if (command->arg[0] != NULL && !check_bin(command->arg[0]))
	{
		command->arg[0] = add_path(command->arg[0], minishell->envp);
	}
	return (1);
}