#include "minishell.h"

int init_minishell(t_minishell *minishell)
{
	minishell->status = 1;
	minishell->n_cmd = 0;
	return (1);
}

void	handle_signals(int signo)
{
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
		line = readline("\033[32;1mminishell ~ \033[m");
		if (ft_isprint(line[0]))
			add_history(line);
		if (line[0])
			parse(line, minishell);
		free(line);
		// заменил на инициализацию, чтобы не закрывался шел после исполнения...
		//free_minishell(minishell);
		init_minishell(minishell);
	}

	return (1);
}

int 	count_array_lines(char **arr)
{
	int		i;

	i = 0;
	while (arr[++i])
		i++;
	return (i);
}

char	**define_env(char **envp)
{
	int		i;
	char	**arr;

	i = -1;
	arr = ft_calloc(sizeof(char *), count_array_lines(envp) + 1);
	while (envp[++i])
		arr[i] = ft_strdup(envp[i]);
	return (arr);
}


int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_minishell minishell;
	minishell.envp = define_env(envp);
	(void)envp;
	//if (signal(SIGINT, handle_signals) == SIG_ERR)
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
	signal(SIGSEGV, handle_signals);
	init_minishell(&minishell);
	shell_loop(&minishell);
	return (1);
}