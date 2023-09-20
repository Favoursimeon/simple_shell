#include "main.h"

/**
 * aid_free_ver - assist information for the builtin env
 * Return: no return
 */
void aid_free_ver(void)
{
	char *assist = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, assist, _strlen(assist));
	assist = "Print the scope of the shell.\n";
	write(STDOUT_FILENO, assist, _strlen(assist));

}
/**
 * aid_assist_setenv - assist info for the builtin setenv
 * Return: no return
 */
void aid_assist_setenv(void)
{

	char *assist = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, assist, _strlen(assist));
	assist = "int replace)\n\t";
	write(STDOUT_FILENO, assist, _strlen(assist));
	assist = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, assist, _strlen(assist));
}
/**
 * aid_assist_unsetenv - assist information for the builtin unsetenv
 * Return: no return
 */
void aid_assist_unsetenv(void)
{
	char *assist = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, assist, _strlen(assist));
	assist = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, assist, _strlen(assist));
}


/**
 * aid_assist_all - Entry point for assist information for the assist builtin
 * Return: no return
 */
void aid_assist_all(void)
{
	char *assist = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, assist, _strlen(assist));
	assist = "These commands are defined internally.Type 'assist' to see the list";
	write(STDOUT_FILENO, assist, _strlen(assist));
	assist = "Type 'assist name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, assist, _strlen(assist));
	assist = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, assist, _strlen(assist));
	assist = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, assist, _strlen(assist));
	assist = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, assist, _strlen(assist));
	assist = "unsetenv [variable]\n";
	write(STDOUT_FILENO, assist, _strlen(assist));
}
/**
 * aid_assist_dismiss - assist information fot the builint exit
 * Return: no return
 */
void aid_assist_dismiss(void)
{
	char *assist = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, assist, _strlen(assist));
	assist = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, assist, _strlen(assist));
	assist = "statusis that of the last command executed\n";
	write(STDOUT_FILENO, assist, _strlen(assist));
}
