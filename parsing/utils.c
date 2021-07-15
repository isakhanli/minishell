#include "../minishell.h"

int 	save_arg(t_list **head, char **arg)
{
	char *temp;

	if (!(temp = ft_strdup(*arg)))
		return (0);

	free(*arg);
	*arg = NULL;
	ft_lstadd_back(head, ft_lstnew(temp));
	return (1);
}

int ft_isspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

char *cjoin(char *line, char c)
{
	int	len;
	int	i;
	char	*new;

	i = 0;
	len = (int)ft_strlen(line);
	new = (char*)malloc(sizeof(char) * (len + 2));

	if (!new)
		return (NULL);
	if (line)
	{
		while (line[i])
		{
			new[i] = line[i];
			i++;
		}
		free(line);
	}
	new[i] = c;
	new[i + 1] = '\0';
	return (new);
}


int is_quoted(char *str, int j)
{
	int i;
	char quote;
	int open = 1;

	i = 0;
	while (str[i] && i < j)
	{
		if ((str[i] == '\'' || str[i] == '\"') && open == 1)
		{
			quote = str[i];
			open = -open;
		}
		else if (str[i] == quote && open == -1)
		{
			open = -open;
			quote = 0;
		}
		i++;
	}
	if (open == 1)
		return 0;
	return 1;
}


//void printarr(char **str)
//{
//	int i;
//
//	i = 0;
//	while (str[i])
//	{
//		ft_putstr_fd(str[i], 1);
//		ft_putchar_fd('\n', 1);
//		i++;
//	}
//}

//void print_list(t_list *head)
//{
//	t_list *current = head;
//
//	while (current != NULL) {
//		printf("%s\n", (char*)current->content);
//		current = current->next;
//	}
//}