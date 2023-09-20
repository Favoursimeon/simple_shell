#include "main.h"

/**
 * is_execute - finds all_builtins and commands
 *
 * @data_shell: data relevant (args)
 * Return: 1 on success.
 */
int is_execute(d_sh *data_shell)
{
	int (*all_builtin)(d_sh *data_shell);

	if (data_shell->args[0] == NULL)
		return (1);

	all_builtin = get_all_builtin(data_shell->args[0]);

	if (all_builtin != NULL)
		return (all_builtin(data_shell));

	return (comand_exec(data_shell));
}
