/*
 * The aim of this program is to help you understand file descriptors.
 * All it does is echo every line it receives on stdin to stdout.
 * Try running it in the background with ./copycat &
 * Note down the PID that gets printed out (or use ps).
 * Once you have the PID, navigate to /proc/<pid>/fd/
 * The files you see, 0, 1 and 2, correspond to the process's stdin, stdout and stderr!
 * Try writing to the processe's stdin from another shell like this:
 *	echo "hello!" > /proc/<pid>/fd/0
 * The message should appear in the shell which originally started the copy cat process!
*/

#include <stdio.h>

int main()
{
	char buf[256];
	while (fgets(buf, 256, stdin) != NULL)
	{
		printf("%s", buf);
	}
	return 0;
}
