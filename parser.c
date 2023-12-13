#include "shell.h"

/**
 * is_cmd - function determines if a file is an executable command
 * @para: the parameter of structure
 * @path: path to the file
 * Return: 1 if true, otherwise 0
 */
int is_cmd(info_t *para, char *path)
{
	struct stat st;

	(void)para;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_characters - function that duplicate characters
 * @strpath: the string PATH
 * @start: start index
 * @stop: stop index
 * Return: pointer to new buffer
 */
char *dup_characters(char *strpath, int start, int stop)
{
	static char buf[1024];
	int m = 0, j = 0;

	for (j = 0, m = start; m < stop; m++)
		if (strpath[m] != ':')
			buf[j++] = strpath[m];
	buf[j] = 0;
	return (buf);
}

/**
 * locate_path - function that locates cmd in the PATH string
 * @para: the parameter of structure
 * @strpath: the PATH string
 * @cmd: the cmd to find
 * Return: full path of cmd if found or NULL
 */
char *locate_path(info_t *para, char *strpath, char *cmd)
{
	int m = 0, curr_pos = 0;
	char *path;

	if (!strpath)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(para, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!strpath[m] || strpath[m] == ':')
		{
			path = dup_chars(strpath, curr_pos, m);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(para, path))
				return (path);
			if (!strpath[m])
				break;
			curr_pos = m;
		}
		m++;
	}
	return (NULL);
}
