#include "mycustom.h"

/**
 * _file_history_path - Gets the history file path.
 * @info: Parameter struct containing information
 * needed for file path construction.
 *
 * This function constructs the path to the history file
 * based on the user's home directory.
 * It first obtains the home directory using
 * the `my_getenv` function, then allocates memory
 * for the file path, concatenates the home directory,
 * a forward slash, and the history file name.
 * The resulting string is returned, and the caller
 * is responsible for freeing the allocated memory.
 *
 * Return: Allocated string containing the history file path,
 * or NULL on failure.
 */
char *_file_history_path(info_t *info)
{
	char *buf, *dir;

	dir = my_getenv(info, "HOME=");

	if (!dir)
		return (NULL);

	buf = malloc(sizeof(char) * (my_strlen(dir) + my_strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);

	buf[0] = 0;
	my_strcpy(buf, dir);
	my_strcat(buf, "/");
	my_strcat(buf, HIST_FILE);

	return (buf);
}

/**
 * create_file_history - Creates a file or appends to an existing file.
 * @info: The parameter struct.
 *
 * This function creates a history file or truncates
 * an existing one to write the command history.
 * It uses the `_file_history_path` function to obtain the file path,
 * opens the file, and iterates through the command history,
 * writing each entry to the file. It then closes the file and returns
 * 1 on success, or -1 on failure. The file path memory
 * is freed after opening the file.
 *
 * Return: 1 on success, -1 on failure.
 */
int create_file_history(info_t *info)
{
	ssize_t fd;
	char *filename = _file_history_path(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);

	for (node = info->history; node; node = node->next)
	{
		my_putsfd(node->str, fd);
		my_putfd('\n', fd);
	}
	my_putfd(BUF_FLUSH, fd);
	close(fd);

	return (1);
}

/**
 * history_recall - Reads history from file.
 * @info: The parameter struct.
 *
 * This function reads command history from a file specified
 * by the user's home directory. It uses the `_file_history_path` function
 * to obtain the file path, opens the file, reads the file content
 * into a buffer, and then processes the buffer to create a linked list of
 * command history. The resulting linked list is stored in the `info` struct.
 * The file path memory and buffer memory are freed after processing.
 *
 * Return: Number of history entries read on success, 0 on failure.
 */
int history_recall(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = _file_history_path(info);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			create_list_of_history(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		create_list_of_history(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		remove_first_node(&(info->history), 0);
	history_recounts(info);
	return (info->histcount);
}

/**
 * create_list_of_history - Adds an entry to a history linked list.
 * @info: Structure containing potential arguments.
 * Used to maintain history data.
 * @buf: Buffer containing the history entry to be added.
 * @linecount: The history line count.
 *
 * This function adds a new entry to the linked list of command history.
 * It uses the `append_end_node`
 * function to add the entry to the end of the list.
 * The line count is also updated accordingly.
 *
 * Return: Always 0.
 */
int create_list_of_history(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	append_end_node(&node, buf, linecount);
	if (!info->history)
		info->history = node;

	return (0);
}

/**
 * history_recounts - Renumbers the history linked list after changes.
 * @info: Structure containing potential arguments.
 * Used to maintain history data.
 *
 * This function renumbers the history linked list after changes,
 * updating the 'num' field
 * of each node to represent its position in the list.
 * The histcount is also updated and returned.
 *
 * Return: The new histcount.
 */
int history_recounts(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	return (info->histcount = i);
}
