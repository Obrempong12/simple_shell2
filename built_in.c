#include "shell.h"

/**
 * _myexit - function that exits the shell
 * @para: Structure containing potential arguments
 * Return: exit with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *para)
{
	int check_exit;

	if (para->argv[1])
	{
		check_exit = _convstr_int(para->argv[1]);
		if (check_exit == -1)
		{
			para->status = 2;
			print_error(para, "Illegal number: ");
			_eputs(para->argv[1]);
			_eputchar('\n');
			return (1);
		}
		para->err_num = _convstr_int(para->argv[1]);
		return (-2);
	}
	para->err_num = -1;
	return (-2);
}

/**
 * _mycd - function that changes the current directory
 * @para: parameter structure with potential arguments
 *  Return: Always 0
 */
int _mycd(info_t *para)
{
	char *c, *dir, buffer[1024];
	int chdir_nest;

	c = getcwd(buffer, 1024);
	if (!c)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!para->argv[1])
	{
		dir = _getenv(para, "HOME=");
		if (!dir)
			chdir_nest = /* TODO: what should this be? */
			chdir((dir = _getenv(para, "PWD=")) ? dir : "/");
		else
			chdir_nest = chdir(dir);
	}
	else if (_strcmp(para->argv[1], "-") == 0)
	{
		if (!_getenv(para, "OLDPWD="))
		{
			_puts(c);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(para, "OLDPWD=")), _putchar('\n');
		chdir_nest = /* TODO: what should this be? */
		chdir((dir = _getenv(nest, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_nest = chdir(para->argv[1]);
	if (chdir_nest == -1)
	{
		print_error(para, "can't cd to ");
		_eputs(para->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(para, "OLDPWD", _getenv(para, "PWD="));
		_setenv(para, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - initializes help command
 * @para: parameter structure with potential arguments
 *  Return: Always 0
 */
int _myhelp(info_t *para)
{
	char **arg_array;

	arg_array = para->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
