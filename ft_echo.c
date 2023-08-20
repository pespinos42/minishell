#include <unistd.h>

int ft_strlen(char *str)
{
    int len;

    len = 0;
    while (str[len])
        len++;
    return (len);
}

void    ft_put_char(char letter, int fd)
{
    write(fd, &letter, 1);
}

void    ft_put_str(char *str, int fd)
{
    write(fd, str, ft_strlen(str));
}

void    ft_put_str_wnl(char *str, int fd)
{
    int n;

    n = 0;
    while (str[n])
    {
        if (str[n] != '\n')
            ft_put_char(str[n], fd);
        n++;
    }
}

void    ft_echo(char *str, int n)
{
    if (!n)
        ft_put_str(str, 1);
    else
        ft_put_str_wnl(str, 1);
}
