#include "../minishell.h"


int handle_other(char *line, int *i, char **current)
{
	int k;
	k = *i;

	while (!(ft_isspace(line[*i])) && line[*i] && !(line[*i] == '\'' || line[*i]
																	  == '\"' ))
		(*i)++;

	char *temp = ft_substr(line, k, (*i - k));
	if (*current)
		*current = ft_strjoin(*current, temp);
	else
		*current = ft_strdup(temp);

	return 1;
}

void print_list(t_list *head)
{
	t_list *current = head;

	while (current != NULL) {
		printf("%s\n", (char*)current->content);
		current = current->next;
	}
}

char **from_list_to_array(t_list *head)
{
	t_list *current = head;
	int size;
	size = ft_lstsize(head);

	char **ret;
	int i;

	i = 0;
	ret = (char**)malloc(sizeof(char*) * (size + 1));

	while (current != NULL) {
		ret[i] = ft_strdup((char*)current->content);
		i++;
		current = current->next;
	}
	ret[i] = NULL;
	return ret;
}

void printarr(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

char **parse_cmd(char *arg, char **envp)
{
	int i;
	char *current;
	char **ret;
	t_list *head;
	(void)envp;

	head = NULL;
	current = NULL;
	i = 0;
	while(arg[i])
	{
		if (ft_isspace(arg[i]))
		{
			if (current)
				save_arg(&head, &current);
			while (ft_isspace(arg[i]) && arg[i])
				i++;
		}
		else if (arg[i] == '\'')
			handle_single_quote(arg, &i, &current);
		else if (arg[i] == '\"')
		{
			handle_double_quote(arg, &i, &current, envp);
		}
		else if (arg[i] == '$')
		{
			handle_dollar(arg, &current, &i, envp);
		}
		else if (!ft_isspace(arg[i]))
			handle_other(arg, &i, &current);
	}
	if (current)
	{
		save_arg(&head, &current);
		current = NULL;
	}

	ret = from_list_to_array(head);
	return ret;
}

int	parse_and_create_command(t_minishell *minishell, char *arg, char *redir,
								int i)
{
	t_command *command;

	command = (t_command*)malloc((sizeof(t_command)));

	command->arg = parse_cmd(arg, minishell->envp);

	minishell->commands[i] = command;
	if (redir)
		handle_redir(command, redir, minishell->envp);

	binarize(minishell, command);

//	handle_exec(minishell, command);


	return 1;
}