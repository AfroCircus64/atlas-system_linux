#ifndef STRACE_H
#define STRACE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include "syscalls.h"

int parent_func(pid_t);
const char *get_syscall_name(size_t syscall_num);

#endif
