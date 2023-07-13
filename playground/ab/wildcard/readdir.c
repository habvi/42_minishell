#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdbool.h>

// d_type
// DT_DIR : 4
// ディレクトリである。
// DT_REG : 8
// 通常のファイルである。

int main(void)
{
	const char *name = ".";

	DIR *dirp = opendir(name);

	struct dirent *dir;
	while (true)
	{
		dir = readdir(dirp);
		if (!dir)
			break ;
		printf("[%hhu], %s\n", dir->d_type, dir->d_name);
	}

	closedir(dirp);
}
