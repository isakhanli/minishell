#include "../include/minishell.h"

int	free_and_ret(int ret, char **str)
{
	free(*str);
	return (ret);
}

int	get_dollar2(char **str, int *i, char **envp)
{
	char	*var;
	char	*var_value;
	char	*temp;

	var_value = NULL;
	temp = *str;
	if (!(get_var(&var, *str, 1)))
		return (0);
	if (!(get_var_value(&var_value, var, envp)))
		return (free_and_ret(0, &var));
	if (var_value)
	{
		free(temp);
		*str = var_value;
	}
	else
	{
		free(*str);
		*str = NULL;
	}
	*i += ft_strlen(var);
	if (var)
		free(var);
	return (1);
}

int	handle_dollar(char *arg, char **current, int *i, char **envp)
{
	char	*temp;

	temp = NULL;
	if (arg[*i + 1] == '?')
		return (handle_status_code(current, i));
	if (ft_isdigit(arg[*i + 1]))
	{
		(*i) += 2;
		return (1);
	}
	else if (ft_isspace(arg[*i + 1]) || !arg[*i + 1] || arg[*i + 1] == '$')
		*current = cjoin(*current, '$', 1);
	else
	{
		temp = ft_strdup((arg + *i));
		get_dollar2(&temp, i, envp);
		if (*current && temp)
			*current = ft_strjoin2(current, &temp);
		else if (temp)
			*current = temp;
		else
			free(temp);
	}
	(*i)++;
	return (1);
}

int	handle_dollar_with_quotes(char **str, char **envp)
{
	int		i;
	char	*current;
	char	*temp;

	current = NULL;
	temp = *str;
	i = 0;
	while (*(*str + i))
	{
		if (*(*str + i) == '$')
			handle_dollar(*str, &current, &i, envp);
		else
		{
			current = cjoin(current, *(*str + i), 1);
			i++;
		}
	}
	if (current)
		*str = current;
	else
		*str = ft_strdup("");
	free(temp);
	return (1);
}
