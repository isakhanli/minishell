#include "../include/minishell.h"

int	parse_cmd_n_rdr(char *line, char **redir, char **cmd)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (is_redir(line, i))
		{
			*redir = cjoin(*redir, line[i], 1);
			if (!(*redir))
				return (0);
		}
		else
		{
			*cmd = cjoin(*cmd, line[i], 1);
			if (!*cmd)
				return (0);
		}
	}
	return (1);
}

int	get_cmd_n_rdr(t_minishell *minishell, char *line, t_index index, int i)
{
	char	*arg;
	char	*redir;
	char	*cmd;

	cmd = NULL;
	redir = NULL;
	arg = ft_substr(line, index.start, (index.end - index.start + 1));
	if (!arg)
		return (0);
	if (!parse_cmd_n_rdr(arg, &redir, &cmd))
		return (0);
	if (!parse_n_create_cmd(minishell, cmd, redir, i))
		return (0);
	free(arg);
	return (1);
}

t_index	get_index(t_minishell *minishell, char *line, int i)
{
	t_index	index;

	index.start = get_start(line, i);
	index.end = get_end(minishell, line, i);
	return (index);
}

int	get_n_commands(char *line)
{
	int	n;
	int	i;

	n = 1;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '|' && !is_quoted(line, i))
			n++;
	}
	return (n);
}

int	parse(char *line, t_minishell *minishell)
{
	int		n_cmds;
	int		i;
	t_index	index;

	n_cmds = get_n_commands(line);
	minishell->n_cmd = n_cmds;
	i = -1;
	while (++i < minishell->n_cmd)
	{
		index = get_index(minishell, line, i + 1);
		if (!(get_cmd_n_rdr(minishell, line, index, i)))
			return (0);
	}
	if (!g_glob.file_error)
	{
		if (!(minishell->n_cmd == 1 && !minishell->commands[0]->arg))
			handle_exec(minishell);
		else if (minishell->n_cmd == 1 && minishell->commands[0]->arg
			&& is_builtin(minishell->commands[0]->arg[0]))
			execute_builtin2(minishell, 0);
	}
	handle_unlink(minishell);
	free_minishell(minishell);
	return (1);
}
