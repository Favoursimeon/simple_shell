#include "main.h"

/**
 * free_data - frees data structure
 *
 * @data_shell: data structure
 * Return: no return
 */
void free_data(d_sh *data_shell)
{
	unsigned int i;

	for (i = 0; data_shell->_environ[i]; i++)
	{
		free(data_shell->_environ[i]);
	}

	free(data_shell->_environ);
	free(data_shell->pid);
}

/**
 * set_data - Initialize data structure
 *
 * @data_shell: data structure
 * @av: argument vector
 * Return: no return
 */
void set_data(d_sh *data_shell, char **av)
{
	unsigned int i;

	data_shell->av = av;
	data_shell->input = NULL;
	data_shell->args = NULL;
	data_shell->status = 0;
	data_shell->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	data_shell->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		data_shell->_environ[i] = _strdup(environ[i]);
	}

	data_shell->_environ[i] = NULL;
	data_shell->pid = aid_func(getpid());
}

/**
 * main - Entry point
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	d_sh data_shell;
	(void) ac;

	signal(SIGINT, get_sigint);
	set_data(&data_shell, av);
	shell_loop(&data_shell);
	free_data(&data_shell);
	if (data_shell.status < 0)
		return (255);
	return (data_shell.status);
}
