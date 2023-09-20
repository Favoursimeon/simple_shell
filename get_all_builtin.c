#include "main.h"

/**
 * get_all_builtin - all_builtin that pais the command in the arg
 * @comad_exec: command
 * Return: function pointer of the all_builtin command
 */
int (*get_all_builtin(char *comad_exec))(d_sh *)
{
	all_builtin_t all_builtin[] = {
		{ "env", _env },
		{ "exit", dismiss_shell },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cdir_shell },
		{ "assist", gassist },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; all_builtin[i].name; i++)
	{
		if (_strcmp(all_builtin[i].name, comad_exec) == 0)
			break;
	}

	return (all_builtin[i].f);
}
