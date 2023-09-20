#include "main.h"

/**
 * _memcpy - copies information between void pointers.
 * @first_point: destination pointer.
 * @pointerr: source pointer.
 * @size: size of the first pointer.
 *
 * Return: no return.
 */
void _memcpy(void *first_point, const void *pointerr, unsigned int size)
{
	char *char_point = (char *)pointerr;
	char *first_char_point = (char *)first_point;
	unsigned int i;

	for (i = 0; i < size; i++)
		first_char_point[i] = char_point[i];
}

/**
 * _realloc - reallocates a memory block.
 * @pointerr: pointer to the memory previously allocated.
 * @first_size: size, in bytes, of the allocated space of pointerr.
 * @sec_size: first size, in bytes, of the first memory block.
 *
 * Return: pointerr.
 * if sec_size == first_size, returns pointerr without changes.
 * if malloc fails, returns NULL.
 */
void *_realloc(void *pointerr, unsigned int first_size, unsigned int sec_size)
{
	void *first_point;

	if (pointerr == NULL)
		return (malloc(sec_size));

	if (sec_size == 0)
	{
		free(pointerr);
		return (NULL);
	}

	if (sec_size == first_size)
		return (pointerr);

	first_point = malloc(sec_size);
	if (first_point == NULL)
		return (NULL);

	if (sec_size < first_size)
		_memcpy(first_point, pointerr, sec_size);
	else
		_memcpy(first_point, pointerr, first_size);

	free(pointerr);
	return (first_point);
}

/**
 * allo_dp - reallocates a memory block of a double pointer.
 * @pointerr: double pointer to the memory previously allocated.
 * @first_size: size, in bytes, of the allocated space of pointer.
 * @sec_size: first size, in bytes, of the first memory block.
 *
 * Return: pointer.
 * if sec_size == first_size, returns pointer without changes.
 * if malloc fails, returns NULL.
 */
char **allo_dp(char **pointerr, unsigned int first_size, unsigned int sec_size)
{
	char **first_point;
	unsigned int i;

	if (pointerr == NULL)
		return (malloc(sizeof(char *) * sec_size));

	if (sec_size == first_size)
		return (pointerr);

	first_point = malloc(sizeof(char *) * sec_size);
	if (first_point == NULL)
		return (NULL);

	for (i = 0; i < first_size; i++)
		first_point[i] = pointerr[i];

	free(pointerr);

	return (first_point);
}
