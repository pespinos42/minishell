/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pespinos <pespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:08:35 by pespinos          #+#    #+#             */
/*   Updated: 2023/08/12 16:09:51 by pespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strlen(char *str)
{
    int len;

    len = 0;
    while (str[len])
        len++;
    return (len);
}

int ft_number_pipes(char *str)
{
    int n_pipes;
    int n;

    n_pipes = 0;
    n = 0;
    while (str[n])
    {
        if (str[n] == '|')
            n_pipes++;
        n++;
    }
    return (n_pipes);
}
// HAY QUE REPASAR DESDE AQUI -----------------------------
void    ft_str_copy(char *str_origin, char *str_destiny)
{
    int n;

    n = 0;
    while (str_origin[n])
    {
        str_destiny[n] = str_origin[n];
        n++;
    }
}

int ft_check_chars(char letter, char *str)
{
    int found;
    int n;

    found = 0;
    n = 0;
    while (str[n] && found == 0)
    {
        if (str[n] == letter)
            found = 1;
        n++;
    }
    return (found);
}

int ft_number_characters(char *str)
{
    int n;
    int n_chars;

    n = 0;
    n_chars = 0;
    while (str[n])
    {
        if (ft_check_chars(str[n + 1], "<>|") && str[n] != ' ' && !(ft_check_chars(str[n], "<>")))
            n_chars++;
        else if (ft_check_chars(str[n], "<>|") && str[n + 1] != ' ' && !(ft_check_chars(str[n], "<>")))
            n_chars++;
        n_chars++;
        n++;
    }
    return (n_chars);
}

char    *ft_separator(char *str)
{
     	char    *result;
	int	n;
	int	p;

	n = 0;
	p = 0;
	result = malloc ((ft_number_characters(str) + 1) * sizeof (*result));
	if (!result)
		return (NULL);
	while (str[n])
	{
		if (ft_check_chars(str[n + 1], "<>|") && str[n] != ' ' && !(ft_check_chars(str[n], "<>")))
		{
            printf("DEBUG -- DENTRO DE LA PRIMERA CONDICION\n");
			result[p] = str[n];
			p++;
			result[p] = ' ';
			p++;
		}
		else if (ft_check_chars(str[n], "<>|") && str[n + 1] != ' ' && !(ft_check_chars(str[n + 1], "<>")))
		{
            printf("DEBUG -- DENTRO DE LA SEGUNDA CONDICION\n");
			result[p] = str[n];
			p++;
			result[p] = ' ';
			p++;
		}
		else
		{
            printf("DEBUG -- DENTRO DEL ELSE\n");
			result[p] = str[n];
			p++;
		}
		n++;
        printf("DEBUG -- result = %s\n", result);
	}
	result[p] = '\0';
	return (result);
}

//------------------------------------ HASTA AQUI

int main()
{
    char str[] = "hola>>que<<tal||todo";
    printf("NUMERO DE CARACTERES FUTUROS -> %i\n", ft_number_characters(str));
    printf("CADENA FINAL -> %s\n", ft_separator(str));
    return (0);
}
