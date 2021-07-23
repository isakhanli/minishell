#include "../minishell.h"

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
	{
		free(var);
		return (0);
	}
	if (var_value)
	{
		free(temp);
		*str = var_value;
	}
	else
		*str = NULL;
	*i += ft_strlen(var);
	if (var)
		free(var);
	return (1);
}

int	handle_replace(char **str, int k, char *var, char *var_value)
{
	if (ft_isspace(*(*str + k + 1)) || !(*(*str + k + 1)))
	{
		*str = replace_dollar_value(*str, "$", k, ft_strlen(var));
		if (!*str)
			return (0);
	}
	else if (var_value)
	{
		*str = replace_dollar_value(*str, var_value, k, ft_strlen(var));
		if (!*str)
			return (0);
	}
	else if (!var_value)
	{
		*str = replace_dollar_value(*str, "", k, ft_strlen(var));
		if (!*str)
			return (0);
	}
	return (1);
}

int	get_dollar(char **str, int *i, char **envp)
{
	char	*var;
	char	*var_value;

	var = NULL;
	var_value = NULL;
	if (!(get_var(&var, *str, *i + 1)))
		return (0);
	if (!(get_var_value(&var_value, var, envp)))
		return (0);
	if (!(handle_replace(str, *i, var, var_value)))
		return (0);
	*i += ft_strlen(var_value);
	if (var)
		free(var);
	if (var_value)
		free(var_value);
	return (1);
}

int	handle_dollar_with_quotes(char **str, char **envp)
{
	int	i;

	i = 0;
	while (*(*str + i))
	{
		if (*(*str + i) == '$')
		{
			if (!(get_dollar(str, &i, envp)))
				return (0);
		}
		i++;
	}
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
			*current = ft_strjoin(*current, temp);
		else if (temp)
			*current = temp;
	}
	(*i)++;
	return (1);
}
