/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_so_long.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiawli <jiawli@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 11:50:12 by jiawli            #+#    #+#             */
/*   Updated: 2025/08/09 18:52:59 by jiawli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	close_fd_and_exit(int fd, char *msg)
{
	close(fd);
	exit_prog(NULL, NULL, msg);
}



static void	check_empty_lines(char *buf, ssize_t bytes_read)
{
	int	i;

	if (buf[0] == '\n')
		exit_prog(NULL, NULL, "Map starts with empty line.");
	i = 0;
	while (i < bytes_read - 1)
	{
		if (buf[i] == '\n' && buf[i + 1] == '\n')
			exit_prog(NULL, NULL, "Map has empty line.");
		i++;
	}
}

static void	check_filename(char *file_name)
{
	size_t	len;

	len = ft_strlen(file_name);
	if (len < 5 || ft_strncmp(file_name + len - 4, ".ber", 4) != 0)
		exit_prog(NULL, NULL, "Should be .ber file");
}

static char	**parse_para(char *file_name)
{
	int		fd;
	ssize_t	bytes_read;
	char	buf[40000];
	char	**parameter;

	check_filename(file_name);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		exit_prog(NULL, NULL, "Error on opening a map.");
	bytes_read = read(fd, buf, 40000);
	if (bytes_read == -1)
		close_fd_and_exit(fd, "Error on reading map.");
	if (bytes_read == 0)
		close_fd_and_exit(fd, "Cannot open an empty map.");
	if (bytes_read == 40000)
		close_fd_and_exit(fd, "Map file too large (>40KB).");
	close(fd);
	buf[bytes_read] = '\0';
	check_empty_lines(buf, bytes_read);
	parameter = ft_split(buf, '\n');
	if (!parameter)
		exit_prog(NULL, NULL, "Memory allocation failed: parsing the map.");
	return (parameter);
}
int	main(int ac, char **av)
{
	char **parameter = NULL;
    t_game *game = NULL;
    t_parameter_check checker;
	
	if (ac != 2)
		exit_prog(NULL, NULL, "Give me a map");
	
	parameter = parse_para(av[1]);
	checker = validate_parameter(parameter);
	game = create_game(&checker, parameter); 
	if(!path_check(game))
		exit_prog(&parameter, &game, "No valid path in the map.");
	free_parameter(&parameter);
	start_engine(game);
    
    exit_prog(&parameter, &game, NULL);
    return (0);
}
