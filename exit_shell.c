#include "main.h"

/**
 * exit_shell - exits the shell
 *
 * @data_shell: data relevant (status and args)
 * Return: 0 on success.
 */
int exit_shell(d_sh *data_shell)
{
	unsigned int ustatus;
	int is_digit;
	int str_len;
	int big_number;

	if (data_shell->args[1] != NULL)
	{
		ustatus = _atoi(data_shell->args[1]);
		is_digit = _isdigit(data_shell->args[1]);
		str_len = _strlen(data_shell->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_number)
		{
			get_error(data_shell, 2);
			data_shell->status = 2;
			return (1);
		}
		data_shell->status = (ustatus % 256);
	}
	return (0);
}
