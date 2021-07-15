#include "minishell.h"

int init_minishell(t_minishell *minishell)
{
	minishell->status = 1;
	minishell->n_cmd = 0;
	return (1);
}

void	handle_signals(int signo) {
  if (signo == SIGINT) {
	write(1, "minishell ~ ", 12);
	write(1, "  \n", 3); // печатает с начала строки \b - смещение влево
	rl_replace_line("", 0);
	rl_on_new_line(); 
	rl_redisplay();
  }
}

int shell_loop(t_minishell *minishell, char **envp)
{
	char *line;

	line = NULL;
	if (signal(SIGINT, handle_signals) == SIG_ERR)
		;// не понятно. наверное здесь нужно передать строку с экрана на печать?
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