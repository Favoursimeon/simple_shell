#include "main.h"

/**
 * cdir_shell - changes current directory
 *
 * @data_shell: data relevant
 * Return: 1 on success
 */
int cdir_shell(d_sh *data_shell)
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
		cdir_home(data_shell);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cdir_prev(data_shell);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cdir_prev_dir(data_shell);
		return (1);
	}

	cd_to(data_shell);

	return (1);
}
