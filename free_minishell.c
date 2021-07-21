#include "./minishell.h"

void	free_list(t_list *head)
{
	t_list *temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->content);
		free(temp);
	}

}

void	free_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	if (arr[i])
		free(arr[i]);
	if (arr)
		free(arr);
}

void	free_commands(t_minishell *minishell)
{
	int i;

	i = 0;
	while (i < minishell->n_cmd)
	{
		free_arr(minishell->commands[i]->arg);
		if (minishell->commands[i])
			free(minishell->commands[i]);
		i++;
	}
	if (minishell->commands)
		free(minishell->commands);
}

void	free_minishell(t_minishell *minishell)
{
	free_commands(minishell);
}