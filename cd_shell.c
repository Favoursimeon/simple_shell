#include "main.h"

/**
 * cd_shell - changes current directory
 *
 * @data_shell: data relevant
 * Return: 1 on success
 */
int cd_shell(d_sh *data_shell)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = data_shell->args[1];

	if (dir != NULL)
	{
		ishome = _strcmp("$HOME", dir);
		ishome2 = _strcmp("~", dir);
		isddash = _strcmp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		cd_to_home(data_shell);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_previous(data_shell);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_dot(data_shell);
		return (1);
	}

	cd_to(data_shell);

	return (1);
}
