#include <stdio.h>
#include <unistd.h>

int	main(void)
{

	chdir("/bin");// todo : move to /usr/bin with chdir("/bin") ??

	printf("path:%s\n", getcwd(NULL, 0));

	char *cmd[] = {"/bin/pwd", NULL};
	execve(cmd[0], cmd, NULL);

//	char *cmd[] = {"/bin/ls", NULL};
//	execve(cmd[0], cmd, NULL);

	return (0);
}
