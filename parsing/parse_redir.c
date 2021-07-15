#include "../minishell.h"

int parse_file_name(char *raw_fname, char **file, char **envp)
{
	int i;
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
			temp =  ft_strdup((raw_fname + i));
			get_dollar2(&temp, &i, envp);
			if (*file)
				*file = ft_strjoin(*file, temp);
			else
				*file = temp;
			i++;
		}
		else
			handle_other(raw_fname, &i, file);
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
	}
	command->fd_in = fd;

//	printf("file is ~ %s\n", file);
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

int  handle_heredoc(t_command *command, char *raw_fname, char **envp)
{
	char	*file;
	int		fd;
	char	*input;

	input = NULL;
	file = NULL;


	parse_file_name(raw_fname, &file, envp);
	fd = open("heredoc", O_CREAT | O_RDWR | O_TRUNC, 0666);

	while (!is_eof(input, file))
	{
		input = readline("> ");
		if (!is_eof(input, file))
		{
			write(fd, input, ft_strlen(input));
			write(fd, "\n", 1);
		}
	}
	close(fd);

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

	parse_file_name(raw_fname, &file, envp);

	if ((fd = open(file, O_CREAT | O_RDWR, 0666)) != -1)
		command->fd_out = fd;

//	printf("file is ~ %s\n", file);
	return (1);
}

int save_and_get_out_fd2(t_command *command, char *raw_fname, char **envp)
{
	char	*file;
	int		fd;
	fd = 1;

	file = NULL;

	parse_file_name(raw_fname, &file, envp);

	if ((fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0666)) != -1)
		command->fd_out = fd;

//	printf("file is ~ %s\n", file);
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
		save_and_get_out_fd(command, file, envp);
	}
	return 1;
}

int create_redir(t_command *command, char *redir, int *i, char **envp)
{
	(void)command;
	if (redir[*i] == '<')
		create_in_redir(command, redir, i, envp);
	else
		create_out_redir(command, redir, i, envp);

	return 1;
}

int handle_redir(t_command *command, char *redir, char **envp)
{
	(void)command;
	(void)envp;

	int i;

	i = 0;
	command->fd_out = 1;
	command->fd_in = 0;

	while (redir[i])
	{
		if (is_redir_sym(redir, &i))
		{
			create_redir(command, redir, &i, envp);
		}
	}

	return (1);
}

