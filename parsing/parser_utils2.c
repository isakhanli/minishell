#include "../include/minishell.h"

int	get_end(t_minishell *minishell, char *line, int i)
{
	int	j;
	int	n;

	j = 0;
	n = 0;
	if (minishell->n_cmd == i)
		return ((int)ft_strlen(line) - 1);
	else
	{
		while (line[j])
		{
			if (line[j] == '|' && !is_quoted(line, j))
				n++;
			if (n == i)
				break ;
			j++;
		}
	}
	return (j - 1);
}

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

int	get_var_value(char **value, char *var, char **envp)
{
	int		i;
	int		len_var;
	char	*temp;

	i = 0;
	len_var = ft_strlen(var);
	temp = *value;
	while (envp[i])
	{
		if ((!ft_strncmp(envp[i], var, len_var)
				&& envp[i][len_var] == '='))
		{
			*value = ft_substr(envp[i], len_var + 1,
					   (int)ft_strlen(envp[i]) - len_var);
			free(temp);
			if (!(*value))
				return (0);
			break ;
		}
		i++;
	}
	return (1);
}

int	handle_status_code(char **current, int *i)
{
	char	*temp;
	char	*temp2;

	temp = ft_itoa(g_glob.status);
	if (*current)
	{
		temp2 = *current;
		*current = ft_strjoin(*current, temp);
		free(temp2);
		free(temp);
	}
	else
		*current = temp;
	(*i) += 2;
	return (1);
}

int	handle_status_code2(char **current, int *i)
{
	char	*temp;
	char	*temp2;

	temp2 = *current;
	temp = ft_itoa(g_glob.status);
	if (*current)
	{
		*current = ft_strdup(temp2 + *i);
		free(temp2);
		*current = ft_strjoin(temp, *current);
		free(temp);
	}
	else
		*current = temp;
	(*i) -= 2;
	return (1);
}
