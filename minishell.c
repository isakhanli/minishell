#include "minishell.h"


int init_minishell(t_minishell *minishell)
{
	minishell->status = 1;
	minishell->n_cmd = 0;
	minishell->flag = 1;
	error_file = 0;


	return (1);
}

int just_space(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (0);
		line++;
	}
	return (1);
}

int	shell_loop(t_minishell *minishell)
{
	char *line;
	status = 0;

	line = NULL;
	while(minishell->status)
	{
		line = readline("\033[32;1mminishell ~ \033[m");
		if (line == NULL)
			break;
		if (line[0])
			add_history(line);
		if (line[0] && !just_space(line) && check_input(line))
			parse(line, minishell);
		if (line)
			free(line);

		init_minishell(minishell);
//		free_minishell(minishell);
		g_flag = 0;
	}

	return (1);
}

int 	count_array_lines(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
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
	g_flag = 0;
	g_flag2 = 0;
	signal(SIGQUIT, handle_signals);
	signal(SIGINT, handle_signals);
	init_minishell(&minishell);
	shell_loop(&minishell);
	return (1);
}