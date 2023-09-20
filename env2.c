#include "main.h"

/**
 * copy_info - copies info to create
 * a first env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 *
 * Return: first env or alias.
 */
char *copy_info(char *name, char *value)
{
	char *first;
	int length_name, length_value, len;

	length_name = _strlen(name);
	length_value = _strlen(value);
	len = length_name + length_value + 2;
	first = malloc(sizeof(char) * (len));
	_strcpy(first, name);
	_strcat(first, "=");
	_strcat(first, value);
	_strcat(first, "\0");

	return (first);
}

/**
 * set_env - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @data_shell: data structure (environ)
 * Return: no return
 */
void set_env(char *name, char *value, d_sh *data_shell)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; data_shell->_environ[i]; i++)
	{
		var_env = string_dup(data_shell->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(data_shell->_environ[i]);
			data_shell->_environ[i] = copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	data_shell->_environ = allo_dp(data_shell->_environ, i, sizeof(char *) * (i + 2));
	data_shell->_environ[i] = copy_info(name, value);
	data_shell->_environ[i + 1] = NULL;
}

/**
 * _setenv - compares env variables names
 * with the name passed.
 * @data_shell: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int _setenv(d_sh *data_shell)
{

	if (data_shell->args[1] == NULL || data_shell->args[2] == NULL)
	{
		get_err(data_shell, -1);
		return (1);
	}

	set_env(data_shell->args[1], data_shell->args[2], data_shell);

	return (1);
}

/**
 * _unsetenv - deletes a environment variable
 *
 * @data_shell: data relevant (env name)
 *
 * Return: 1 on success.
 */
int _unsetenv(d_sh *data_shell)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (data_shell->args[1] == NULL)
	{
		get_err(data_shell, -1);
		return (1);
	}
	k = -1;
	for (i = 0; data_shell->_environ[i]; i++)
	{
		var_env = string_dup(data_shell->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, data_shell->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		get_err(data_shell, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; data_shell->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = data_shell->_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(data_shell->_environ[k]);
	free(data_shell->_environ);
	data_shell->_environ = realloc_environ;
	return (1);
}
