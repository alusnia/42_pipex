/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 07:59:48 by alusnia           #+#    #+#             */
/*   Updated: 2025/12/02 06:53:02 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"

typedef struct s_data
{
	char	***argv;
	char	**catalogs;
	char	**envp;
	char	*temp;
	char	*path;
	char	*safe_word;
	int		status;
	int		error;
	int		*fd;
	int		counter;
	pid_t	pid;
	mode_t	mode;

}	t_data;

//pipex_utils-------------------------------------------------------------------
t_data	*handle_error(t_data *data);
void	open_function(t_data *data, char **argv);
//init_data---------------------------------------------------------------------
char	**free_arr(char **ptr);
void	kill_program(t_data *data, int status, char *extra);
t_data	*init_data(int argc, char **argv, char **envp);

#endif