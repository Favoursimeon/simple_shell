#include "main.h"

/**
 * check_env - checks if the typed variable is an env variable
 *
 * @h: head of linked list
 * @in: reg_inpute string
 * @data: data structure
 * Return: no return
 */
void check_env(r_var **h, char *in, d_sh *data)
{
	int row, chr, j, lval;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlen(_envr[row] + chr + 1);
				addtion_of_reverseNode(h, j, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[j] == _envr[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}

	addtion_of_reverseNode(h, j, NULL, 0);
}

/**
 * check_vars - check if the typed variable is $$ or $?
 *
 * @h: head of the linked list
 * @in: reg_inpute string
 * @st: last status of the Shell
 * @data: data structure
 * Return: no return
 */
int check_vars(r_var **h, char *in, char *st, d_sh *data)
{
	int i, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(data->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				addtion_of_reverseNode(h, 2, st, lst), i++;
			else if (in[i + 1] == '$')
				addtion_of_reverseNode(h, 2, data->pid, lpd), i++;
			else if (in[i + 1] == '\n')
				addtion_of_reverseNode(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				addtion_of_reverseNode(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				addtion_of_reverseNode(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				addtion_of_reverseNode(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				addtion_of_reverseNode(h, 0, NULL, 0);
			else
				check_env(h, in + i, data);
		}
	}

	return (i);
}

/**
 * replaced_reg_inpute - replaces string into variables
 *
 * @head: head of the linked list
 * @reg_inpute: reg_inpute string
 * @first_reg_inpute: first reg_inpute string (replaced)
 * @nlen: first length
 * Return: replaced string
 */
char *replaced_reg_inpute(r_var **head, char *reg_inpute, char *first_reg_inpute, int nlen)
{
	r_var *indx;
	int i, j, k;

	indx = *head;
	for (j = i = 0; i < nlen; i++)
	{
		if (reg_inpute[j] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				first_reg_inpute[i] = reg_inpute[j];
				j++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (k = 0; k < indx->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->len_val; k++)
				{
					first_reg_inpute[i] = indx->val[k];
					i++;
				}
				j += (indx->len_var);
				i--;
			}
			indx = indx->next;
		}
		else
		{
			first_reg_inpute[i] = reg_inpute[j];
			j++;
		}
	}

	return (first_reg_inpute);
}

/**
 * rep_var - calls functions to replace string into vars
 *
 * @reg_inpute: reg_inpute string
 * @data_shell: data structure
 * Return: replaced string
 */
char *rep_var(char *reg_inpute, d_sh *data_shell)
{
	r_var *head, *indx;
	char *status, *first_reg_inpute;
	int olen, nlen;

	status = aid_func(data_shell->status);
	head = NULL;

	olen = check_vars(&head, reg_inpute, status, data_shell);

	if (head == NULL)
	{
		free(status);
		return (reg_inpute);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	first_reg_inpute = malloc(sizeof(char) * (nlen + 1));
	first_reg_inpute[nlen] = '\0';

	first_reg_inpute = replaced_reg_inpute(&head, reg_inpute, first_reg_inpute, nlen);

	free(reg_inpute);
	free(status);
	empty_of_reverselist(&head);

	return (first_reg_inpute);
}
