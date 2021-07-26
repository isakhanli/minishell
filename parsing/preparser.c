#include "../include/minishell.h"

int	check_pipes(char *str)
{
	int		flag;
	int		len;
	int		i;

	i = -1;
	flag = 0;
	len = ft_strlen(str);
	if (str[0] == '|' || str[len - 1] == '|')
		return (0);
	while (str[++i])
	{
		if (!ft_isspace(str[i]) && str[i] != '|')
			flag = 0;
		if (str[i] == '|' && !is_quoted(str, i))
			flag++;
		if (flag > 1)
			return (0);
	}
	return (1);
}

int	check_redirs3(char *arg, int i, char c)
{
	char	redir;

	redir = arg[i];
	i++;
	if (arg[i] == redir && (arg[i + 1] == redir || arg[i + 1] == c))
		return (0);
	while (ft_isspace(arg[i]))
		i++;
	if ((arg[i] == '|' || arg[i] == c)
		&& !(arg[i - 1] == '<' && arg[i] == '>'))
		return (0);
	if (arg[i] == redir && arg[i - 1] != redir)
		return (0);
	return (1);
}

int	check_redirs2(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '>' && !is_quoted(arg, i)
			&& !check_redirs3(arg, i, '<'))
			return (0);
		if (arg[i] == '<' && !is_quoted(arg, i)
			&& !check_redirs3(arg, i, '>'))
			return (0);
	}
	return (1);
}

int	check_redirs(char *trimmed)
{
	int		len;
	int		i;

	if (!trimmed)
		return (0);
	len = ft_strlen(trimmed);
	if (trimmed[len - 1] == '<' || trimmed[len - 1] == '>')
		return (0);
	i = 0;
	while (trimmed[i] == '<' || trimmed[i] == '>')
		i++;
	if (!trimmed[i])
		return (0);
	if (!check_redirs2(trimmed))
		return (0);
	return (1);
}

int	check_input(char *arg)
{
	char	*trimmed;

	trimmed = ft_strtrim(arg, " ");
	if (!check_pipes(trimmed))
	{
		free(trimmed);
		printf("minishell: syntax error: | - bad token\n");
		g_glob.status = 258;
		return (0);
	}
	if (!check_redirs(trimmed))
	{
		free(trimmed);
		g_glob.status = 258;
		printf("minishell: syntax error: < > - bad token\n");
		return (0);
	}
	free(trimmed);
	return (1);
}
