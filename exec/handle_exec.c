#include "../minishell.h"

int		handle_exec(t_minishell *minishell, t_command *command, int odd[],
					   int even[], int i)
{

	pid_t pid;
	(void)even;
//	int mystdin = dup(0);
//	int mystout = dup(1);

	if (command->fd_out <= 0)
		command->fd_out = 1;

	printf("cmd is %s\n", command->arg[0]);

	pid = fork();
	if (pid == 0)
	{
		printf("out is: %d\n", command->fd_out);
		printf("in is: %d\n", command->fd_in);
//		dup2(command->fd_in, 0);
//		dup2(command->fd_out, 1);

		if (i == 1)
		{
			dup2(odd[1], 1);
			close(odd[0]);
		}
		else if (i == minishell->n_cmd)
		{
			if (i % 2 == 0)
			{
				dup2(odd[0], 0);
				close(odd[1]);
			}
			else
			{
				dup2(even[0], 0);
				close(odd[1]);
			}
		}
		else
		{
			if (i % 2 == 0)
			{
				dup2(odd[0], 0);
				dup2(even[1], 1);
				close(odd[1]);
				close(even[0]);
			}
			else
			{
				dup2(even[0], 0);
				dup2(odd[1], 1);
				close(odd[0]);
				close(even[1]);
			}
		}



		execve(command->arg[0], command->arg, minishell->envp);
		printf("%s: command not found\n", command->arg[0]);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		printf("error\n");
	}
	else
	{
		wait(NULL);
		if (i == 1)
		{
			close(odd[1]);
		}
		else if (i == minishell->n_cmd)
		{
			if (i % 2 == 0)
			{
				close(odd[0]);
			}
			else
			{
				close(even[0]);
			}
		}
		else
		{
			if (i % 2 == 0)
			{
				close(odd[0]);
				close(even[1]);
			} else
			{
				close(odd[1]);
				close(even[0]);
			}
		}

//		dup2(0, mystdin);
//		dup2(1, mystout);
//		if (command->fd_in != 0)
//			close(command->fd_in);
//		if(command->fd_out != 1)
//			close(command->fd_out);
	}
	return 1;
}
