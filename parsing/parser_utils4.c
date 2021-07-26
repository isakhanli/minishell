#include "../include/minishell.h"

int	count_array_lines(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**define_env(char **envp)
{
	int		i;
	char	**arr;

	i = 0;
	arr = ft_calloc(sizeof(char *), count_array_lines(envp) + 1);
	while (envp[i])
	{
		arr[i] = ft_strdup(envp[i]);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

int	is_redir_sym(char *red, int i)
{
	if ((red[i] == '<' || red[i] == '>') && !is_quoted(red, i))
		return (1);
	return (0);
}

int	get_file(char *redir, char **file, int *i, int k)
{
	char	*temp;

	while (redir[*i] && !is_redir_sym(redir, *i))
		(*i)++;
	*file = ft_substr(redir, k, (*i - k));
	temp = *file;
	*file = ft_strtrim(*file, "  \"");
	free(temp);
	return (1);
}

int	has_dollar(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
