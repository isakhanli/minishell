#include "../include/minishell.h"

pid_t	execute_fork(t_minishell *minishell, int i, int fd[][2])
{
	pid_t	pid;

	binarize(minishell, minishell->commands[i]);
	g_glob.sig_flag = 1;
	pid = fork();
	if (pid == 0 && !minishell->commands[i]->file_error)
	{
		handle_pipes_redirs(minishell, i, fd);
		close_pipes(minishell->n_cmd - 1, fd);
		execve(minishell->commands[i]->arg[0], minishell->commands[i]->arg,
			   minishell->envp);
		handle_exit(minishell->commands[i]);
	}
	if (pid < 0)
		exit(1);
	return (pid);
}

pid_t 	execute_builtin(t_minishell *minishell, int i, int fd[][2])
{
	int		stdin;
	int		stdout;
	int		ret;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		stdin = dup(0);
		stdout = dup(1);
		handle_pipes_redirs(minishell, i, fd);
		ret = handle_builtin(minishell->commands[i]->arg, minishell, 0);
		dup2(stdin, 0);
		dup2(stdout, 1);
		exit(ret);
	}
	if (pid < 0)
		exit(1);
	return (pid);
}

int	execute_builtin2(t_minishell *minishell, int i)
{
	int		stdin;
	int		stdout;
	int		ret;

	stdin = dup(0);
	stdout = dup(1);
	if (minishell->commands[i]->fd_in > 0)
		dup2(minishell->commands[i]->fd_in, 0);
	if (minishell->commands[i]->fd_out > 1)
		dup2(minishell->commands[i]->fd_out, 1);
	ret = handle_builtin(minishell->commands[i]->arg, minishell, 0);
	dup2(stdin, 0);
	dup2(stdout, 1);
	g_glob.status = ret;
	return (1);
}

int	handle_exec(t_minishell *minishell)
{
	int		fd[1024][2];
	int		i;
	pid_t	pid[1024];

	i = -1;
	create_pipe(minishell->n_cmd - 1, fd);
	while (++i < minishell->n_cmd)
	{
		if (minishell->commands[i]->arg
			&& is_builtin(minishell->commands[i]->arg[0]))
			pid[i] = execute_builtin(minishell, i, fd);
		else if (minishell->commands[i]->arg)
			pid[i] = execute_fork(minishell, i, fd);
	}
	close_pipes(minishell->n_cmd - 1, fd);
	i = -1;
	while (++i < minishell->n_cmd)
	{
		if (pid[i] > 0)
			waitpid(pid[i], &g_glob.status, 0);
	}
	g_glob.status = WEXITSTATUS(g_glob.status);
	g_glob.sig_flag = 0;
	return (1);
}
