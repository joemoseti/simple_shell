#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "main.h"

/**
 * fprintf2 - produces output according to a format
 * @fd: file descriptor of the file to write to.
 * @format: a string containing normal
 * sequence(s) of characters to print as-is, and
 * special character sequence(s) to determine how to print the next arguments.
 *
 * Return: the number of characters printed,
 * excluding the string-terminating null character
 */
int fprintf2(int fd, const char *format, ...)
{
	int i, j, bytes_count = 0, bytes_written = 0, ret = 0, *pti;
	va_list ap;

	shstruct(NULL)->fd = fd;
	if (format == NULL || (format[0] == '%' && format[1] == 0))
		return (-1);
	va_start(ap, format);	/*initialize argument pointer*/
	for (i = 0; format[i]; i++)
	{
		if (format[i] == '%')	/*when a % character is encountered*/
		{
			if (format[++i] == '%')
			{
				bytes_written += write(fd, (format + i), 1);
			}
			else
			{
				pti = printfext2(ap, format[i]);
				bytes_count = pti[0];
				bytes_written += bytes_count;
				if ((bytes_count > 0 || pti[1] == 1) &&
						(format[i] != '!' || format[i] != 'K'))
					ret++;
			}
		}
		else
		{
			bytes_written += write(fd, (format + i), 1);
		}
		va_end(ap);
		va_start(ap, format);
		for (j = 0; j < ret; j++)
		{
			va_arg(ap, int);
		}
	}
	va_end(ap);
	return (bytes_written);
}
