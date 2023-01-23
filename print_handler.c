#include "main.h"
/**
 * print_handler - Prints an argument based on its type
 * @format: Formatted string in which to print the arguments.
 * @args_list: List of arguments to be printed.
 * @index: index.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int print_handler(const char *format, int *index, va_list args_list,
	char buffer[], int flags, int width, int precision, int size)
{
	int i, length = 0, printed_chars = -1;

	format_t format_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (i = 0; format_types[i].fmt_char != '\0'; i++)
		if (format[*index] == format_types[i].fmt_char)
			return (format_types[i].funptr(args_list, buffer,
						flags, width, precision, size));
	if (format_types[i].fmt_char == '\0')
	{
		if (format[*index] == '\0')
			return (-1);
		length += write(1, "%%", 1);
		if (format[*index - 1] == ' ')
			length += write(1, " ", 1);
		else if (width)
		{
			--(*index);
			while (format[*index] != ' ' && format[*index] != '%')
				--(*index);
			if (format[*index] == ' ')
				--(*index);
			return (1);
		}
		length += write(1, &format[*index], 1);
		return (length);
	}
	return (printed_chars);
}
