#include "../minishell.h"

int	get_n_commands(char *line)
{
	int n;
	int i;

	n = 1;
	i = 0;
	while (line[i])
	{
		if (line[i] == '|' && !is_quoted(line, i))
			n++;
		i++;
	}
	return n;
}

int	get_start(char *line, int i)
{
	int j;
	int n;

	j = 0;
	n = 1;
	if (i == 1)
		return (0);
	else
	{
		while (line[j])
		{
			if (line[j] == '|' && !is_quoted(line, j))
				n++;
			if (n == i)
				break ;
			j++;
		}
	}
	return (j + 1);
}

int	get_end(t_minishell *minishell, char *line, int i)
{
	int j;
	int n;

	j = 0;
	n = 0;
	if (minishell->n_cmd == i)
		return ((int)ft_strlen(line) - 1);
	else
	{
		while (line[j])
		{
			if (line[j] == '|' && !is_quoted(line, j))
				n++;
			if (n == i)
				break ;
			j++;
		}
	}
	return (j - 1);
}

t_index	get_index(t_minishell *minishell, char *line, int i)
{
	t_index index;

	index.start = get_start(line, i);
	index.end = get_end(minishell, line, i);
	return (index);
}