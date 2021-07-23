#include "../minishell.h"

int	is_valid_red(char *cmd, int c)
{
	if (ft_isspace(cmd[c]) && is_quoted(cmd, c))
		return (1);
	else if (!ft_isspace(cmd[c]))
		return (1);
	return (0);
}

int	check_quoted_redir(char *cmd, int i)
{
	if ((cmd[i] == '>' || cmd[i] == '<') && !is_quoted(cmd, i))
		return (1);
	if ((cmd[i - 1] == '>' || cmd[i - 1] == '<') && !is_quoted(cmd, i))
		return (1);
	return (0);
}

int	is_redir(char *cmd, int i)
{
	if (check_quoted_redir(cmd, i))
		return (1);
	if (ft_isspace(cmd[i]) && !is_quoted(cmd, i))
	{
		while (ft_isspace(cmd[i]))
			i--;
		if (cmd[i] == '<' || cmd[i] == '>')
			return (1);
		else
			return (0);
	}
	else
	{
		while (is_valid_red(cmd, i) && i >= 0 && !((cmd[i] == '<'
					|| cmd[i] == '>') && !is_quoted(cmd, i)))
			i--;
		while (ft_isspace(cmd[i]))
			i--;
		if ((cmd[i] == '<' || cmd[i] == '>') && !is_quoted(cmd, i))
			return (1);
	}
	return (0);
}

int	get_start(char *line, int i)
{
	int	j;
	int	n;

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

char	*cjoin(char *line, char c, int flag)
{
	int		len;
	int		i;
	char	*new;

	i = 0;
	len = (int)ft_strlen(line);
	new = (char *)malloc(sizeof(char) * (len + 2));
	if (!new)
		return (NULL);
	if (line)
	{
		while (line[i])
		{
			new[i] = line[i];
			i++;
		}
		if (flag)
			free(line);
	}
	new[i] = c;
	new[i + 1] = '\0';
	return (new);
}
