#include <unistd.h>

int ft_strlen(char *str)
{
    int len;

    len = 0;
    while (str[len])
        len++;
    return (len);
}

void    ft_put_str(char *str, int fd)
{
    write(fd, str, ft_strlen(str));
}

void    ft_echo(char *str, int n)
{
    ft_put_str(str, 1);
    if (!n)
        ft_put_str("\n", 1);
}

int main()
{
    ft_echo("HOLAMUNDO", 0);
    ft_echo("HOLAMUNDO", 1);
    return (0);
}
