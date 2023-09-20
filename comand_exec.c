#include "main.h"

/**
 * is_change_dir - checks ":" if is in the current directory.
 * @path: type char pointer char.
 * @i: type int pointer of index.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int is_change_dir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * comad_loc - locates a command
 *
 * @comad_exec: command name
 * @_environ: environment variable
 * Return: location of the command.
 */
char *comad_loc(char *comad_exec, char **_environ)
{
	char *path, *pointerr_path, *_vou_path, *dir;
	int len_dir, len_comad_exec, i;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (path)
	{
		pointerr_path = string_dup(path);
		len_comad_exec = _strlen(comad_exec);
		_vou_path = _strtok(pointerr_path, ":");
		i = 0;
		while (_vou_path != NULL)
		{
			if (is_change_dir(path, &i))
				if (stat(comad_exec, &st) == 0)
					return (comad_exec);
			len_dir = _strlen(_vou_path);
			dir = malloc(len_dir + len_comad_exec + 2);
			_strcpy(dir, _vou_path);
			_strcat(dir, "/");
			_strcat(dir, comad_exec);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(pointerr_path);
				return (dir);
			}
			free(dir);
			_vou_path = _strtok(NULL, ":");
		}
		free(pointerr_path);
		if (stat(comad_exec, &st) == 0)
			return (comad_exec);
		return (NULL);
	}
	if (comad_exec[0] == '/')
		if (stat(comad_exec, &st) == 0)
			return (comad_exec);
	return (NULL);
}

/**
 * is_chmod - determines if is an executable
 *
 * @data_shell: data structure
 * Return: 0 if is not an executable, other number if it does
 */
int is_chmod(d_sh *data_shell)
{
	struct stat st;
	int i;
	char *reg_inpute;

	reg_inpute = data_shell->args[0];
	for (i = 0; reg_inpute[i]; i++)
	{
		if (reg_inpute[i] == '.')
		{
			if (reg_inpute[i + 1] == '.')
				return (0);
			if (reg_inpute[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (reg_inpute[i] == '/' && i != 0)
		{
			if (reg_inpute[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(reg_inpute + i, &st) == 0)
	{
		return (i);
	}
	get_err(data_shell, 127);
	return (-1);
}

/**
 * chk_err_comad - verifies if user has permissions to access
 *
 * @dir: destination directory
 * @data_shell: data structure
 * Return: 1 if there is an error, 0 if not
 */
int chk_err_comad(char *dir, d_sh *data_shell)
{
	if (dir == NULL)
	{
		get_err(data_shell, 127);
		return (1);
	}

	if (_strcmp(data_shell->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_err(data_shell, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(data_shell->args[0], X_OK) == -1)
		{
			get_err(data_shell, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * comand_exec - executes command lines
 *
 * @data_shell: data relevant (args and reg_inpute)
 * Return: 1 on success.
 */
int comand_exec(d_sh *data_shell)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = is_chmod(data_shell);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = comad_loc(data_shell->args[0], data_shell->_environ);
		if (chk_err_comad(dir, data_shell) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = comad_loc(data_shell->args[0], data_shell->_environ);
		else
			dir = data_shell->args[0];
		execve(dir + exec, data_shell->args, data_shell->_environ);
	}
	else if (pd < 0)
	{
		perror(data_shell->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	data_shell->status = state / 256;
	return (1);
}
