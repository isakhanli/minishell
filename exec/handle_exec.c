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

	i = -1;
	create_pipe(minishell->n_cmd - 1, fd);
	while  ( ++i < minishell->n_cmd)
	{
//		printf("fd in is %d\n", minishell->commands[i]->fd_in);
//		printf("fd out is %d\n", minishell->commands[i]->fd_out);
		pid = fork();
		if (pid == 0)
		{
			if (minishell->commands[i]->fd_in > 0)
				dup2(minishell->commands[i]->fd_in, 0);
			if (minishell->commands[i]->fd_out > 0)
				dup2(minishell->commands[i]->fd_out, 1);

			if (i != 0 && minishell->commands[i]->fd_in <= 0)
			{
				dup2(fd[i - 1][0], 0);
			}
			if (i != minishell->n_cmd - 1 && minishell->commands[i]->fd_out
			<= 0)
			{
				dup2(fd[i][1], 1);
			}
			close_pipes(minishell->n_cmd - 1, fd);
			execve(minishell->commands[i]->arg[0], minishell->commands[i]->arg,
				   minishell->envp);
			printf("minishell: %s : command not found\n",
				   minishell->commands[i]->arg[0]);
		}
	}
	close_pipes(minishell->n_cmd - 1, fd);
	waitpid(pid,&status,0);
	return (1);
}

