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
	printf("minishell: %s : command not found\n", str);
	if (errno == 13)
		exit(126);
	else if (errno == 2)
		exit(127);
	exit(1);
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

		// проверка на втстроенную функцию здесь?
		if (!(handle_builtin(minishell->commands[i]->arg, minishell)))
		{
			// добавил сюда функцию добавления пути переменной сред к команде
			binarize(minishell, minishell->commands[i]);
			g_flag = 1;
			g_flag2 = minishell->commands[i]->flag;

//			printf("fd in is %d\n", minishell->commands[i]->fd_in);
//			printf("fd out is %d\n", minishell->commands[i]->fd_out);
			pid = fork();

			if (pid == 0 && !minishell->commands[i]->file_error)
			{
				if (minishell->commands[i]->fd_in > 0)
					dup2(minishell->commands[i]->fd_in, 0);
				if (minishell->commands[i]->fd_out > 1)
					dup2(minishell->commands[i]->fd_out, 1);

				if (i != 0 && minishell->commands[i]->fd_in <= 0)
				{
					dup2(fd[i - 1][0], 0);
				}
				if (i != minishell->n_cmd - 1 && minishell->commands[i]->fd_out
				<= 1)
				{
					dup2(fd[i][1], 1);
				}

				close_pipes(minishell->n_cmd - 1, fd);

				execve(minishell->commands[i]->arg[0], minishell->commands[i]->arg,
					minishell->envp);
				handle_exit(minishell->commands[i]->arg[0]);
			}
			if (pid < 0)
				exit(1);
		}
	}
	close_pipes(minishell->n_cmd - 1, fd);
	i = -1;
	while (++i < minishell->n_cmd)
		waitpid(pid,&status,0);
	g_flag = 0;
//	g_flag2 = 0;
	return (1);
}

