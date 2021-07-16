#include "../minishell.h"

// ◦ echo with option -n
// ◦ cd with only a relative or absolute path
// ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options

void	define_builtin(t_minishell *minishell)
{
	minishell->builtin[0].func = "echo";
	minishell->builtin[1].func = "cd";
	minishell->builtin[2].func = "pwd";
	minishell->builtin[3].func = "export";
	minishell->builtin[4].func = "unset";
	minishell->builtin[5].func = "env";
	minishell->builtin[6].func = "exit";
}

int		builtin_echo(t_minishell *minishell)
{
	(void)minishell;
	return (1);
}

int		builtin_cd(t_minishell *minishell)
{
	(void)minishell;
	return (1);
}

int		builtin_pwd(t_minishell *minishell)
{
	(void)minishell;
	return (1);
}

int		builtin_export(t_minishell *minishell)
{
	(void)minishell;
	return (1);
}

int		builtin_unset(t_minishell *minishell)
{
	(void)minishell;
	return (1);
}

int		builtin_env(t_minishell *minishell)
{
	(void)minishell;
	return (1);
}

int		builtin_exit(t_minishell *minishell)
{
	(void)minishell;
	return (1);
}

int		handle_builtin(t_minishell *minishell)
{
	if (minishell->commands[0]->arg[0] == minishell->builtin[0].func)
		builtin_echo(minishell);
	else if (minishell->commands[0]->arg[0] == minishell->builtin[1].func)
		builtin_cd(minishell);
	else if (minishell->commands[0]->arg[0] == minishell->builtin[2].func)
		builtin_pwd(minishell);
	else if (minishell->commands[0]->arg[0] == minishell->builtin[3].func)
		builtin_export(minishell);
	else if (minishell->commands[0]->arg[0] == minishell->builtin[4].func)
		builtin_unset(minishell);
	else if (minishell->commands[0]->arg[0] == minishell->builtin[5].func)
		builtin_env(minishell);
	else if (minishell->commands[0]->arg[0] == minishell->builtin[6].func)
		builtin_exit(minishell);
	return (0);
}