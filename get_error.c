#include "main.h"

/**
 * get_error - calls the error according the builtin, syntax or permission
 * @data_shell: data structure that contains arguments
 * @eval: error value
 * Return: error
 */
int get_error(d_sh *data_shell, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = err_ver(data_shell);
		break;
	case 126:
		error = error_path_126(data_shell);
		break;
	case 127:
		error = error_not_found(data_shell);
		break;
	case 2:
		if (_strcmp("exit", data_shell->args[0]) == 0)
			error = shell_err(data_shell);
		else if (_strcmp("cd", data_shell->args[0]) == 0)
			error = error_get_cd(data_shell);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	data_shell->status = eval;
	return (eval);
}
