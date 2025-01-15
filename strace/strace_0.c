#include "_strace.h"

/**
 * main - main function for strace
 *
 * @argc: argument count
 * @argv: argument vector
 * @env: environment
 *
 * Return: Success (0)
 */
int main(int argc, char **argv, char *env[])
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s command [args...]\n", argv[0]);
		return (1);
	}

	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		return (1);
	}

	if (child_pid == 0)
	{
		if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1)
		{
			perror("ptrace");
			return (1);
		}

		execve(argv[1], &argv[1], env);
		perror("execve");
		return (1);
	}

	return (parent_func(child_pid));
}


/**
 * parent_func - parent process
 *
 * @child: child process
 *
 * Return: success
 */
int parent_func(pid_t child)
{
	int status;
	struct user_regs_struct regs;
	int entry = 0;

	while (1)
	{
		if (waitpid(child, &status, 0) == -1)
		{
			perror("waitpid");
			return (1);
		}

		if (WIFEXITED(status))
		{
			break;
		}

		if (ptrace(PTRACE_GETREGS, child, NULL, &regs) == -1)
		{
			perror("ptrace");
			return (1);
		}

		if (entry == 0 || entry % 2 != 0)
		{
			fprintf(stderr, "%llu\n", regs.orig_rax);
		}

		if (ptrace(PTRACE_SYSCALL, child, NULL, NULL) == -1)
		{
			perror("ptrace");
			return (1);
		}

		entry++;
	}
	return (0);
}
