#include "../include/minishell.h"

int	create_pipe(int size, int fd[][2])
{
	int	i;

	i = 0;
	while (i < size)
	{
		pipe(fd[i]);
		i++;
	}
	return (1);
}

int	close_pipes(int size, int fd[][2])
{
	int	i;

	i = 0;
	while (i < size)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	return (1);
}

void	handle_pipes_redirs(t_minishell *minishell, int i, int fd[][2])
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
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(":", 2);
		ft_putstr_fd(" command not found \n", 2);
		exit(127);
	}
	exit(1);
}

int	is_builtin(char *str)
{
	if (ft_strcmp(str, "pwd") || ft_strcmp(str, "echo")
		|| ft_strcmp(str, "exit") || ft_strcmp(str, "env")
		|| ft_strcmp(str, "cd") || ft_strcmp(str, "export")
		|| ft_strcmp(str, "unset"))
		return (1);
	return (0);
}
