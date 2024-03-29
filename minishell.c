/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pespinos <pespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 21:50:19 by pespinos          #+#    #+#             */
/*   Updated: 2023/08/09 17:35:19 by pespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_all	g_data;

void	ft_putstr(char *str, int fd)
{
	int	n;

	n = 0;
	while (str[n])
	{
		write(fd, &str[n], 1);
		n++;
	}
}

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

char	*ft_strjoin(char *str1, char *str2)
{
	char	*str_result;
	int	c1;
	int	c2;

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
	return (str_result);
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

int	*ft_create_map(int n_elements) //SE HA MODIFICADO ESTA FUNCION
{
	int	*map;
	int	n;

	n = 0;
	g_data.map_elements = n_elements;
	map = malloc (n_elements * sizeof (*g_data.map));
	if (!map)
		return (NULL);
	while (n < g_data.map_elements)
		map[n++] = 1;
	return (map);
}

void	ft_print_map(int *map) //SE HA MODIFICADO ESTA FUNCION
{
	int	n;

	n = 0;
	while (n < g_data.map_elements)
		printf("%i ", map[n++]);
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

//GESTION DE COMILLAS------------------------------------------------------------------------

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

char    *ft_convert_colons() //SE HA MODIFICADO ESTA FUNCION
{
	char	*str_return;
    int		ignore_limit;
    int		n;
	int		i;
	int		*new_map;

	new_map = ft_create_map(ft_strlen(g_data.str_order));

	str_return = malloc (100 * sizeof (*str_return));
	if (!str_return)
		return (NULL);
    n = 0;
	i = 0;
    ignore_limit = -1;
    while (g_data.str_order[n])
    {
        if (ignore_limit != -1)
        {
            if (n == ignore_limit)
                ignore_limit = -1;
            else
			{
				str_return[i] = g_data.str_order[n];
				new_map[i++] = g_data.map[n];
			}
        }
        else if (g_data.str_order[n] == '"' || g_data.str_order[n] == '\'')
            ignore_limit = ft_find_ignore_limit(g_data.str_order, n);
        else
		{
			str_return[i] = g_data.str_order[n];
			new_map[i++] = g_data.map[n];
		}
        n++;
    }
	str_return[i] = '\0';
	printf("FT_CONVERT_COLONS --- LONGITUD DE LA CADENA DEVUELTA = %i\n", ft_strlen(str_return));
    printf("FT_CONVERT_COLONS --- CADENA DEVUELTA -> %s\n", str_return);
	g_data.map = new_map;
	g_data.map_elements = i;
    return (str_return);
}

//FIN GESTION DE COMILLAS----------------------------------------------------------------------

char	*ft_expand_var(char *str)
{
	char	*str_return;

	str_return = getenv(str);
	return (str_return);
}

char	*ft_get_word(char *str, int position)
{
	int	start;
	int	len;

	start = position;
	len = 0;
	while (str[position] != ' ' && str[position] != '$' && str[position]
        && str[position] != 34 && str[position] != 39)
	{
		len++;
		position++;
	}
	return (ft_substr(str, start, len));
}

char	*ft_check_env_vars(void) //SE HA MODIFICADO ESTA FUNCION
{
	char	*str;
    char    *expand_var;
	int	n;

	n = 0;
	str = malloc (0 * sizeof (*str));
	if (!str)
		return (NULL);
	while (g_data.str_order[n])
	{
		if (g_data.str_order[n] == '$' && g_data.map[n] && 
            g_data.str_order[n + 1] != 0 && g_data.str_order[n + 1] != 34 &&
            g_data.str_order[n + 1] != 39)
		{
			//str = ft_strjoin(str, ft_expand_var(ft_get_word(g_data.str_order, n + 1)));
            expand_var = ft_expand_var(ft_get_word(g_data.str_order, n + 1));
            str = ft_strjoin(str, ft_expand_var(ft_get_word(g_data.str_order, n + 1)));
			n = n + (ft_strlen(ft_get_word(g_data.str_order, n + 1)) + 1);
		}
		else
		{
			str = ft_straddchar(str, g_data.str_order[n]);
			n++;
		}
	}
	printf("FT_CHECK_ENV_VARS --- RESULTADO = %s\n", str);
	return (str);
}

void	ft_control_c(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		//rl_replace_line("", 0);
		//rl_on_new_line();
	}
}

int	ft_control_d()
{
	if (!g_data.str_order)
		exit(0);
	return (0);
}

void	ft_init_signals()
{
	signal(SIGINT, ft_control_c);
	signal(SIGQUIT, SIG_IGN);
}

int	main(void)
{
	char *str;

	ft_init_signals();
	g_data.str_order = ft_print_entry("minishell >> ");
	while (g_data.str_order != NULL)
	{
		if (ft_control_d())
			return (-1);
		if (ft_search_char(';') || ft_search_char('\\'))
			return (-1);
		g_data.map = ft_create_map(ft_strlen(g_data.str_order));
		//ft_print_map();
		if (ft_check_str())
            return(printf("ERROR -> COMILLAS ABIERTAS\n"), -1);
        else
        {
            ft_print_map(g_data.map);
			g_data.str_order = ft_convert_colons();
            ft_check_env_vars();
            ft_print_map(g_data.map);
            ft_add_history(g_data.str_order);
        }
		free (g_data.str_order);
		g_data.str_order = ft_print_entry("minishell >> ");
	}
	free (g_data.map);
	return (0);
}
