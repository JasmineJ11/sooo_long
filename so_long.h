/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiawli <jiawli@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:17:29 by jiawli            #+#    #+#             */
/*   Updated: 2025/07/31 14:24:05 by jiawli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct s_parameter_checker
{
	int	length;
	int	height;
	int entrance;
	int exit;
	int collectible;
}	t_parameter_check;

//so_long.c
char	**parse_para(char *file_name);
void	close_fd_and_exit(int fd, char *msg);

//free.c
void	exit_prog(char ***parameter, char *msg);
void	free_parameter(char ***parameter);

//validation.c
void	validate_parameter(char **parameter);

//utils.c
int	arr_len(char **arr);

#endif