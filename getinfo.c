#include "shell.h"

/**
 * initialize_struct - initializes info_t struct
 * @para: struct address
 */
void initialize_struct(info_t *para)
{
	para->arg = NULL;
	para->argv = NULL;
	para->path = NULL;
	para->argc = 0;
}

/**
 * set_struct_info - function that initializes info_t struct
 * @para: struct address
 * @argv: argument vector
 */
void set_struct_info(info_t *para, char **argv)
{
	int m = 0;

	para->fname = argv[0];
	if (para->arg)
	{
		para->argv = strtow(para->arg, " \t");
		if (!para->argv)
		{

			para->argv = malloc(sizeof(char *) * 2);
			if (para->argv)
			{
				para->argv[0] = _strdup(para->arg);
				para->argv[1] = NULL;
			}
		}
		for (m = 0; para->argv && para->argv[m]; m++)
			;
		para->argc = m;

		replace_alias(para);
		replace_vars(para);
	}
}

/**
 * free_info_struct - frees info_t struct fields
 * @para: struct address
 * @all: true for freeing all fields
 */
void free_info_struct(info_t *para, int all)
{
	ffree(para->argv);
	para->argv = NULL;
	para->path = NULL;
	if (all)
	{
		if (!para->cmd_buf)
			free(para->arg);
		if (para->env)
			free_list(&(para->env));
		if (para->history)
			free_list(&(para->history));
		if (para->alias)
			free_list(&(para->alias));
		ffree(para->environ);
			para->environ = NULL;
		bfree((void **)para->cmd_buf);
		if (para->readfd > 2)
			close(para->readfd);
		_putchar(BUF_FLUSH);
	}
}
