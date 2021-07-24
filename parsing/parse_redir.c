#include "../include/minishell.h"

int	get_in_fd(t_command *command, char **file, char **envp)
{
	int	fd;

	handle_dollar_with_quotes(file, envp);
	fd = open(*file, O_RDONLY, 0666);
	if (fd == -1)
	{
		printf("%s\n", strerror(errno));
		command->file_error = 1;
	}
	command->fd_in = fd;
	free(*file);
	return (1);
}

int	get_out_fd(t_command *command, char **file, char **envp,
			   int flag)
{
	int	fd;

	handle_dollar_with_quotes(file, envp);
	if (flag == 1)
	{
		fd = open(*file, O_CREAT | O_RDWR | O_TRUNC, 0666);
		if (fd == -1)
			return (0);
	}
	else
	{
		fd = open(*file, O_CREAT | O_RDWR | O_APPEND, 0666);
		if (fd == -1)
			return (0);
	}
	command->fd_out = fd;
	free(*file);
	return (1);
}

int	create_in_redir(t_command *command, char *redir, int *i, char **envp)
{
	char	*file;
	int		j;

	j = *i + 1;
	if (redir[*i + 1] == '<' || redir[*i + 1] == '>')
	{
		(*i) += 2;
		get_file(redir, &file, i, *i);
		if (redir[j] == '<')
			handle_heredoc(command, &file, envp);
		else
			handle_read_and_write(command, &file, envp);
	}
	else
	{
		(*i)++;
		get_file(redir, &file, i, *i);
		get_in_fd(command, &file, envp);
	}
	return (1);
}

int	create_out_redir(t_command *command, char *redir, int *i, char **envp)
{
	char	*file;

	if (redir[*i + 1] == '>')
	{
		(*i) += 2;
		get_file(redir, &file, i, *i);
		get_out_fd(command, &file, envp, 0);
	}
	else
	{
		(*i)++;
		get_file(redir, &file, i, *i);
		get_out_fd(command, &file, envp, 1);
	}
	return (1);
}

int	handle_redir(t_command *command, char *redir, char **envp)
{
	int	i;

	i = 0;
	command->fd_out = 1;
	command->fd_in = 0;
	while (redir[i])
	{
		if (redir[i] == '<' && is_redir_sym(redir, i))
			create_in_redir(command, redir, &i, envp);
		else if (redir[i] == '>' && is_redir_sym(redir, i))
			create_out_redir(command, redir, &i, envp);
	}
	free(redir);
	return (1);
}
