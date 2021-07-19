#include "../minishell.h"

int  handle_heredoc(t_command *command, char *raw_fname, char **envp)
{
	char	*file;
	char	*input;
	int		fd;
	int		status;
	pid_t	pid;

	input = NULL;
	file = NULL;

	parse_file_name(raw_fname, &file, envp);
	g_var = 1;
	signal(SIGINT, handle_sig2);
	pid = fork();

	open_file(file,)

	if (pid == 0)
	{
		fd = open("heredoc", O_CREAT | O_RDWR | O_TRUNC, 0666);

		while (!is_eof(input, file))
		{
			input = readline("> ");
			if (!is_eof(input, file))
			{
				write(fd, input, ft_strlen(input));
				write(fd, "\n", 1);
			}
			free(input);
		}
		close(fd);
		free(file);
		exit(0);
	}

	waitpid(pid, &status, 0);

//	signal(SIGINT, handle_signals);
	g_var = 0;
	fd = open("heredoc", O_RDWR, 0666);
	command->fd_in = fd;
	return (1);
}