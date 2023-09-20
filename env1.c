#include "main.h"

/**
 * comp_env - compares env variables names
 * with the name passed.
 * @nenv: name of the environment variable
 * @name: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int comp_env(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * _getenv - get an environment variable
 * @name: name of the environment variable
 * @_environ: environment variable
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *_getenv(const char *name, char **_environ)
{
	char *pointerr_env;
	int i, mov;

	/* Initialize pointerr_env value */
	pointerr_env = NULL;
	mov = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (i = 0; _environ[i]; i++)
	{
		/* If name and env are equal */
		mov = comp_env(_environ[i], name);
		if (mov)
		{
			pointerr_env = _environ[i];
			break;
		}
	}

	return (pointerr_env + mov);
}

/**
 * _env - prints the evironment variables
 *
 * @data_shell: data relevant.
 * Return: 1 on success.
 */
int _env(d_sh *data_shell)
{
	int i, j;

	for (i = 0; data_shell->_environ[i]; i++)
	{

		for (j = 0; data_shell->_environ[i][j]; j++)
			;

		write(STDOUT_FILENO, data_shell->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	data_shell->status = 0;

	return (1);
}
