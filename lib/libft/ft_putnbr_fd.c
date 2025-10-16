#include "libft.h"

static void write_number(long n, int fd)
{
    char    c;

    if (n >= 10)
        write_number(n / 10, fd);
    c = (char)('0' + (n % 10));
    write(fd, &c, 1);
}

void    ft_putnbr_fd(int n, int fd)
{
    long    nb;

    nb = (long)n;
    if (nb < 0)
    {
        write(fd, "-", 1);
        nb = -nb;
    }
    write_number(nb, fd);
}
