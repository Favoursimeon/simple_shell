#include "main.h"

/**
 * swap_some_characters - swaps | and & for non-printed chars
 *
 * @input: input string
 * @bool: type of swap
 * Return: swapped string
 */
char *swap_some_characters(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}

			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}

/**
 * add_separators - add separators and command lines in the lists
 *
 * @head_s: head of separator list
 * @head_l: head of command lines list
 * @input: input string
 * Return: no return
 */
void add_separators(seperate_list **head_s, line_list **head_l, char *input)
{
	int i;
	char *line;

	input = swap_some_characters(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			put_seperate_list(head_s, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			put_seperate_list(head_s, input[i]);
			i++;
		}
	}

	line = _strtok(input, ";|&");
	do {
		line = swap_some_characters(line, 1);
		add_line_node_end(head_l, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * go_next - go to the next command line stored
 *
 * @list_s: separator list
 * @list_l: command line list
 * @data_shell: data structure
 * Return: no return
 */
void go_next(seperate_list **list_s, line_list **list_l, d_sh *data_shell)
{
	int loop_sep;
	seperate_list *ls_s;
	line_list *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (data_shell->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * divide_the_cmd - splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @data_shell: data structure
 * @input: input string
 * Return: 0 to exit, 1 to continue
 */
int divide_the_cmd(d_sh *data_shell, char *input)
{

	seperate_list *head_s, *list_s;
	line_list *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	add_separators(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		data_shell->input = list_l->line;
		data_shell->args = split_line(data_shell->input);
		loop = exec_line(data_shell);
		free(data_shell->args);

		if (loop == 0)
			break;

		go_next(&list_s, &list_l, data_shell);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_seperate_list(&head_s);
	free_line_list(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * split_line - tokenizes the input string
 *
 * @input: input string.
 * Return: string splitted.
 */
char **split_line(char *input)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = _reallocdp(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[i] = token;
	}

	return (tokens);
}
