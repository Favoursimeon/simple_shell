#include "main.h"

/**
 * ghelp - function that retrieves help messages according builtin
 * @data_shell: data structure (args and input)
 * Return: Return 0
*/
int ghelp(d_sh *data_shell)
{

	if (data_shell->args[1] == 0)
		aux_help_general();
	else if (_strcmp(data_shell->args[1], "setenv") == 0)
		aux_help_setenv();
	else if (_strcmp(data_shell->args[1], "env") == 0)
		aux_help_env();
	else if (_strcmp(data_shell->args[1], "unsetenv") == 0)
		aux_help_unsetenv();
	else if (_strcmp(data_shell->args[1], "help") == 0)
		aux_help();
	else if (_strcmp(data_shell->args[1], "exit") == 0)
		aux_help_exit();
	else if (_strcmp(data_shell->args[1], "cd") == 0)
		aux_help_cd();
	else if (_strcmp(data_shell->args[1], "alias") == 0)
		aux_help_alias();
	else
		write(STDERR_FILENO, data_shell->args[0],
		      _strlen(data_shell->args[0]));

	data_shell->status = 0;
	return (1);
}
