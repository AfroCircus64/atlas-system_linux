#include <unistd.h>
#include <signal.h>

/**
 * pid_exist - tests if a process exists
 *
 * @pid: PID to check
 *
 * Return: PID
 */
int pid_exist(pid_t pid)
{
	return (kill(pid, 0) == 0);
}
