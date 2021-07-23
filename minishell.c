#include "minishell.h"

int	init_minishell(t_minishell *minishell)
{
	minishell->n_cmd = 0;
	minishell->flag = 1;
	error_file = 0;
	g_flag = 0;
	g_flag2 = 0;
	g_glob.heredoc_index = 0;
	return (1);
}

int	shell_loop(t_minishell *minishell)
{
	char	*line;

	g_glob.g_status = 1;
	line = NULL;
	while(1)
	{
		line = readline("\033[32;1mminishell ~ \033[m");
		if (line == NULL)
			break;
		if (line[0])
			add_history(line);
		if (line[0] && !just_space(line) && check_input(line))
		{
			parse(line, minishell);
			free_minishell(minishell);
		}
		if (line[0])
			free(line);
		init_minishell(minishell);
	}
	return (1);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_minishell minishell;
	minishell.envp = define_env(envp);
	signal(SIGQUIT, handle_signals);
	signal(SIGINT, handle_signals);
	init_minishell(&minishell);
	shell_loop(&minishell);
	return (1);
}