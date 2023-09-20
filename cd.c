#include "main.h"

/**
 * cd_dot - changes to the parent directory
 *
 * @data_shell: data relevant (environ)
 *
 * Return: no return
 */
void cd_dot(d_sh *data_shell)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, data_shell);
	dir = data_shell->args[1];
	if (_strcmp(".", dir) == 0)
	{
		set_env("PWD", cp_pwd, data_shell);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	rev_string(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			rev_string(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd, data_shell);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", data_shell);
	}
	data_shell->status = 0;
	free(cp_pwd);
}

/**
 * cd_to - changes to a directory given
 * by the user
 *
 * @data_shell: data relevant (directories)
 * Return: no return
 */
void cd_to(d_sh *data_shell)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = data_shell->args[1];
	if (chdir(dir) == -1)
	{
		get_error(data_shell, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, data_shell);

	cp_dir = _strdup(dir);
	set_env("PWD", cp_dir, data_shell);

	free(cp_pwd);
	free(cp_dir);

	data_shell->status = 0;

	chdir(dir);
}

/**
 * cd_previous - changes to the previous directory
 *
 * @data_shell: data relevant (environ)
 * Return: no return
 */
void cd_previous(d_sh *data_shell)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", data_shell->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_env("OLDPWD", cp_pwd, data_shell);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd, data_shell);
	else
		set_env("PWD", cp_oldpwd, data_shell);

	p_pwd = _getenv("PWD", data_shell->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	data_shell->status = 0;

	chdir(p_pwd);
}

/**
 * cd_to_home - changes to home directory
 *
 * @data_shell: data relevant (environ)
 * Return: no return
 */
void cd_to_home(d_sh *data_shell)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", data_shell->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, data_shell);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(data_shell, 2);
		free(p_pwd);
		return;
	}

	set_env("OLDPWD", p_pwd, data_shell);
	set_env("PWD", home, data_shell);
	free(p_pwd);
	data_shell->status = 0;
}
