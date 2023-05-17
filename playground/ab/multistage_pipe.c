#include <unistd.h> // fork
#include <sys/wait.h> // wait
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include "test.h"

extern char	**environ;

static void	child_proc(int pipefd[2], pid_t pid, char *cmd[])
{
	printf("===  child process start [PID: %d] ===\n", pid);
	close(pipefd[0]);
	close(STDOUT_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
if (execvp(cmd[0], cmd) == EXECVE_ERROR) // forbidden func
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

static void	parent_proc(int pipefd[2], pid_t pid, char *cmd[], char *next_cmd[])
{
	int		status;
	pid_t	wait_pid;

	printf("=== parent process start [PID: %d] ===\n", pid);
	close(pipefd[1]);
	close(STDIN_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	wait_pid = wait(&status);
	if (wait_pid == WAIT_ERROR)
	{
		perror("wait");
		exit(EXIT_FAILURE);
	}
	// last command
	if (*next_cmd == NULL)
	{
		printf("=== parent process last ===\n");
		if (execvp(cmd[0], cmd) == EXECVE_ERROR) // forbidden func
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	// if (WIFEXITED(status))
	// 	printf("\nwait pid: %d, status: %d\n", wait_pid, WEXITSTATUS(status));
	// printf("=== parents process end ===\n");
}

// move next_cmd after "|"
static char	**move_next_command(char **next_cmd)
{
	while (*next_cmd && strcmp(*next_cmd, "|") != 0)
		next_cmd++;
	if (*next_cmd != NULL)
	{
		*next_cmd = NULL;
		next_cmd++;
	}
	return (next_cmd);
}

// fd[0]:read, pipefd[1]:write
int	main(int argc, char *argv[])
{
	int		pipefd[2];
	pid_t	pid;
	char	**cmd;
	char	**next_cmd;

	if (argc == 1)
		return (EXIT_SUCCESS);
	cmd = argv + 1;
	next_cmd = cmd;
	while (true)
	{
		next_cmd = move_next_command(next_cmd);
		// pipe
		if (pipe(pipefd) == PIPE_ERROR)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		// fork, exec
		pid = fork();
		if (pid == FORK_ERROR)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == CHILD_PID)
			child_proc(pipefd, pid, cmd);
		else
			parent_proc(pipefd, pid, cmd, next_cmd);
		cmd = next_cmd;
	}
	return (EXIT_SUCCESS);
}

// ./a.out "/bin/echo" "-e" "aaa\naacc\nbbb\nbbcc\nccc\naabb\nabc" "|" "/bin/grep" "a" "|" "/bin/grep" "c"