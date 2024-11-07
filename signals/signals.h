#ifndef SIGNALS_H
#define SIGNALS_H


#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

void sigint_handler(int signum);

int handle_signal(void);
void (*current_handler_signal(void))(int);
int handle_sigaction(void);
void (*current_handler_sigaction(void))(int);
int trace_signal_sender(void);
void sigquit_handler(int signo, siginfo_t *info, void *context);
int description(int argc, char *argv[]);
void sigint_handler(int signum);


#endif
