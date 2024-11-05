#ifndef SIGNALS_H
#define SIGNALS_H


#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

void sigint_handler(int signum);

int handle_signal(void);
void (*current_handler_signal(void))(int);
int handle_sigaction(void);

#endif
