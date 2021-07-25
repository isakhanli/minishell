#include "../include/minishell.h"

int	save_arg(t_list **head, char **arg)
{
	char	*temp;

	temp = ft_strdup(*arg);
	if (!temp)
		return (0);
	free(*arg);
	*arg = NULL;
	ft_lstadd_back(head, ft_lstnew(temp));
	return (1);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	is_quoted(char *str, int j)
{
	int		i;
	int		open;
	char	quote;

	open = 1;
	i = 0;
	quote = str[i];
	while (str[i] && i < j)
	{
		if ((str[i] == '\'' || str[i] == '\"') && open == 1)
		{
			quote = str[i];
			open = -open;
		}
		else if (str[i] == quote && open == -1)
		{
			open = -open;
			quote = 0;
		}
		i++;
	}
	if (open == 1)
		return (0);
	return (1);
}

int	ft_strcmp(char *arg, char *builtin)
{
	int	len_arg;
	int	len_builtin;

	len_arg = ft_strlen(arg);
	len_builtin = ft_strlen(builtin);
	if (!ft_strncmp(arg, builtin, len_arg) && len_arg == len_builtin)
		return (1);
	return (0);
}

int	just_space(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (0);
		line++;
	}
	return (1);
}
