#include "../minishell.h"

int parse_file_name(char *raw_fname, char **file, char **envp)
{
	int i;
	char *temp2;

	i = 0;
	while(raw_fname[i])
	{
		while (ft_isspace(raw_fname[i]))
			i++;
		if (raw_fname[i] == '\'')
			handle_single_quote(raw_fname, &i, file);
		else if (raw_fname[i] == '\"')
		{
			handle_double_quote(raw_fname, &i, file, envp);
		}
		else if (raw_fname[i] == '$')
		{
			char *temp;
			if (ft_isspace(raw_fname[i + 1]) || !raw_fname[i + 1])
			{
				*file = cjoin(*file, '$');
				return (1);
			}
			temp =  ft_strdup((raw_fname + i));
			get_dollar2(&temp, &i, envp);
			if (*file && temp)
			{
				temp2 = *file;
				*file = ft_strjoin(*file, temp);
				free(temp2);
			}
			else if (temp)
				*file = temp;
			if (!temp)
			{
				error_file = 1;
				write(2, "ambiguous redirect\n", 19);
				return (0);
			}
			i++;
		}
		else
			handle_rest(raw_fname, &i, file);
	}

	return 1;

}

int  save_and_get_in_fd(t_command *command, char *raw_fname, char **envp)
{
	char	*file;
	int		fd;

	fd = 0;


	file = NULL;

	parse_file_name(raw_fname, &file, envp);

	if ((fd = open(file, O_RDONLY, 0666)) == -1)
	{
		printf("%s\n", strerror(errno));
		command->file_error = 1;

	}
	command->fd_in = fd;

	free(file);

//	printf("file is ~ %s\n", file);
	return (1);
}

int  handle_read_and_write(t_command *command, char *raw_fname, char **envp)
{
	char	*file;
	int		fd;

	fd = 0;
	file = NULL;

	parse_file_name(raw_fname, &file, envp);
	fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0666);

	command->fd_in = fd;
	free(file);

	return (1);
}


int is_eof(char *buff, char *eof)
{
	if (!buff || !eof)
		return (0);
	if (ft_strncmp(buff, eof, ft_strlen(eof)) == 0)
		return (1);
	return (0);
}

int has_dollar(char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int handle_heredoc_dollar(char **input, char **envp)
{
	int i;

	i = 0;
	while (*(*input + i))
	{
		if (*(*input + i) == '$')
			get_dollar(input, &i, envp);
		i++;
	}
	return 1;
}

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
	signal(SIGINT, handle_sig2);
	pid = fork();
	if (pid == 0)
	{
		g_flag = 1;
		fd = open("heredoc", O_CREAT | O_RDWR | O_TRUNC, 0666);
		while (1)
		{
			input = readline("> ");
			if (input == NULL)
				break;
			if(is_eof(input, file))
				break;
			if (has_dollar(input))
				handle_heredoc_dollar(&input, envp);
			write(fd, input, ft_strlen(input));
			write(fd, "\n", 1);
			free(input);
		}
		close(fd);
		free(file);
		exit(0);
	}

	waitpid(pid, &status, 0);

	g_flag = 0;
	signal(SIGINT, handle_signals);

	fd = open("heredoc", O_RDWR, 0666);
	command->fd_in = fd;
	return (1);
}


int save_and_get_out_fd(t_command *command, char *raw_fname, char **envp)
{
	char	*file;
	int		fd;
	fd = 1;

	file = NULL;

	if (!(parse_file_name(raw_fname, &file, envp)))
		return (0);

	if ((fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0666)) != -1)
		command->fd_out = fd;

	free(file);
//	printf("file is ~ %s\n", file);
	return (1);
}

int save_and_get_out_fd2(t_command *command, char *raw_fname, char **envp)
{
	char	*file;
	int		fd;

	fd = 1;
	file = NULL;
	if (!(parse_file_name(raw_fname, &file, envp)))
		return (0);

	if ((fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0666)) != -1)
		command->fd_out = fd;

	free(file);

	return (1);
}

int is_redir_sym(char *red, int *i)
{
	if ((red[*i] == '<' || red[*i] == '>') && !is_quoted(red, *i))
		return (1);
	return (0);
}

int create_in_redir(t_command *command, char *redir, int *i, char **envp)
{
	int k;
	char *file;

	if (redir[*i + 1] == '<')
	{
		(*i) += 2;
		k = *i;
		while (redir[*i] && !is_redir_sym(redir, i))
			(*i)++;
		file = ft_substr(redir, k, (*i - k));
//		printf("in file is %s\n", file);
		handle_heredoc(command, file, envp);
	}
	else if (redir[*i + 1] == '>')
	{
		(*i) += 2;
		k = *i;
		while (redir[*i] && !is_redir_sym(redir, i))
			(*i)++;
		file = ft_substr(redir, k, (*i - k));
		handle_read_and_write(command, file, envp);
	}
	else
	{
		(*i)++;
		k = *i;
		while (redir[*i] && !is_redir_sym(redir, i))
			(*i)++;
		file = ft_substr(redir, k, (*i - k));
//		printf("in file is %s\n", file);
		save_and_get_in_fd(command, file, envp);
	}

	free(file);
	return 1;
}



int create_out_redir(t_command *command, char *redir, int *i, char **envp)
{
	(void)command;
	int k;
	char *file;

	if (redir[*i + 1] == '>')
	{
		(*i) += 2;
		k = *i;
		while (redir[*i] && !is_redir_sym(redir, i))
			(*i)++;
		file = ft_substr(redir, k, (*i - k));
//		printf("in file is %s\n", file);
		save_and_get_out_fd2(command, file, envp);

	}
	else
	{
		(*i)++;
		k = *i;
		while (redir[*i] && !is_redir_sym(redir, i))
			(*i)++;
		file = ft_substr(redir, k, (*i - k));
//		printf("out file is %s\n", file);
		if (!(save_and_get_out_fd(command, file, envp)))
			return (0);
	}
	free(file);
	return 1;
}

int create_redir(t_command *command, char *redir, int *i, char **envp)
{
	if (redir[*i] == '<')
		create_in_redir(command, redir, i, envp);
	else
	{
		create_out_redir(command, redir, i, envp);
	}

	return 1;
}

int handle_redir(t_command *command, char *redir, char **envp)
{
	int i;

	i = 0;
	command->fd_out = 1;
	command->fd_in = 0;

	while (redir[i])
	{
		if (is_redir_sym(redir, &i))
		{
			if (!(create_redir(command, redir, &i, envp)))
				return (0);
		}
	}
	free(redir);
	return (1);
}

