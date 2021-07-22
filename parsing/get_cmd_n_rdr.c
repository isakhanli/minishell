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

int	parse_cmd_n_rdr(char *line, char **redir, char **cmd)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (is_redir(line, i))
		{
			*redir = cjoin(*redir, line[i]);
			if (!(*redir))
				return (0);
		}
		else
		{
			*cmd = cjoin(*cmd, line[i]);
			if (!*cmd)
				return (0);
		}
	}
	return (1);
}

int	get_cmd_n_rdr(t_minishell *minishell, char *line, t_index index, int i)
{
	char	*cmd;
	char	*redir;
	char	*arg;

	arg = NULL;
	redir = NULL;
	cmd = ft_substr(line, index.start, (index.end - index.start + 1));
	if (!cmd)
		return (0);
	if (!parse_cmd_n_rdr(cmd, &redir, &arg))
		return (0);
	if (!parse_and_create_command(minishell, arg, redir, i))
		return (0);
	if (!arg)
		return 0;
	free(cmd);
	return (1);
}
