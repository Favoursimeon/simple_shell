#include "main.h"

/**
 * gassist - function that retrieves assist messages according all_builtin
 * @data_shell: data structure (args and reg_inpute)
 * Return: Return 0
*/
int gassist(d_sh *data_shell)
{

	if (data_shell->args[1] == 0)
		aid_assist_all();
	else if (_strcmp(data_shell->args[1], "setenv") == 0)
		aid_assist_setenv();
	else if (_strcmp(data_shell->args[1], "env") == 0)
		aid_free_ver();
	else if (_strcmp(data_shell->args[1], "unsetenv") == 0)
		aid_assist_unsetenv();
	else if (_strcmp(data_shell->args[1], "assist") == 0)
		aid_assist();
	else if (_strcmp(data_shell->args[1], "exit") == 0)
		aid_assist_dismiss();
	else if (_strcmp(data_shell->args[1], "cd") == 0)
		aid_assist_cd();
	else if (_strcmp(data_shell->args[1], "alias") == 0)
		aid_assist_alias();
	else
		write(STDERR_FILENO, data_shell->args[0],
		      _strlen(data_shell->args[0]));

	data_shell->status = 0;
	return (1);
}
