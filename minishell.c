/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pespinos <pespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 21:50:19 by pespinos          #+#    #+#             */
/*   Updated: 2023/07/25 16:25:09 by pespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_all	g_data;

int	ft_strlen(char const *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strdup(char *src)
{
	char	*str;
	int	p;

	p = 0;
	str = malloc ((ft_strlen(src) + 1) * sizeof (*str));
	if (!str)
		return (NULL);
	while (src[p])
	{
		str[p] = src[p];
		p++;
	}
	str[p] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	p;
	char	*str;

	p = 0;
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (ft_strlen(&s[start]) < len)
		len = ft_strlen(&s[start]);
	str = malloc ((len + 1) * sizeof (*str));
	if (!str)
		return (NULL);
	while (s[start + p] && p < len)
	{
		str[p] = s[start + p];
		p++;
	}
	str[p] = '\0';
	return (str);
}

int	ft_num_words(char const *s, char c)
{
	int	q;
	int	p;
	int	first;

	q = 0;
	p = 0;
	first = 1;
	while (s[p])
	{
		if (s[p] != c && s[p] != '\0' && first == 1)
		{
			q++;
			first = 0;
		}
		if (s[p] == c)
			first = 1;
		p++;
	}
	return (q);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		q;
	int		p;
	int		start;

	q = 0;
	p = 0;
	start = 0;
	result = malloc ((ft_num_words(s, c) + 1) * sizeof (char *));
	if (!result)
		return (NULL);
	while (s[p] && q < ft_num_words(s, c))
	{
		while (s[p] && s[p] == c)
			p++;
		start = p;
		while (s[p] && s[p] != c)
			p++;
		if (start != p)
			result[q++] = ft_substr(s, start, p - start);
	}
	result[q] = NULL;
	return (result);
}

void	ft_print_words(char **str)
{
	int	n;

	n = 0;
	while (str[n] != NULL)
	{
		printf("[%i] -> %s\n", n, str[n]);
		n++;
	}
}

void	ft_add_history(char *str)
{
	if (ft_strlen(str) > 0)
		add_history(str);
}

char	*ft_print_entry(char *msg)
{
	char	*str;

	str = readline(msg);
	return (str);
}

void	ft_create_map(void)
{
	int	n;

	n = 0;
	g_data.map_elements = ft_strlen(g_data.str_order);
	g_data.map = malloc (g_data.map_elements * sizeof (*g_data.map));
	if (!g_data.map)
		return ;
	while (n < g_data.map_elements)
		g_data.map[n++] = 1;
}

void	ft_print_map(void)
{
	int	n;

	n = 0;
	while (n < g_data.map_elements)
		printf("%i ", g_data.map[n++]);
	printf("\n");
}

void	ft_fill_map(int start_position, int end_position, int value)
{
	int	n;

	n = start_position;
	while (n <= end_position)
	{
		g_data.map[n] = value;
		n++;
	}
}

char	*ft_strjoin(char *str1, char *str2)
{
	char	*str_result;
	int	c1;
	int	c2;

    printf("DENTRO DE STRJOIN\nSTR1 -> %s\nSTR2 -> %s\n", str1, str2);

	c1 = 0;
	c2 = 0;
	str_result = malloc ((ft_strlen(str1) + ft_strlen(str2) + 1) * sizeof (*str_result));
	if (!str_result)
		return (NULL);
	while (str1[c1])
	{
		str_result[c1] = str1[c1];
		c1++;
	}
	while (str2[c2])
	{
		str_result[c1+c2] = str2[c2];
		c2++;
	}
	str_result[c1+c2] = '\0';
    printf("FINAL DE STRJOIN\n");
	return (str_result);
}

char	*ft_straddchar(char *str, char letter)
{
	char	*s;
	int	c1;

	c1 = 0;
	s = malloc ((ft_strlen(str) + 2) * sizeof (*s));
	if (!s)
		return (NULL);
	while (str[c1])
	{
		s[c1] = str[c1];
		c1++;
	}
	s[c1] = letter;
	s[c1 + 1] = '\0';
	return (s);
}

//1 - OPEN 0 - CLOSE
int	ft_check_open(char letter, int position)
{
	int	n;
	int	find;

	n = position + 1;
	find = 0;
	while (g_data.str_order[n] && find == 0)
	{
		if (g_data.str_order[n] == letter)
		{
			g_data.close_position = n;
			find = 1;
		}
		n++;
	}
	if (find == 1)
	{
		if (letter == 34)
			ft_fill_map(position, g_data.close_position, 1);
		else if (letter == 39)
			ft_fill_map(position, g_data.close_position, 0);
		return (0);
	}
	else
		return (1);
}
//1 - OPEN 0 - CLOSE
int	ft_check_str(void)
{
	int	n;

	n = 0;
	while (g_data.str_order[n])
	{
		if (g_data.str_order[n] == 34)
		{
			if (ft_check_open(34, n) == 1)
				return (1);
			else
				n = g_data.close_position + 1;
		}
		else if (g_data.str_order[n] == 39)
		{
			if (ft_check_open(39, n) == 1)
				return (1);
			else
				n = g_data.close_position + 1;
		}
		else
			n++;
	}
    return (0);
}

//1 - FOUND 0 - NOT FOUND
int	ft_search_char(char letter)
{
	int	n;

	n = 0;
	while (g_data.str_order[n])
	{
		if (g_data.str_order[n] == letter)
			return (1);
		n++;
	}
	return (0);
}

char	*ft_expand_var(char *str)
{
	char	*str_return;

    printf("DENTRO DE FT_EXPAND_VAR\t\t\t str -> %s\n", str);

	str_return = getenv(str);
	return (str_return);
}

char	*ft_get_word(char *str, int position)
{
	int	start;
	int	len;

	//printf("DENTRO DE FT_GET_WORD\n");

	start = position;
	len = 0;
	while (str[position] != ' ' && str[position] != '$' && str[position]
        && str[position] != 34 && str[position] != 39)
	{
		len++;
		position++;
	}
	//printf("CADENA A CORTAR -> %s\nPOSICION INICIAL -> %i\nLONGITUD A CORTAR -> %i\n", str, start, len);
	return (ft_substr(str, start, len));
}

void	ft_check_env_vars(void)
{
	char	*str;
    char    *expand_var;
	int	n;

	n = 0;

	str = malloc (0 * sizeof (*str));
	if (!str)
		return ;

	printf("VALOR STR -> %s\n", str);

	while (g_data.str_order[n])
	{
		if (g_data.str_order[n] == '$' && g_data.map[n] && 
            g_data.str_order[n + 1] != 0 && g_data.str_order[n + 1] != 34 &&
            g_data.str_order[n + 1] != 39)
		{
            printf("DENTRO DE $\n");
			//str = ft_strjoin(str, ft_expand_var(ft_get_word(g_data.str_order, n + 1)));
            expand_var = ft_expand_var(ft_get_word(g_data.str_order, n + 1));
            printf("EXPAND_VAR -> %s\n", expand_var);
            str = ft_strjoin(str, ft_expand_var(ft_get_word(g_data.str_order, n + 1)));
			printf("PRUEBA DE CONVERSION ----------------- %s\n", ft_expand_var(ft_get_word(g_data.str_order, n + 1)));
			n = n + (ft_strlen(ft_get_word(g_data.str_order, n + 1)) + 1);
            printf("NUEVO VALOR DE N -> %i\n", n);
		}
		else
		{
			str = ft_straddchar(str, g_data.str_order[n]);
			n++;
		}
        printf("VALOR STR -> %s\t\t\t n = %i\n", str, n);
	}
	printf("CADENA CONVERTIDA -> %s\n", str);
}

int	main(void)
{
	g_data.str_order = ft_print_entry("minishell >> ");
	while (g_data.str_order != NULL)
	{
		if (ft_search_char(';') || ft_search_char('\\'))
		{
			printf("CARACTERES ERRONEOS\n");
			return (-1);
		}
		ft_create_map();
		ft_print_map();
		if (ft_check_str())
            printf("ERROR -> COMILLAS ABIERTAS\n");
        else
        {
            ft_print_map();
            ft_check_env_vars();
            //printf("LONGITUD TOTAL DE CARACTERES SIN CONTAR ESPACIOS -> %i\n", ft_total_length());
            ft_add_history(g_data.str_order);            
        }            
		free (g_data.str_order);
		g_data.str_order = ft_print_entry("minishell >> ");
	}
	printf("$USER = %s\n", ft_expand_var("USER"));
	free (g_data.map);
	return (0);
}