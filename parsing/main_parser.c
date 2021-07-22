#include "../minishell.h"

int parse(char *line, t_minishell *minishell)
{
	int		n_cmds;
	int		i;
	t_index	index;

	i = -1;
	n_cmds = 0;
	n_cmds = get_n_commands(line);
	minishell->n_cmd = n_cmds;
	minishell->commands = (t_command**) malloc(sizeof (t_command) * n_cmds);
	while (++i < n_cmds)
	{
		index = get_index(minishell, line, i + 1);
		if (!(get_cmd_n_rdr(minishell, line, index, i)))
			return (0);
	}
//	if (n_cmds)
		handle_exec(minishell);
	return (1);
}