#include "../minishell.h"

int parse(char *line, t_minishell *minishell, char **envp)
{
	(void)envp;
	int n_cmds;
	int i;
	t_index index;

	n_cmds = get_n_commands(line);
	minishell->n_cmd = n_cmds;

	minishell->commands = (t_command**) malloc(sizeof (t_command) * n_cmds);

	i = 0;


	int fd[minishell->n_cmd - 1];


	pipe(fd);

//	int odd[2];
//	int even[2];
//
//	if (minishell->n_cmd == 2)
//		pipe(odd);
//	if (minishell->n_cmd > 2)
//	{
//		pipe(odd);
//		pipe(even);
//	}
	int odd[2];
	int even[2];

	while (i < n_cmds)
	{
		odd[0] = fd[0];
		odd[1] = fd[1];
		even[0] = fd[2];
		even[1] = fd[3];

		index = get_index(minishell, line, i + 1);
		add_command(minishell, line, index, i);


		handle_exec(minishell, minishell->commands[i], odd,even, i + 1);


		i++;
	}
	return (1);
}