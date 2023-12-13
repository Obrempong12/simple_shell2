#include "shell.h"

/**
 * hsh - function that creates main shell loop
 * @para: the parameter
 * @argv: the argument vector
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *para, char **argv)
{
	ssize_t y = 0;
	int in_built_nest = 0;

	while (y != -1 && in_built_nest != -2)
	{
		clear_para(para);
		if (interactive(para))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		y = get_input(para);
		if (y != -1)
		{
			set_para(info, argv);
			in_built_nest = find_built_in(para);
			if (in_built_nest == -1)
				find_cmd(para);
		}
		else if (interactive(para))
			_putchar('\n');
		free_para(para, 0);
	}
	write_history(para);
	free_para(para, 1);
	if (!interactive(para) && para->status)
		exit(para->status);
	if (in_built_nest == -2)
	{
		if (para->err_num == -1)
			exit(para->status);
		exit(para->err_num);
	}
	return (in_built_nest);
}

/**
 * find_in_built - function that locates a built_in command
 * @para: the parameter & return info struct
 *
 * Return: -1 if built_in not found,
 *			0 if built_in executed successfully,
 *			1 if built_in found but not successful,
 *			-2 if built_in signals exit()
 */
int find_in_built(info_t *para)
{
	int m, in_built_nest = -1;
	in_built_table built_intbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (m = 0; built_intbl[m].type; m++)
		if (_strcmp(para->argv[0], built_intbl[m].type) == 0)
		{
			para->line_count++;
			in_built_nest = built_intbl[m].func(para);
			break;
		}
	return (in_built_nest);
}

/**
 * find_cmd - function that finds a command in PATH
 * @para: the parameter
 * Return: void
 */
void find_cmd(info_t *para)
{
	char *path = NULL;
	int m, k;

	para->path = para->argv[0];
	if (para->linecount_flag == 1)
	{
		para->line_count++;
		para->linecount_flag = 0;
	}
	for (m = 0, j = 0; para->arg[m]; m++)
		if (!is_delim(para->arg[m], " \t\n"))
			j++;
	if (!j)
		return;

	path = find_path(para, _getenv(para, "PATH="), para->argv[0]);
	if (path)
	{
		para->path = path;
		fork_cmd(para);
	}
	else
	{
		if ((interactive(para) || _getenv(para, "PATH=")
			|| para->argv[0][0] == '/') && is_cmd(para, para->argv[0]))
			fork_cmd(para);
		else if (*(para->arg) != '\n')
		{
			para->status = 127;
			print_error(para, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @para: the parameter & return info struct
 * Return: void
 */
void fork_cmd(info_t *para)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* PLACE ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(para->path, para->argv, get_environ(para)) == -1)
		{
			free_para(para, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* PLACE ERROR FUNCTION */
	}
	else
	{
		wait(&(para->status));
		if (WIFEXITED(para->status))
		{
			para->status = WEXITSTATUS(para->status);
			if (para->status == 126)
				print_error(para, "Permission denied\n");
		}
	}
}
