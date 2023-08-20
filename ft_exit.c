#include <unistd.h>
#include <stdlib.h>

//-----------------------------------------------STRDUP-----------------------------------

int     ft_strlen(char *str)
{
        int len;

        len = 0;
        while (str[len])
                len++;
        return (len);
}

char    *ft_strdup(char *src)
{
        char    *str;
        int     p;

        str = malloc ((ft_strlen(src) + 1) * sizeof (*str));
        if (!str)
                return (NULL);
        p = 0;
        while (src[p])
        {
                str[p] = src[p];
                p++;
        }
        str[p] = '\0';
        return (str);
}

//----------------------------------------------ITOA----------------------------------------
typedef struct s_itoa_data
{
        int     sign;
        int     len;
        char    *result;
}       t_itoa_data;

static int      ft_len(int n)
{
        int     len;

        len = 0;
        while (n > 0)
        {
                len++;
                n /= 10;
        }
        return (len);
}

char *ft_itoa(int n)
{
        t_itoa_data     d;

        d.sign = 0;
        d.len = 0;
        if (n == 0)
                return (ft_strdup("0"));
        if (n < 0)
        {
                if (n == -2147483648)
                        return (ft_strdup("-2147483648"));
                d.sign++;
                n = -n;
        }
        d.len = ft_len(n) + d.sign;
        d.result = malloc ((d.len + 1) * sizeof (*d.result));
        if (!d.result)
                return (NULL);
        if (d.sign)
                d.result[0] = '-';
        d.result[d.len] = '\0';
        d.len--;
        while (n > 0)
        {
                d.result[d.len--] = (n % 10) + 48;
                n /= 10;
        }
        return (d.result);
}
//------------------------------------------FIN ITOA-----------------------------------------

void    ft_exit(int code)
{
        write(1, "exit ", 5);
        write(1, ft_itoa(code), ft_strlen(ft_itoa(code)));
        write(1, "\n", 1);
        exit(code);
}
