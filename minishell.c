#include "./minishell.h"

int init_minishell(t_minishell *minishell)
{
	minishell->status = 1;
	minishell->n_cmd = 0;
	return (1);
}

int shell_loop(t_minishell *minishell, char **envp)
{
	char *line;

	line = NULL;
	while(minishell->status)
	{
		line = readline("minishell ~ ");
		add_history(line);
		if (line[0])
			parse(line, minishell, envp);
		free(line);
	}
	return (1);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_minishell minishell;
	minishell.envp = envp;
	init_minishell(&minishell);
	shell_loop(&minishell, envp);

	return (1);
}