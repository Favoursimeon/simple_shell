#include "main.h"

/**
 * get_signt - Handle the crtl + c call in prompt
 * @sig: Signal handler
 */
void get_signt(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
