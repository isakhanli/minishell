#include "minishell.h"

int init_minishell(t_minishell *minishell)
{
	minishell->status = 1;
	minishell->n_cmd = 0;
	return (1);
}

void	handle_signals(int signo) {
	//функция работает, но есть оин косяк
	// если запустить команду, а потом на новой строке нажать ^C, 
	// то подтягивается левая строка. Вывод сбивается
	//тянется какой-то результат вывода, который наверное надо чистить
	if (signo == SIGINT) {  /* обработка ^C */
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \b\b\n", 5);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signo == SIGQUIT) /* обработка ^\   */
	{
		rl_on_new_line(); 
		rl_redisplay();
		rl_replace_line("", 0);
		write(1, "  \b\b", 4);
	}
	else if (signo == SIGSEGV) /* обработка ^D   */
		exit(0);
}

int	shell_loop(t_minishell *minishell)
{
	char *line;

	line = NULL;
	while(minishell->status)
	{

		line = readline("minishell ~ ");
		add_history(line);
		if (line[0])
			parse(line, minishell);
		free(line);
		free_minishell(minishell);
	}

	return (1);
}

/*
// TEST INPUT PARAMS //
int print_main_params(char **arr)
{
	int		i = -1;

	while (arr[++i])
		printf("arr[%d] = %s\n", i, arr[i]);
	return EXIT_SUCCESS;
}
*/
int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_minishell minishell;
	minishell.envp = envp;
	define_builtin(&minishell);
	//print_main_params(minishell.envp);// check env array to be replaced to structure
	//if (signal(SIGINT, handle_signals) == SIG_ERR)
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
	signal(SIGSEGV, handle_signals);
	init_minishell(&minishell);
	shell_loop(&minishell);
	return (1);
}