#include "mycustom.h"

/**
 * buffer_input - Reads and buffers chained commands.
 * @info: Parameter struct containing relevant information.
 * @buf: Address of the buffer to store the input.
 * @len: Address of the variable to store the length of the buffer.
 *
 * This function reads input from the standard input and buffers it.
 * It handles chained commands, removes trailing newline characters,
 * updates command history, and checks for command chains.
 *
 * Return: The number of bytes read.
 */
ssize_t buffer_input(info_t *info, char **buf, size_t *len)
{
	ssize_t bytes_read = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		bytes_read = getline(buf, &len_p, stdin);
#else
		bytes_read = buf_getline(info, buf, &len_p);
#endif
		if (bytes_read > 0)
		{
			if ((*buf)[bytes_read - 1] == '\n')
			{
				(*buf)[bytes_read - 1] = '\0';
				bytes_read--;
			}
			info->linecount_flag = 1;
			delete_remarks(*buf);
			create_list_of_history(info, *buf, info->histcount++);
			{
				*len = bytes_read;
				info->cmd_buf = buf;
			}
		}
	}
	return (bytes_read);
}

/**
 * input_minus_newline - Reads a line from the input
 * without the newline character.
 * @info: Parameter struct containing relevant information.
 *
 * This function reads a line from the standard input
 * without including the newline character.
 * It handles command chains and updates the position in the buffer.
 *
 * Return: The number of bytes read.
 */
ssize_t input_minus_newline(info_t *info)
{
	static char *buf;
	static size_t pos_i, pos_j, len;
	ssize_t bytes_read = 0;
	char **ptr = &(info->arg), *buffer_ptr;

	my_putchar(BUF_FLUSH);
	bytes_read = buffer_input(info, &buf, &len);
	if (bytes_read == -1)
		return (-1);
	if (len)
	{
		pos_j = pos_i;
		buffer_ptr = buf + pos_i;

		checking_the_chain(info, buf, &pos_j, pos_i, len);
		while (pos_j < len)
		{
			if (chain_is_true(info, buf, &pos_j))
				break;
			pos_j++;
		}

		pos_i = pos_j + 1;
		if (pos_i >= len)
		{
			pos_i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*ptr = buffer_ptr;
		return (my_strlen(buffer_ptr));
	}

	*ptr = buf;
	return (bytes_read); /* Return the length of the buffer from my_getline() */
}

/**
 * buffer_reading - Reads a buffer.
 * @info: Parameter struct containing relevant information.
 * @buf: Buffer.
 * @pos_i: Size.
 *
 * This function reads a buffer from the input.
 *
 * Return: The number of bytes read.
 */
ssize_t buffer_reading(info_t *info, char *buf, size_t *pos_i)
{
	ssize_t bytes_read = 0;

	if (*pos_i)
		return (0);
	bytes_read = read(info->readfd, buf, READ_BUF_SIZE);
	if (bytes_read >= 0)
		*pos_i = bytes_read;
	return (bytes_read);
}

/**
 * buf_getline - Gets the next line of input from STDIN.
 * @info: Parameter struct containing relevant information.
 * @ptr: Address of the pointer to the buffer, preallocated or NULL.
 * @len: Size of the preallocated buffer if not NULL.
 *
 * This function gets the next line of input from the standard input.
 *
 * Return: The size of the buffer.
 */
int buf_getline(info_t *info, char **ptr, size_t *len)
{
	static char buf[READ_BUF_SIZE];
	static size_t pos_i, len_buf;
	size_t sz;
	ssize_t bytes_read = 0, buffer_size = 0;
	char *buffer_ptr = NULL, *new_ptr = NULL, *c;

	buffer_ptr = *ptr;
	if (buffer_ptr && len)
		buffer_size = *len;
	if (pos_i == len_buf)
		pos_i = len_buf = 0;

	bytes_read = buffer_reading(info, buf, &len_buf);
	if (bytes_read == -1 || (bytes_read == 0 && len_buf == 0))
		return (-1);

	c = my_strchr(buf + pos_i, '\n');
	sz = c ? 1 + (unsigned int)(c - buf) : len_buf;
	new_ptr = mem_realloc(buffer_ptr, buffer_size,
			buffer_size ? buffer_size + sz : sz + 1);
	if (!new_ptr)
		return ((buffer_ptr ? free(buffer_ptr), -1 : -1));

	if (buffer_size)
		my_strncat(new_ptr, buf + pos_i, sz - pos_i);
	else
		my_strncpy(new_ptr, buf + pos_i, sz - pos_i + 1);

	buffer_size += sz - pos_i;
	pos_i = sz;
	buffer_ptr = new_ptr;

	if (len)
		*len = buffer_size;
	*ptr = buffer_ptr;
	return (buffer_size);
}

/**
 * sigintHandler - Blocks ctrl-C.
 * @sn: The signal number.
 *
 * This function handles the SIGINT signal, blocking the interrupt signal.
 *
 * Return: Void.
 */
void sigintHandler(__attribute__((unused)) int sn)
{
	my_puts("\n");
	my_puts("$ ");
	my_putchar(BUF_FLUSH);
}
