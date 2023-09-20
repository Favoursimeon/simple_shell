#include "main.h"

/**
 * put_seperate_list - adds a separator found at the end
 * of a seperate_list.
 * @head: head of the linked list.
 * @sep: separator found (; | &).
 * Return: address of the head.
 */
seperate_list *put_seperate_list(seperate_list **head, char seperation)
{
	seperate_list *first, *temp;

	first = malloc(sizeof(seperate_list));
	if (first == NULL)
		return (NULL);

	first->separator = seperation;
	first->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = first;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = first;
	}

	return (*head);
}

/**
 * free_seperate_list - frees a seperate_list
 * @head: head of the linked list.
 * Return: null.
 */
void free_seperate_list(seperate_list **head)
{
	seperate_list *temp;
	seperate_list *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * add_line_node_end - adds a command line at the end
 * of a line_list.
 * @head: head of the linked list.
 * @line: command line.
 * Return: address of the head.
 */
line_list *add_line_node_end(line_list **head, char *line)
{
	line_list *first, *temp;

	first = malloc(sizeof(line_list));
	if (first == NULL)
		return (NULL);

	first->line = line;
	first->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = first;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = first;
	}

	return (*head);
}

/**
 * free_line_list - frees a line_list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_line_list(line_list **head)
{
	line_list *temp;
	line_list *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}
