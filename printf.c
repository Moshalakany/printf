#include "main.h"

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

#define BUFF_SIZE 1024

typedef struct {
    int flags;
    int width;
    int precision;
    int size;
} FormatSpec;

int _printf(const char *format, ...);
void print_buffer(char *buffer, int *buff_ind);
int handle_print(char *buffer, int *buff_ind, va_list list, FormatSpec spec, char type);
FormatSpec get_format_spec(const char *format, int *i, va_list list);

int _printf(const char *format, ...) {
    int printed_chars = 0;
    int buff_ind = 0;
    char buffer[BUFF_SIZE];
    va_list list;

    if (format == NULL)
        return -1;

    va_start(list, format);

    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] != '%') {
            buffer[buff_ind++] = format[i];
            if (buff_ind == BUFF_SIZE)
                print_buffer(buffer, &buff_ind);
            printed_chars++;
        } else {
            FormatSpec spec = get_format_spec(format, &i, list);
            int printed = handle_print(buffer, &buff_ind, list, spec, format[i]);
            if (printed == -1)
                return -1;
            printed_chars += printed;
        }
    }

    print_buffer(buffer, &buff_ind);
    va_end(list);

    return printed_chars;
}

void print_buffer(char *buffer, int *buff_ind) {
    if (*buff_ind > 0)
        write(1, buffer, *buff_ind);

    *buff_ind = 0;
}

int handle_print(char *buffer, int *buff_ind, va_list list, FormatSpec spec, char type) {
    // Implement the logic for handling each format specifier here
    // Use spec.flags, spec.width, spec.precision, spec.size, and type

    // Example:
    // if (type == 'd' || type == 'i') {
    //     // Handle integer printing here
    //     // Use spec.flags, spec.width, spec.precision, spec.size
    //     // Append the result to buffer
    // }

    return 0; // Return the number of characters printed
}

FormatSpec get_format_spec(const char *format, int *i, va_list list) {
    // Implement logic to parse format specifiers here
    // Update *i to skip the specifier and update the FormatSpec struct accordingly
    FormatSpec spec;
    spec.flags = 0;
    spec.width = 0;
    spec.precision = -1;
    spec.size = 0;

    // Example:
    // if (format[*i] == '0') {
    //     spec.flags |= FLAG_ZERO;
    //     (*i)++;
    // }

    return spec;
}
