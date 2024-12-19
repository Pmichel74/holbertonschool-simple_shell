#include <stdio.h>
#include <unistd.h>

int main ()
{
	int pid_parent;
	int pid_child;

	pid_parent = getppid();
	pid_child = getpid();
	printf("%d,  %d\n", pid_parent, pid_child);
	return (0);
}
