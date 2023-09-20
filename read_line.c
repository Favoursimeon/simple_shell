#include "main.h"

/**
 * call_lines - reads the reg_inpute string.
 *
 * @i_eof: return value of getline function
 * Return: reg_inpute string
 */
char *call_lines(int *i_eof)
{
	char *reg_inpute = NULL;
	size_t bufsize = 0;

	*i_eof = get_line(&reg_inpute, &bufsize, stdin);

	return (reg_inpute);
}
