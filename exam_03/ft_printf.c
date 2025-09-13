#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

// helper to count printed characters
int ft_putchar(char c)
{
    return write(1, &c, 1);
}

int ft_putstr(char *s)
{
    int i = 0;

    if (!s)
        s = "(null)";
    while (s[i])
        ft_putchar(s[i++]);
    return i;
}

int ft_putnbr(int n)
{
    int len = 0;
    if (n == -2147483648)
        return write(1, "-2147483648", 11);
    if (n < 0)
    {
        len += ft_putchar('-');
        n = -n;
    }
    if (n >= 10)
        len += ft_putnbr(n / 10);
    len += ft_putchar((n % 10) + '0');
    return len;
}

int ft_puthex(unsigned int n)
{
    int len = 0;
    char *hex = "0123456789abcdef";
    if (n >= 16)
        len += ft_puthex(n / 16);
    len += ft_putchar(hex[n % 16]);
    return len;
}

int ft_printf(const char *format, ...)
{
    va_list args;
    int i = 0, total = 0;

    va_start(args, format);
    while (format[i])
    {
        if (format[i] == '%' && format[i + 1])
        {
            i++;
            if (format[i] == 's')
                total += ft_putstr(va_arg(args, char *));
            else if (format[i] == 'd')
                total += ft_putnbr(va_arg(args, int));
            else if (format[i] == 'x')
                total += ft_puthex(va_arg(args, unsigned int));
            else
                total += ft_putchar(format[i]);
        }
        else
            total += ft_putchar(format[i]);
        i++;
    }
    va_end(args);
    return total;
}

