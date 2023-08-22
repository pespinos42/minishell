/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pespinos <pespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 21:59:43 by pespinos          #+#    #+#             */
/*   Updated: 2023/08/22 19:01:04 by pespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>
# include <sys/ioctl.h>

typedef struct s_all
{
	int		*map;
	int		map_elements;
	int		close_position;
	char	*str_order;
	int		sigint_done;
	int		first_colon;
	int		count_simple_colon;
	int		count_double_colon;
}	t_all;

t_all g_data;

#endif
