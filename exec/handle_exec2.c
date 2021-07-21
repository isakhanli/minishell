#include "../minishell.h"

int create_pipe(int size, int fd[][2])
{
	int i;

	i = 0;
	while (i < size)
	{
		pipe(fd[i]);
		i++;
	}
	return (1);
}

int close_pipes(int size, int fd[][2])
{
	int i;

	i = 0;
	while (i < size)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	return (1);
}

void 	handle_exit(char *str)
{
	(void) str;
	if (errno == 13)
	{
		ft_putstr_fd("Permission denied\n", 2);
		exit(126);
	}
	else if (errno == 2)
	{
		ft_putstr_fd("you are drunk go home: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" command not found \n", 2);
		exit(127);
	}
	exit(1);
}

void handle_pipes_redirs(t_minishell *minishell, int i, int fd[][2])
{
	if (minishell->commands[i]->fd_in > 0)
		dup2(minishell->commands[i]->fd_in, 0);
	else if (i != 0 && minishell->commands[i]->fd_in <= 0)
		dup2(fd[i - 1][0], 0);
	if (minishell->commands[i]->fd_out > 1)
		dup2(minishell->commands[i]->fd_out, 1);
	else if (i != minishell->n_cmd - 1 && minishell->commands[i]->fd_out
									 <= 1)
		dup2(fd[i][1], 1);
}



pid_t execute_fork(t_minishell *minishell, int i, int fd[][2])
{
	pid_t	pid;

	binarize(minishell, minishell->commands[i]);
	g_flag = 1;
	g_flag2 = minishell->commands[i]->flag;

	pid = fork();
	if (pid == 0 && !minishell->commands[i]->file_error)
	{
		handle_pipes_redirs(minishell, i, fd);
		close_pipes(minishell->n_cmd - 1, fd);
		execve(minishell->commands[i]->arg[0], minishell->commands[i]->arg,
			   minishell->envp);
		handle_exit(minishell->commands[i]->arg[0]);
	}
	if (pid < 0)
		exit(1);
	return (pid);
}

int is_builtin(char *str)
{
	if (ft_strcmp(str, "pwd") || ft_strcmp(str, "echo")
		|| ft_strcmp(str, "exit") || ft_strcmp(str, "env")
		|| ft_strcmp(str, "cd") || ft_strcmp(str, "export")
		|| ft_strcmp(str, "unset"))
		return (1);
	return 0;
}

void	execute_builtin(t_minishell *minishell, int i, int fd[][2])
{
	int stdin;
	int stdout;

	stdin = dup(0);
	stdout = dup(1);
	handle_pipes_redirs(minishell, i, fd);
	handle_builtin(minishell->commands[i]->arg, minishell);
	dup2(stdin, 0);
	dup2(stdout, 1);
}

int		handle_exec(t_minishell *minishell)
{
	int		fd[minishell->n_cmd - 1][2];
	int		status;
	int		i;
	pid_t	pid[minishell->n_cmd - 1];

	i = -1;
	create_pipe(minishell->n_cmd - 1, fd);
	test = 1;
	while  ( ++i < minishell->n_cmd)
	{
		if (is_builtin(minishell->commands[i]->arg[0]))
			execute_builtin(minishell, i, fd);
		else
			pid[i] = execute_fork(minishell, i, fd);
	}
	close_pipes(minishell->n_cmd - 1, fd);
	i = -1;
	while (++i < minishell->n_cmd)
	{
		if (pid[i] > 0)
			waitpid(pid[i], &status, 0);
	}
	g_flag = 0;
//	g_flag2 = 0;
	return (1);
}