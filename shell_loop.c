#include "main.h"

/**
 * without_comment - deletes comments from the reg_inpute
 *
 * @in: reg_inpute string
 * Return: reg_inpute without comments
 */
char *without_comment(char *in)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		in = _realloc(in, i, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

/**
 * shell_loop - Loop of shell
 * @data_shell: data relevant (av, reg_inpute, args)
 *
 * Return: no return.
 */
void shell_loop(d_sh *data_shell)
{
	int loop, i_eof;
	char *reg_inpute;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		reg_inpute = call_lines(&i_eof);
		if (i_eof != -1)
		{
			reg_inpute = without_comment(reg_inpute);
			if (reg_inpute == NULL)
				continue;

			if (check_syntax_error(data_shell, reg_inpute) == 1)
			{
				data_shell->status = 2;
				free(reg_inpute);
				continue;
			}
			reg_inpute = rep_var(reg_inpute, data_shell);
			loop = divide_the_comad_exec(data_shell, reg_inpute);
			data_shell->counter += 1;
			free(reg_inpute);
		}
		else
		{
			loop = 0;
			free(reg_inpute);
		}
	}
}
