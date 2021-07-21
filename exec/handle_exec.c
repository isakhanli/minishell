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

void 	set_redirections(t_minishell *minishell, int i, int fd[][2])
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
}

pid_t 	run_exec(t_minishell *minishell, int i)
{
	pid_t pid;

	pid = fork();
	g_flag = 1;

	binarize(minishell, minishell->commands[i]);

	if (pid == 0)
	{
		execve(minishell->commands[i]->arg[0], minishell->commands[i]->arg,
			   minishell->envp);
		handle_exit(minishell->commands[i]->arg[0]);
	}
	if (pid < 0)
		exit(1);
	return pid;
}

pid_t 	run_command(t_minishell *minishell, int i)
{


	if (!(handle_builtin(minishell->commands[i]->arg, minishell)))
		return run_exec(minishell, i);
	return 0;
}

int		handle_exec(t_minishell *minishell)
{
	int		fd[minishell->n_cmd - 1][2];
	pid_t	pid[20];
	int		status;
	int		i;

	i = -1;



	create_pipe(minishell->n_cmd - 1, fd);
	while  ( ++i < minishell->n_cmd)
	{
		g_flag2 = minishell->commands[i]->flag;
		set_redirections(minishell, i, fd);
		pid[i] = run_command(minishell, i);
		close_pipes(minishell->n_cmd - 1, fd);
	}
	close_pipes(minishell->n_cmd - 1, fd);
	i = -1;
	while (++i < minishell->n_cmd)
		waitpid(pid[i],&status,0);
	g_flag = 0;
//	g_flag2 = 0;
	return (1);
}

