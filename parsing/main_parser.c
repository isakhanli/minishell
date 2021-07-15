#include "../minishell.h"

int parse(char *line, t_minishell *minishell, char **envp)
{
	(void)envp;
	int n_cmds;
	int i;
	t_index index;

	i = -1;
	n_cmds = get_n_commands(line);
	minishell->n_cmd = n_cmds;
	minishell->commands = (t_command**) malloc(sizeof (t_command) * n_cmds);
	while (++i < n_cmds)
	{
		index = get_index(minishell, line, i + 1);
		if (!(get_command(minishell, line, index, i)))
			return (0);
	}
	handle_exec2(minishell);
	return (1);
}