#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int	main(void)
{
	int		 err;
//	char	*path = "/home/user42/42tokyo/minishell/link";

//	printf("1. cd link\n");
	errno = 0;
	chdir("link");
//	chdir(path);
	err = errno;
	printf("path:%s, err:%d, %s\n\n", getcwd(NULL, 0), err, strerror(err));

	printf("2. cd ../srcs/././\n");
	err = errno;

	// pwd    = "/home/user42/42tokyo/minishell/link"
	// arg    = ".."
	// cdpath = "/home/user42/42tokyo/minishell/link/.."
    //        = "/home/user42/42tokyo/minishell"          <- linkなら展開されるので`path_i/../`を削除

	// pwd    = "/home/user42/42tokyo/minishell"
	// arg    = "srcs"
	// cdpath = "/home/user42/42tokyo/minishell/srcs" -> failure

	// pwd    = "/home/user42/42tokyo/minishell/srcs"
	// arg    = "."
	// cdpath = "/home/user42/42tokyo/minishell/srcs/."
	//        = "/home/user42/42tokyo/minishell/srcs"


	// ../../
	// "home/user42/42tokyo/minishell/testdir/ng_or_deleted"

	// "home/user42/42tokyo/minishell/testdir/ng_or_deleted/../"
	// "home/user42/42tokyo/minishell/testdir/"


	// ../../../
	// "home/user42/42tokyo/minishell/testdir/ng/ok"

	// "home/user42/42tokyo/minishell/testdir/ng/ok/.."
	// "home/user42/42tokyo/minishell/testdir/ng"        <- failue


	chdir("/home/user42/42tokyo/minishell/");
	printf("path:%s, err:%d, %s\n\n", getcwd(NULL, 0), err, strerror(err));
	chdir("/home/user42/42tokyo/minishell/srcs");
	printf("path:%s, err:%d, %s\n\n", getcwd(NULL, 0), err, strerror(err));

//	printf("3. cd ../dir3\n");
//	chdir("../dir3");
//	err = errno;
//	printf("path:%s, err:%d, %s\n\n", getcwd(NULL, 0), err, strerror(err));


//	printf("2. cd ../dir3\n");



	return (0);
}
