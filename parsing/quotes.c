#include "../minishell.h"

int 	free_nd_return(char *line)
{
	free(line);
	return (0);
}

int		handle_single_quote(char *line, int *i, char **current)
{
	char	*temp;
	char 	*temp2;
	int		k;

	temp2 = *current;
	(*i)++;
	k = *i;
	while (line[*i] != '\'' && line[*i])
		(*i)++;
	if (!(temp = ft_substr(line, k, (*i - k))))
		return (0);
	if (*current)
	{
		if (!(*current = ft_strjoin(*current, temp)))
			return (free_nd_return(temp));
		free(temp2);
	}
	else
	if (!(*current = ft_strdup(temp)))
		return (free_nd_return(temp));
	free(temp);
	(*i)++;
	return 1;
}

int		handle_double_quote(char *line, int *i, char **current, char **envp)
{
	char	*temp;
	char	*temp2;
	int		k;

	temp2 = *current;
	(*i)++;
	k = *i;
	while (line[*i] != '\"' && line[*i])
		(*i)++;
	if (!(temp = ft_substr(line, k, (*i - k))))
		return (0);
	if (!(handle_dollar_with_quotes(&temp, envp)))
		return (free_nd_return(temp));
	if (*current)
	{
		if (!(*current = ft_strjoin(*current, temp)))
			return (free_nd_return(temp));
		free(temp2);
	}
	else
	if (!(*current = ft_strdup(temp)))
		return (free_nd_return(temp));
	free(temp);
	(*i)++;
	return 1;
}