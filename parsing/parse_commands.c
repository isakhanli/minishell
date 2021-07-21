#include "../minishell.h"

int handle_rest(char *line, int *i, char **current)
{
	int		k;
	char	*temp;

	k = *i;
	while (!(ft_isspace(line[*i])) && line[*i] && !(line[*i] == '\''
		|| line[*i] == '\"' || line[*i] == '$'))
		(*i)++;
	temp = ft_substr(line, k, (*i - k));
	if (!temp)
		return (0);
	if (*current)
	{
		*current = ft_strjoin(*current, temp);
		free(temp);
		if (!*current)
			return (0);
	}
	else
	{
		*current = ft_strdup(temp);
		free(temp);
		if (*current)
			return (0);
	}
	return 1;
}

char **from_list_to_array(t_list *head)
{
	int		i;
	int		size;
	char	**ret;
	t_list	*current;

	current = head;
	size = ft_lstsize(head);
	i = 0;
	ret = (char**)malloc(sizeof(char*) * (size + 1));
	if (!ret)
		return NULL;
	while (current != NULL)
	{
		ret[i] = ft_strdup((char*)current->content);
		if (!ret[i])
			return (NULL);
		i++;
		current = current->next;
	}
	free_list(head);
	ret[i] = NULL;
	return ret;
}

int	start_parsing(char *arg, int *i, char **current, char **envp, t_list **head)
{
	(void)head;
	if (arg[*i] == '\'')
		handle_single_quote(arg, i, current);
	else if (arg[*i] == '\"')
		handle_double_quote(arg, i, current, envp);
	else if (arg[*i] == '$')
		handle_dollar(arg, current, i, envp);
	else if (!ft_isspace(arg[*i]))
		handle_rest(arg, i, current);
	return (1);
}

char **parse_cmd(char *arg, char **envp)
{
	int		i;
	char	*current;
	t_list	*head;

	i = 0;
	head = NULL;
	current = NULL;
	while(arg[i])
	{
		if (ft_isspace(arg[i]))
		{
			if (current)
				save_arg(&head, &current);
			while (ft_isspace(arg[i]) && arg[i])
				i++;
		}
		else
			start_parsing(arg, &i, &current, envp, &head);
	}
	if (current)
		save_arg(&head, &current);
	free(arg);
	return (from_list_to_array(head));
}

int	parse_and_create_command(t_minishell *minishell, char *arg, char *redir,
								int i)
{
	t_command *command;

	command = (t_command*)malloc((sizeof(t_command)));
	if (!command)
		return (0);
	command->arg = parse_cmd(arg, minishell->envp);
	minishell->commands[i] = command;
	command->fd_in = -1;
	command->fd_out = -1;
	command->file_error = 0;
	if (redir)
	{
		if (!(handle_redir(command, redir, minishell->envp)))
			return (0);
	}
	return (1);
}