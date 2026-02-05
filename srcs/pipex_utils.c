/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 08:33:58 by alusnia           #+#    #+#             */
/*   Updated: 2025/12/02 07:39:50 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_data	*handle_error(t_data *data)
{
	int	fd[2];

	if (!data->fd[0])
	{
		if (pipe(fd) == -1)
			kill_program(data, 1, NULL);
		close(fd[1]);
		data->fd[0] = fd[0];
	}
	if (!data->fd[3])
	{
		if (pipe(fd) == -1)
			kill_program(data, 1, NULL);
		close(fd[0]);
		data->fd[3] = fd[1];
	}
	return (data);
}

static t_data	*check_for_path(t_data *data, char *path, char *f_name)
{
	if (!f_name)
		kill_program(data, 1, NULL);
	data->path = ft_strjoin(path, f_name);
	if (!data->path)
		kill_program(data, 1, f_name);
	if (access(data->path, F_OK) == 0)
	{
		if (access(data->path, X_OK) == 1)
		{
			free(data->path);
			data->path = NULL;
		}
	}
	else
	{
		free(data->path);
		data->path = NULL;
	}
	free(f_name);
	return (data);
}

void	open_function(t_data *data, char **argv)
{
	size_t	i;

	i = 0;
	if (argv[0][0] == '.' || argv[0][0] == '/')
	{
		if (access(argv[0], F_OK) == 1)
			kill_program(data, 127, NULL);
		if (access(argv[0], X_OK) == 1)
			kill_program(data, 126, NULL);
		data->path = argv[0];
	}
	while (data->catalogs && data->catalogs[i] && !data->path)
	{
		data->temp = data->catalogs[i++];
		if (!data->temp)
			kill_program(data, 3, NULL);
		data = check_for_path(data, data->temp, ft_strjoin("/", argv[0]));
	}
	if (!data->path)
		kill_program(data, 127, NULL);
	execve(data->path, data->argv[data->counter + 1], data->envp);
	perror("execve() failed\n");
	kill_program(data, 1, NULL);
}
