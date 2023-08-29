#include <stdio.h>
#include <unistd.h>

void    ft_putchar(char letter, int fd)
{
    write(fd, &letter, 1);
}

int ft_find_ignore_limit(char *str, int start_position)
{
    char    letter_to_find;
    int     n;
    int     limit;

    letter_to_find = str[start_position];
    n = start_position + 1;
    limit = -2;
    while (str[n] && limit == -2)
    {
        if (str[n] == letter_to_find)
            limit = n;
        n++;
    }
    return (limit);
}

char    *ft_convert_colons(char *str)
{
    int n;
    int ignore_limit;

    n = 0;
    ignore_limit = -1;
    while (str[n])
    {
        if (ignore_limit != -1)
        {
            if (n == ignore_limit)
                ignore_limit = -1;
            else
                ft_putchar(str[n], 1);
        }
        else if (str[n] == '"' || str[n] == '\'')
            ignore_limit = ft_find_ignore_limit(str, n);
        else
            ft_putchar(str[n], 1);
        n++;
    }
    return (NULL);
}

int main()
{
    char *str = "\"\'\"\'\"\'hola\'\"\'\"\'\"";
    ft_convert_colons(str);

    printf("\n");

    return (0);
}
