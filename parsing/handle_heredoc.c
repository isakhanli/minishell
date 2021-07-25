#include "../include/minishell.h"

int	handle_read_and_write(t_command *command, char **file, char **envp)
{
	int	fd;

	handle_dollar_with_quotes(file, envp);
	fd = open(*file, O_CREAT | O_RDWR | O_APPEND, 0666);
	if (fd == -1)
		return (handle_file_error(0, file));
	command->fd_in = fd;
	free(*file);
	return (1);
}

int	is_eof(char *buff, char *eof)
{
	if (!buff || !eof)
		return (0);
	if (ft_strcmp(buff, eof))
		return (1);
	return (0);
}

void	read_input(char *input, char *file, char **envp, int fd)
{
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
			break ;
		if (is_eof(input, file))
			break ;
		if (has_dollar(input))
			handle_dollar_with_quotes(&input, envp);
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
}

int	fork_heredoc(char *input, char *heredoc, char *file, char **envp)
{
	int		fd;
	pid_t	pid;

	signal(SIGINT, handle_ctrl_c);
	pid = fork();
	if (pid == 0)
	{
		g_glob.sig_flag = 1;
		fd = open(heredoc, O_CREAT | O_RDWR | O_TRUNC, 0666);
		read_input(input, file, envp, fd);
		close(fd);
		free(file);
		exit(0);
	}
	if (pid < 0)
		exit(1);
	waitpid(pid, &g_glob.status, 0);
	g_glob.status = WEXITSTATUS(g_glob.status);
	return (1);
}

int	handle_heredoc(t_command *command, char **file, char **envp)
{
	char	*input;
	char	*heredoc;
	int		fd;

	input = NULL;
	heredoc = cjoin(*file, (++g_glob.heredoc_index + 48), 0);
	if (!heredoc)
		return (0);
	fork_heredoc(input, heredoc, *file, envp);
	g_glob.sig_flag = 0;
	signal(SIGINT, handle_signals);
	fd = open(heredoc, O_RDWR, 0666);
	if (fd == -1)
		return (0);
	command->heredoc = heredoc;
	free(*file);
	command->fd_in = fd;
	return (1);
}
