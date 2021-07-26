#include "../include/minishell.h"

char	*ft_strjoin2(char **s1, char **s2)
{
	char	*ret;

	if (*s1 && *s2)
	{
		ret = ft_strjoin(*s1, *s2);
		if (!ret)
			return (NULL);
		free(*s1);
		free(*s2);
		return (ret);
	}
	return (NULL);
}

int	handle_file_error(int ret, char **file)
{
	g_glob.file_error = 1;
	g_glob.status = 1;
	printf("minishell: %s : %s\n", *file, strerror(errno));
	free(*file);
	return (ret);
}

int	free_n_return(int ret, char **str)
{
	free(*str);
	return (ret);
}

int 	error_message(char *msg, char *cmd, int ret)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (msg)
		ft_putendl_fd(msg, 2);
	else
		ft_putendl_fd(strerror(errno), 2);
	return (ret);
}

int check_path(char **envp)
{
	int		i;
	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
		{
			return (1);
		}
		i++;
	}
	return (0);
}