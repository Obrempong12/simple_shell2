#include "shell.h"

/**
 * main - entry point of program
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success, otherwise 1
 */
int main(int argc, char **argv)
{
	info_t para[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=w" (fd)
		: "w" (fd));

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_ pinputstr(argv[0]);
				_ pinputstr(": 0: Can't open ");
				_ pinputstr(argv[1]);
				_writchar('\n');
				_writchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		para->readfd = fd;
	}
	populate_env_list(para);
	read_history(para);
	hsh(para, argv);
	return (EXIT_SUCCESS);
}
