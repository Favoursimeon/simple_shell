#include "main.h"

/**
 * get_lines - assigns the line var for get_line
 * @linepointerr: Buffer that store the reg_inpute str
 * @buffer: str that is been called to line
 * @n: size of line
 * @j: size of buffer
 */
void get_lines(char **linepointerr, size_t *n, char *buffer, size_t j)
{

	if (*linepointerr == NULL)
	{
		if  (j > BUFSIZE)
			*n = j;

		else
			*n = BUFSIZE;
		*linepointerr = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*linepointerr = buffer;
	}
	else
	{
		_strcpy(*linepointerr, buffer);
		free(buffer);
	}
}
/**
 * get_line - Read inpt from stream
 * @linepointerr: buffer that stores the reg_inpute
 * @n: size of linepointerr
 * @stream: stream to read from
 * Return: The number of bytes
 */
ssize_t get_line(char **linepointerr, size_t *n, FILE *stream)
{
	int i;
	static ssize_t reg_inpute;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (reg_inpute == 0)
		fflush(stream);
	else
		return (-1);
	reg_inpute = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && reg_inpute == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && reg_inpute != 0)
		{
			reg_inpute++;
			break;
		}
		if (reg_inpute >= BUFSIZE)
			buffer = _realloc(buffer, reg_inpute, reg_inpute + 1);
		buffer[reg_inpute] = t;
		reg_inpute++;
	}
	buffer[reg_inpute] = '\0';
	get_lines(linepointerr, n, buffer, reg_inpute);
	retval = reg_inpute;
	if (i != 0)
		reg_inpute = 0;
	return (retval);
}
