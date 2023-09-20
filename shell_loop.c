#include "main.h"

/**
 * without_comment - deletes comments from the input
 *
 * @in: input string
 * Return: input without comments
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
 * @data_shell: data relevant (av, input, args)
 *
 * Return: no return.
 */
void shell_loop(d_sh *data_shell)
{
	int loop, i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_line(&i_eof);
		if (i_eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(data_shell, input) == 1)
			{
				data_shell->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, data_shell);
			loop = split_commands(data_shell, input);
			data_shell->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
