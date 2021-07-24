#include "./include/minishell.h"

void	handle_sig2(int sig)
{
	if (sig == SIGINT && g_flag)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		exit(1);
	}
}

void	handle_sig3(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}


void	handle_signals(int sig)
{
	if (sig == SIGQUIT && g_flag)
	{
		write(2, "Quit: 3\n", 8);
		rl_on_new_line();
	}
	if (sig == SIGQUIT && !g_flag)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGINT && g_flag && g_flag2)
	{
		write(1, "\b\b  \b\b", 6); //for cat working
		rl_on_new_line();
	}

	if (sig == SIGINT && g_flag && !g_flag2)
	{
		rl_on_new_line();
	}

	if (sig == SIGINT && !g_flag)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}