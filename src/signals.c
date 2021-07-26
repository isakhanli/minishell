#include "../include/minishell.h"

void	handle_ctrl_c(int signo)
{
	if (signo == SIGINT && g_glob.sig_flag)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		exit(1);
	}
}

void	handle_signals(int signo)
{
	if (signo == SIGQUIT && g_glob.sig_flag)
	{
		write(2, "Quit: 3\n", 8);
		rl_on_new_line();
	}
	if (signo == SIGQUIT && !g_glob.sig_flag)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	if (signo == SIGINT && g_glob.sig_flag)
	{
		write(1, "\n", 1);
		rl_on_new_line();
	}
	if (signo == SIGINT && !g_glob.sig_flag)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_glob.status = 1;
	}
}
