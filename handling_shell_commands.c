#include "mycustom.h"

/**
 * file_exe_cmd - Determines if a file is an executable command.
 * @info: The info struct.
 * @path: Path to the file.
 *
 * Description:
 *   This function checks whether the specified path
 *   points to an executable file.
 *
 * Return: 1 if true, 0 otherwise.
 */
int file_exe_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;

	/* Check if the path is valid and get file status */
	if (!path || stat(path, &st))
		return (0);
	/* Check if the file is a regular file (executable) */
	if (st.st_mode & S_IFREG)
		return (1);

	return (0);
}

/**
 * replicate_characters - Duplicates characters.
 * @pathstr: The PATH string.
 * @start_idx: Starting index.
 * @stop_idx: Stopping index.
 *
 * Description:
 *   This function creates and returns a buffer containing a duplicate
 *   of the specified portion of the PATH string.
 *
 * Return: Pointer to the new buffer.
 */
char *replicate_characters(char *pathstr, int start_idx, int stop_idx)
{
	static char buf[1024];
	int src_index = 0, dest_index = 0;

	/* Copy characters from start index to stop index (excluding ':') */
	for (dest_index = 0, src_index = start_idx;
			src_index < stop_idx; src_index++)
		if (pathstr[src_index] != ':')
			buf[dest_index++] = pathstr[src_index];
	buf[dest_index] = 0;

	return (buf);
}

/**
 * finding_string_path - Finds the command in the PATH string.
 * @info: The info struct.
 * @pathstr: The PATH string.
 * @cmd: The command to find.
 *
 * Description:
 *   This function searches for the specified command in the PATH string,
 *   returning the full path if found, or NULL if not found.
 *
 * Return: Full path of the command if found, otherwise NULL.
 */
char *finding_string_path(info_t *info, char *pathstr, char *cmd)
{
	int src_index = 0, current_position = 0;
	char *path;
	/* Check if PATH string is provided */
	if (!pathstr)
		return (NULL);
	/* Check if the command starts with "./" and is an executable file */
	if ((my_strlen(cmd) > 2) && begin_here(cmd, "./"))
	{
		if (file_exe_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		/* Check for the end of the PATH string or a path separator ':' */
		if (!pathstr[src_index] || pathstr[src_index] == ':')
		{
			/* Duplicate characters from current position to src_index */
			path = replicate_characters(pathstr, current_position, src_index);
			/* Append the command to the path */
			if (!*path)
				my_strcat(path, cmd);
			else
			{
				my_strcat(path, "/");
				my_strcat(path, cmd);
			}
			/* Check if the resulting path is an executable file */
			if (file_exe_cmd(info, path))
				return (path);
			/* Break if the end of PATH string is reached */
			if (!pathstr[src_index])
				break;
			/* Update current position to the next character after ':' */
			current_position = src_index;
		}
		/* Move to the next character in PATH string */
		src_index++;
	}

	return (NULL);
}
