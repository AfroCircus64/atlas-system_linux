#ifndef SIGNALS_H
#define SIGNALS_H


#include <stdio.h>
#include <signal.h>

int handle_signal(void);
void (*current_handler_signal(void))(int);

#endif
