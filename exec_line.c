#include "main.h"

/**
 * exec_line - finds builtins and commands
 *
 * @data_shell: data relevant (args)
 * Return: 1 on success.
 */
int exec_line(d_sh *data_shell)
{
	int (*builtin)(d_sh *data_shell);

	if (data_shell->args[0] == NULL)
		return (1);

	builtin = get_builtin(data_shell->args[0]);

	if (builtin != NULL)
		return (builtin(data_shell));

	return (cmd_exec(data_shell));
}
