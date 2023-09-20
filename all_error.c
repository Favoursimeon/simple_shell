#include "main.h"

/**
 * rep_string - counts the repetitions of a char
 *
 * @reg_inpute: reg_inpute string
 * @i: index
 * Return: repetitions
 */
int rep_string(char *reg_inpute, int i)
{
	if (*(reg_inpute - 1) == *reg_inpute)
		return (rep_string(reg_inpute - 1, i + 1));

	return (i);
}

/**
 * find_synt_err - finds syntax errors
 *
 * @reg_inpute: reg_inpute string
 * @i: index
 * @last: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int find_synt_err(char *reg_inpute, int i, char last)
{
	int count;

	count = 0;
	if (*reg_inpute == '\0')
		return (0);

	if (*reg_inpute == ' ' || *reg_inpute == '\t')
		return (find_synt_err(reg_inpute + 1, i + 1, last));

	if (*reg_inpute == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*reg_inpute == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = rep_string(reg_inpute, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*reg_inpute == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = rep_string(reg_inpute, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (find_synt_err(reg_inpute + 1, i + 1, *reg_inpute));
}

/**
 * first_char - finds index of the first char
 *
 * @reg_inpute: reg_inpute string
 * @i: index
 * Return: 1 if there is an error. 0 in other case.
 */
int first_char(char *reg_inpute, int *i)
{

	for (*i = 0; reg_inpute[*i]; *i += 1)
	{
		if (reg_inpute[*i] == ' ' || reg_inpute[*i] == '\t')
			continue;

		if (reg_inpute[*i] == ';' || reg_inpute[*i] == '|' || reg_inpute[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * write_synt_err - prints when a syntax error is found
 *
 * @data_shell: data structure
 * @reg_inpute: reg_inpute string
 * @i: index of the error
 * @bool: to control msg error
 * Return: no return
 */
void write_synt_err(d_sh *data_shell, char *reg_inpute, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (reg_inpute[i] == ';')
	{
		if (bool == 0)
			msg = (reg_inpute[i + 1] == ';' ? ";;" : ";");
		else
			msg = (reg_inpute[i - 1] == ';' ? ";;" : ";");
	}

	if (reg_inpute[i] == '|')
		msg = (reg_inpute[i + 1] == '|' ? "||" : "|");

	if (reg_inpute[i] == '&')
		msg = (reg_inpute[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = aid_func(data_shell->counter);
	length = _strlen(data_shell->av[0]) + _strlen(counter);
	length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, data_shell->av[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * check_syntax_error - intermediate function to
 * find and print a syntax error
 *
 * @data_shell: data structure
 * @reg_inpute: reg_inpute string
 * Return: 1 if there is an error. 0 in other case
 */
int check_syntax_error(d_sh *data_shell, char *reg_inpute)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = first_char(reg_inpute, &begin);
	if (f_char == -1)
	{
		write_synt_err(data_shell, reg_inpute, begin, 0);
		return (1);
	}

	i = find_synt_err(reg_inpute + begin, 0, *(reg_inpute + begin));
	if (i != 0)
	{
		write_synt_err(data_shell, reg_inpute, begin + i, 1);
		return (1);
	}

	return (0);
}
