#include "main.h"

/**
 * addtion_of_reverseNode -let's you add a variable at the end of the node
 * of a r_var list.
 * @head: head of the linked list.
 * @lvar: length of the variable.
 * @val: value of the variable.
 * @lval: length of the value.
 * Return: address of the head.
 */
r_var *addtion_of_reverseNode(r_var **head, int lvar, char *val, int lval)
{
	r_var *first, *temporaryVariable;

	first = malloc(sizeof(r_var));
	if (first == NULL)
		return (NULL);

	first->len_var = lvar;
	first->val = val;
	first->len_val = lval;

	first->next = NULL;
	temporaryVariable = *head;

	if (temporaryVariable == NULL)
	{
		*head = first;
	}
	else
	{
		while (temporaryVariable->next != NULL)
			temporaryVariable = temporaryVariable->next;
		temporaryVariable->next = first;
	}

	return (*head);
}

/**
 * empty_of_reverselist - frees a r_var list
 * @head: head of the linked list.
 * Return: no return.
 */
void empty_of_reverselist(r_var **head)
{
	r_var *temporaryVariable;
	r_var *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temporaryVariable = curr) != NULL)
		{
			curr = curr->next;
			free(temporaryVariable);
		}
		*head = NULL;
	}
}
