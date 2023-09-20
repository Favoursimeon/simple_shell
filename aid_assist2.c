#include "main.h"

/**
 * aid_assist - assist information for the builtin assist.
 * Return: no return
 */
void aid_assist(void)
{
	char *assist = "assist: assist [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, assist, _strlen(assist));
	assist = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, assist, _strlen(assist));
	assist = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, assist, _strlen(assist));
}
/**
 * aid_assist_alias - assist info for the builtin alias.
 * Return: no return
 */
void aid_assist_alias(void)
{
	char *assist = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, assist, _strlen(assist));
	assist = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, assist, _strlen(assist));
}
/**
 * aid_assist_cd - assist info for the builtin alias.
 * Return: null
 */
void aid_assist_cd(void)
{
	char *assist = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, assist, _strlen(assist));
	assist = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, assist, _strlen(assist));
}
