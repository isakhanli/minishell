#include "../minishell.h"

int	get_n_commands(char *line)
{
	int n;

	n = 1;
	while(*line)
	{
		if (*line == '|')
			n++;
		line++;
	}
	return n;
}

int		get_start(t_minishell *minishell, char *line, int i)
{
	(void)minishell;
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
			if (line[j] == '|')
				n++;
			if (n == i)
				return j + 1;
			j++;
		}
	}
	return (j + 1);
}

int		get_end(t_minishell *minishell, char *line, int i)
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
			if (line[j] == '|')
				n++;
			if (n == i)
				return j - 1;
			j++;
		}
	}
	return (j - 1);
}

t_index get_index(t_minishell *minishell, char *line, int i)
{
	t_index index;

	index.start = get_start(minishell, line, i);
	index.end = get_end(minishell, line, i);

	return (index);
}