#include "_strace.h"

/**
 * main - Main function for strace_1
 *
 * @argc: Argument count
 * @argv: Argument vector
 * @envp: Environment variables
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char *argv[], char *envp[])
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
			exit(1);
		}

		execve(argv[1], &argv[1], envp);
		perror("execve");
		exit(1);
	}

	return (parent_func(child_pid));
}


/**
 * parent_func - Function for the parent process to trace child
 *
 * @child: PID of the child process
 *
 * Return: 0 on success, 1 on failure
 */
int parent_func(pid_t child)
{
	int status;
	struct user_regs_struct regs;

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

		printf("%lld\n", regs.orig_rax);

		if (ptrace(PTRACE_SYSCALL, child, NULL, NULL) == -1)
		{
			perror("ptrace");
			return (1);
		}
	}

	return (0);
}
