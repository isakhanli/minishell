#include "../minishell.h"

int 	get_var(char **var, char *str, int k)
{
	int		start;

	start = k;
	while (ft_isalnum(str[k]) && str[k])
		k++;
	*var = ft_substr(str, start, k - start);
	if (!(*var))
		return (0);
	return (1);
}

int		get_var_value(char **value, char *var, char **envp)
{
	int		i;
	int		len_var;

	i = 0;
	len_var = ft_strlen(var);
	while (envp[i])
	{
		if ((!ft_strncmp(envp[i], var, len_var) &&
			 envp[i][len_var] == '='))
		{
			*value = ft_substr(envp[i], len_var + 1,
									(int)ft_strlen(envp[i]) - len_var);
			if (!(*value))
				return (0);
			break;
		}
		i++;
	}
	return (1);
}

int		get_dollar2(char **str, int *i, char **envp)
{
	char	*var;
	char	*var_value;
	char	*temp;

	var_value = NULL;
	temp = *str;
	if (!(get_var(&var, *str, 1)))
		return 0;
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
	if(var)
		free(var);
	return (1);
}

char	*replace_dollar_value(char *str, char *var, int start, int len)
{
	char *temp1;
	char *temp2;
	char *temp3;

	if (!(temp1 = ft_strdup(str)))
		return (NULL);
	temp1[start] = '\0';
	if (!(temp2 = ft_strjoin(temp1, var)))
	{
		free(temp1);
		return (NULL);
	}
	if (!(temp3 = ft_strjoin(temp2, (temp1 + start + len + 1))))
	{
		free(temp1);
		free(temp2);
		return (NULL);
	}
	free(temp1);
	free(temp2);
	return temp3;
}

int		get_dollar(char **str, int *i, char **envp)
{
	char	*var;
	char	*var_value;
	int		k = *i;

	var = NULL;
	var_value = NULL;
	if (!(get_var(&var, *str, k + 1)))
		return (0);
	if (!(get_var_value(&var_value, var, envp)))
		return 0;
	if (!ft_isalnum(*(*str + k + 1)))
	{
		if (!(*str = replace_dollar_value(*str, "$", k, ft_strlen(var))))
			return (0);
	}
	else if (var_value)
	{
		if (!(*str = replace_dollar_value(*str, var_value, k, ft_strlen(var))))
			return (0);
	}
	else if(!var_value)
	{
		if (!(*str = replace_dollar_value(*str, "", k, ft_strlen(var))))
			return (0);
	}
	*i += ft_strlen(var_value);

	if (var)
		free(var);
	if (var_value)
		free(var_value);

	return 1;
}

int		handle_dollar_with_quotes(char **str, char **envp)
{
	int i;

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
	return 1;
}

//int just_dollar(char *str)
//{
//	while (*str)
//	{
//		if (*str != '$')
//
//	}
//}


int		handle_status_code(char **current, int *i)
{
	char *temp2 = ft_itoa(status);

	if (*current)
		*current = ft_strjoin(*current, temp2);
	else
		*current = temp2;
	(*i) += 2;
	return (1);
}

int 	handle_dollar(char *arg, char **current, int *i, char **envp)
{
	char *temp;

	temp = NULL;

	if (arg[*i + 1] == '?')
		return handle_status_code(current, i);
	if (ft_isdigit(arg[*i + 1]))
	{
		(*i) += 2;
		return 1;
	}
	else if (ft_isspace(arg[*i + 1]) || !arg[*i + 1] || arg[*i + 1] == '$')
		*current = cjoin(*current, '$');
	else
	{
		temp = ft_strdup((arg + *i));
//		if (!just_dollars(temp))

//		get_dollar(current, i, envp);

		get_dollar2(&temp, i, envp);
		if (*current && temp)
			*current = ft_strjoin(*current, temp);
		else if (temp)
			*current = temp;
	}
	(*i)++;
	return (1);
}