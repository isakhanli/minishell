#include "../include/minishell.h"

int	get_current(char **current, char **temp, char **temp2, int quoted)
{
	if (*current)
	{
		*current = ft_strjoin(*current, *temp);
		if (!*current)
			return (free_n_return(0, temp));
		free(*temp2);
	}
	else if (quoted)
	{
		if (*temp)
			*current = ft_strdup(*temp);
		else
			current = NULL;
		if (!*current)
			return (free_n_return(0, temp));
	}
	else
	{
		*current = ft_strdup(*temp);
		if (!*current)
			return (free_n_return(0, temp));
	}
	return (1);
}

int	handle_single_quote(char *line, int *i, char **current)
{
	char	*temp;
	char	*temp2;
	int		k;

	temp2 = *current;
	(*i)++;
	k = *i;
	while (line[*i] != '\'' && line[*i])
		(*i)++;
	temp = ft_substr(line, k, (*i - k));
	if (!temp)
		return (0);
	if (!(get_current(current, &temp, &temp2, 0)))
		return (0);
	free(temp);
	(*i)++;
	return (1);
}

int	handle_double_quote(char *line, int *i, char **current, char **envp)
{
	char	*temp;
	char	*temp2;
	int		k;

	temp2 = *current;
	(*i)++;
	k = *i;
	while (line[*i] != '\"' && line[*i])
		(*i)++;
	temp = ft_substr(line, k, (*i - k));
	if (!temp)
		return (0);
	if (!(handle_dollar_with_quotes(&temp, envp)))
		return (free_n_return(0, &temp));
	if (!(get_current(current, &temp, &temp2, 1)))
		return (0);
	free(temp);
	(*i)++;
	return (1);
}
