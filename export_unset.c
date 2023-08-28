#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int ft_strlen(char *str)
{
    int len = 0;

    while (str[len])
        len++;
    return (len);
}

char	*ft_strdup(char *src)
{
	char	*str;
	int		p;

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

int ft_count_rows(char ***str)
{
    int n_rows = 0;

    while (str[n_rows])
        n_rows++;
    return (n_rows);
}

char    ***ft_allocate_matrix(int number_rows, int number_columns)
{
    char    ***new_matrix;
    int     fila;
    int     columna;

    fila = 0;
    columna = 0;
    new_matrix = malloc ((number_rows + 1) * sizeof (*new_matrix));
    if (!new_matrix)
        return (NULL);
    while (fila < number_rows)
    {
        new_matrix[fila] = malloc ((number_columns + 1) * sizeof (**new_matrix));
        if (!new_matrix[fila])
            return (NULL);
        while (columna < number_columns)
        {
            new_matrix[fila][columna] = malloc (100 * sizeof (***new_matrix));
            if (!new_matrix[fila][columna])
                return (NULL);
            columna++;
        }
        columna = 0;
        fila++;
    }
    return (new_matrix);
}

int ft_strcmp(char *str1, char *str2)
{
    int i;

    i = 0;
    while (str1[i] == str2[i] && str1[i] && str2[i])
    {
        //printf("STRCMP -> %c\n", str1[i]);
        i++;
    }
    if (str1[i] == '\0' && str2[i] == '\0')
        return (1);
    else
        return (0);
}

int ft_check_exist_var(char ***env_vars, int n_rows, char *name_var)
{
    int find;
    int row;

    find = 0;
    row = 0;
    while (row < n_rows && find == 0)
    {
        if (ft_strcmp(env_vars[row][0], name_var))
            find = 1;
        row++;
    }
    if (find == 1)
        return (row - 1);
    else
        return (0);
}

char	*ft_expand_var(char ***env_vars, char *str)
{
	char	*str_return;
    int     n_rows;
    int     row;

    n_rows = ft_count_rows(env_vars);
    row = -1;
    row = ft_check_exist_var(env_vars, n_rows, str);
    if (row != -1)
        return (env_vars[row][1]);
    else
        return (NULL);
	return (str_return);
}

char    ***ft_unset(char ***env_vars, char *name_var)
{
    char    ***new_env_vars;
    int     n_rows;
    int     row_new;
    int     row_old;

    row_new = 0;
    row_old = 0;
    n_rows = ft_count_rows(env_vars);
    new_env_vars = ft_allocate_matrix(n_rows - 1, 2);
    while (row_new < n_rows - 1)
    {
        if (ft_strcmp(env_vars[row_old][0], name_var))
            row_old++;
        else
        {
            new_env_vars[row_new][0] = env_vars[row_old][0];
            new_env_vars[row_new][1] = env_vars[row_old][1];
            row_new++;
            row_old++;
        }
    }
    free (env_vars);
    return (new_env_vars);
}

char    ***ft_export(char ***env_vars, char *name_var, char *value_var)
{
    char    ***new_env_vars;
    int     n_rows;
    int     row;

    n_rows = 0;
    row = 0;

    n_rows = ft_count_rows(env_vars);

    if (ft_check_exist_var(env_vars, n_rows, name_var))
    {
        env_vars[ft_check_exist_var(env_vars, n_rows, name_var)][1] = value_var;
        return (env_vars);
    }
    new_env_vars = ft_allocate_matrix(n_rows + 1, 2);
    while (row <= n_rows - 1)
    {
        new_env_vars[row][0] = env_vars[row][0];
        new_env_vars[row][1] = env_vars[row][1];
        row++;
    }
    new_env_vars[row][0] = name_var;
    new_env_vars[row][1] = value_var;
    free(env_vars);
    return (new_env_vars);
}

void    ft_print_matrix(char ***str, int n_rows, int n_columns)
{
    int row;
    int column;

    row = 0;
    column = 0;
    while (row < n_rows)
    {
        while (column < n_columns)
        {
            printf("%s ", str[row][column]);
            column++;
        }
        printf("\n");
        column = 0;
        row++;
    }
}

int main()
{
    char ***str;
    int n_rows = 0;

    str = ft_allocate_matrix(1, 2);
    n_rows = ft_count_rows(str);
    printf("NUMERO DE FILAS -> %i\n", n_rows);
    ft_print_matrix(str, n_rows, 2);

    str = ft_export(str, "HOLA", "MUNDO");
    str = ft_export(str, "ADIOS", "HELADO");
    n_rows = ft_count_rows(str);
    printf("NUMERO DE FILAS -> %i\n", n_rows);
    ft_print_matrix(str, n_rows, 2);

    str = ft_export(str, "BOLA", "PISTACHO");
    str = ft_export(str, "HOLA", "CARAMELO");
    n_rows = ft_count_rows(str);
    printf("NUMERO DE FILAS -> %i\n", n_rows);
    ft_print_matrix(str, n_rows, 2);

    str = ft_unset(str, "HOLA");
    n_rows = ft_count_rows(str);
    printf("NUMERO DE FILAS -> %i\n", n_rows);

    ft_print_matrix(str, n_rows, 2);

    str = ft_export(str, "HOLA", "HELADO");
    n_rows = ft_count_rows(str);
    printf("NUMERO DE FILAS -> %i\n", n_rows);
    ft_print_matrix(str, n_rows, 2);

    printf("\n");

    printf("VALOR DE HOLA -> %s\n", ft_expand_var(str, "HOLA"));
    printf("VALOR DE ADIOS -> %s\n", ft_expand_var(str, "ADIOS"));
    printf("VALOR DE BOLA -> %s\n", ft_expand_var(str, "BOLA"));

    return (0);
}
