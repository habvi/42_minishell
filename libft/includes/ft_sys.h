#ifndef FT_SYS_H
# define FT_SYS_H

# include <sys/errno.h>
# include <dirent.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <termios.h>

# define SYS_ERROR	(-1)
# define TTY_ERROR	0

/* alloc */
void			*x_malloc(size_t size);

/* write */
ssize_t			x_write(int fd, const void *buf, size_t nbyte);

/* signal */
int				x_access(const char *path, int mode);
int				x_unlink(const char *path);

/* signal */
sig_t			x_signal(int sig, sig_t func);
int				x_sigaction(int sig, \
							const struct sigaction *restrict act, \
							struct sigaction *restrict oact);
int				x_kill(pid_t pid, int sig);

/* pipe, fork, exec */
pid_t			x_fork(void);
pid_t			x_wait(int *stat_loc);
pid_t			x_waitpid(pid_t pid, int *stat_loc, int options);
int				x_execve(const char *path, \
						char *const argv[], \
						char *const envp[]);
int				x_dup(int fd);
int				x_dup2(int fd, int fd2);
int				x_pipe(int fd[2]);

/* file */
// todo : open(const char *path, int oflag, ...);
int				x_open(const char *path, int oflag);
int				x_close(int fd);
ssize_t			x_read(int fd, void *buf, size_t nbyte);

/* dir */
char			*x_getcwd(char *buf, size_t size);
int				x_chdir(const char *path);
DIR				*x_opendir(const char *filename);
struct dirent	*x_readdir(DIR *dirp);
int				x_closedir(DIR *dirp);

/* tty */
int				x_isatty(int fd);
char			*x_ttyname(int fd);

/* set,get attr */
int				x_tcgetattr(int fd, struct termios *termios_p);
int				x_tcsetattr(int fd, \
							int optional_actions, \
							const struct termios *termios_p);

/* not yet used */
//printf, wait3, wait4
//sigemptyset, sigaddset,
//stat, lstat, fstat
//ttyslot, ioctl,
//getenv, tgetent, tgetflag,
//tgetnum, tgetstr, tgoto, tputs

#endif