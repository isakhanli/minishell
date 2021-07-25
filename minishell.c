#include "./include/minishell.h"

int	init_minishell(t_minishell *minishell)
{
	minishell->n_cmd = 0;
	g_glob.file_error = 0;
	g_glob.sig_flag = 0;
	g_glob.heredoc_index = 0;
	g_glob.file_error = 0;
	return (1);
}

int	shell_loop(t_minishell *minishell)
{
	char	*line;

	line = NULL;
	while(1)
	{
		line = readline("\033[32;1mminishell $ \033[m");
		if (line == NULL)
			break;
		if (line[0])
			add_history(line);
		if (line[0] && !just_space(line) && check_input(line))
			parse(line, minishell);
		if (line)
			free(line);
		init_minishell(minishell);
	}
	return (1);
}

int main(int argc, char **argv, char **envp)
{
	g_glob.status = 0;
	(void)argc;
	(void)argv;
	t_minishell minishell;
	minishell.commands = NULL;
	minishell.envp = define_env(envp);
	signal(SIGQUIT, handle_signals);
	signal(SIGINT, handle_signals);
	init_minishell(&minishell);
	shell_loop(&minishell);
	return (g_glob.status);
}