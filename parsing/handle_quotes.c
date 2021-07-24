#include "../include/minishell.h"

int	free_nd_return(char *line)
{
	free(line);
	return (0);
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
	if (*current)
	{
		*current = ft_strjoin(*current, temp);
		if (!*current)
			return (free_nd_return(temp));
		free(temp2);
	}
	else
	{
		*current = ft_strdup(temp);
		if (!*current)
			return (free_nd_return(temp));
	}
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
		return (free_nd_return(temp));
	if (*current)
	{
		*current = ft_strjoin(*current, temp);
		if (!*current)
			return (free_nd_return(temp));
		free(temp2);
	}
	else
	{
		if (temp)
			*current = ft_strdup(temp);
		else
			current = NULL;
		if (!*current)
			return (free_nd_return(temp));
	}
	free(temp);
	(*i)++;
	return (1);
}
