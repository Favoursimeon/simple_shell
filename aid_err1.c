#include "main.h"

/**
 * strcat_cd - function that concatenates the message for cd error
 *
 * @data_shell: data relevant (directory)
 * @msg: message to print
 * @error: output message
 * @ver_str: counter lines
 * Return: error message
 */
char *strcat_cd(d_sh *data_shell, char *msg, char *error, char *ver_str)
{
	char *rejected_flag;

	_strcpy(error, data_shell->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, data_shell->args[0]);
	_strcat(error, msg);
	if (data_shell->args[1][0] == '-')
	{
		rejected_flag = malloc(3);
		rejected_flag[0] = '-';
		rejected_flag[1] = data_shell->args[1][1];
		rejected_flag[2] = '\0';
		_strcat(error, rejected_flag);
		free(rejected_flag);
	}
	else
	{
		_strcat(error, data_shell->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * error_get_cd - error message for cd command in get_cd
 * @data_shell: data relevant (directory)
 * Return: Error message
 */
char *error_get_cd(d_sh *data_shell)
{
	int length, len_id;
	char *error, *ver_str, *msg;

	ver_str = aid_func(data_shell->counter);
	if (data_shell->args[1][0] == '-')
	{
		msg = ": Rejected  option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(data_shell->args[1]);
	}

	length = _strlen(data_shell->av[0]) + _strlen(data_shell->args[0]);
	length += _strlen(ver_str) + _strlen(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = strcat_cd(data_shell, msg, error, ver_str);

	free(ver_str);

	return (error);
}

/**
 * error_not_found - generic error message for command not found
 * @data_shell: data relevant (counter, arguments)
 * Return: Error message
 */
char *error_not_found(d_sh *data_shell)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aid_func(data_shell->counter);
	length = _strlen(data_shell->av[0]) + _strlen(ver_str);
	length += _strlen(data_shell->args[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, data_shell->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, data_shell->args[0]);
	_strcat(error, ": can't be found\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * shell_err - generic error message for exit in get_exit
 * @data_shell: data relevant (counter, arguments)
 *
 * Return: Error message
 */
char *shell_err(d_sh *data_shell)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aid_func(data_shell->counter);
	length = _strlen(data_shell->av[0]) + _strlen(ver_str);
	length += _strlen(data_shell->args[0]) + _strlen(data_shell->args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, data_shell->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, data_shell->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, data_shell->args[1]);
	_strcat(error, "\n\0");
	free(ver_str);

	return (error);
}
