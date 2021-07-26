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

void 	handle_exit(t_command *command, char **envp)
{
	struct stat	is_dir;

	if (stat(command->cmd, &is_dir) == 0 && S_ISDIR(is_dir.st_mode)
		&& check_bin(command->cmd))
		exit(error_message("is directory", command->cmd, 126));
	if (errno == 13)
		exit(error_message(NULL, command->cmd, 126));
	if (errno == 8)
		exit(error_message(NULL, command->cmd, 1));
	else
	{
		if (check_bin(command->cmd) || !check_path(envp))
			exit(error_message("no such a file or directory",
					command->cmd, 127));
		else
			exit(error_message("command not found", command->cmd, 127));
	}
}

int	handle_unlink(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (i < minishell->n_cmd)
	{
		if (minishell->commands[i]->heredoc)
		{
			unlink(minishell->commands[i]->heredoc);
			free(minishell->commands[i]->heredoc);
		}
		i++;
	}
	return (1);
}
