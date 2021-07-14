#include "../minishell.h"

int is_valid_red(char *cmd, int c)
{
	if (ft_isspace(cmd[c]) && is_quoted(cmd, c))
		return (1);
	else if (!ft_isspace(cmd[c]))
		return (1);
	return (0);
}

int 	is_redir(char *cmd, int i)
{
	int k;

	k = i;
	if ((cmd[i] == '>' || cmd[i] == '<') && !is_quoted(cmd, i))
		return (1);

	if ((cmd[i - 1] == '>' || cmd[i - 1	] == '<') && !is_quoted(cmd, i))
		return (1);

	else
	{

		if (ft_isspace(cmd[k]) && !is_quoted(cmd, k))
		{
			while (ft_isspace(cmd[k]))
				k--;
			if (cmd[k] == '<' || cmd[k] == '>')
				return (1);
			else
				return (0);
		}
		else
		{
			while (is_valid_red(cmd, k) && k >= 0 && !((cmd[k] == '<' ||
			cmd[k] == '>') && !is_quoted(cmd, k)) )
				k--;
			while (ft_isspace(cmd[k]))
				k--;
			if ((cmd[k] == '<' || cmd[k] == '>') && !is_quoted(cmd, k))
				return (1);
		}
	}

	return 0;
}

int get_redirection(char *line, char **redir, char **cmd)
{
	int i;

	i = -1;
	while (line[++i])
	{
		if (is_redir(line, i))
			*redir = cjoin(*redir, line[i]);
		else
			*cmd = cjoin(*cmd, line[i]);
	}
	return (1);
}


int	add_command(t_minishell *minishell, char *line, t_index index, int i)
{
	char *cmd;
	char *redir;
	char *arg;

	arg = NULL;
	redir = NULL;
	if (!(cmd = ft_substr(line, index.start, (index.end - index.start + 1))))
		return (0);

	if (!get_redirection(cmd, &redir, &arg))
		return (0);

	parse_and_create_command(minishell, arg, redir, i);

//	printf("cmd is: %s\n", arg);
//	printf("redir is: %s\n", redir);


	free(cmd);

	return 1;
}