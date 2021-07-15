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

int		handle_exec2(t_minishell *minishell)
{
	int fd[minishell->n_cmd - 1][2];
	int status;
	int i;
	pid_t  pid;
	create_pipe(minishell->n_cmd - 1, fd);

	i = -1;
	while  ( ++i < minishell->n_cmd)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i != 0)
				dup2(fd[i - 1][0], 0);
			if (i != minishell->n_cmd - 1)
				dup2(fd[i][1], 1);
			close_pipes(minishell->n_cmd - 1, fd);
			execve(minishell->commands[i]->arg[0], minishell->commands[i]->arg,
				   minishell->envp);
		}
	}
	close_pipes(minishell->n_cmd - 1, fd);
	waitpid(pid,&status,0);
	return (1);
}

