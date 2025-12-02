/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:55:49 by alusnia           #+#    #+#             */
/*   Updated: 2025/12/02 07:45:29 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**free_arr(char **ptr)
{
	size_t	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
	return (NULL);
}

void	kill_program(t_data *data, int status, char *extra)
{
	size_t	i;

	i = 0;
	if (data->error != 0)
		status = 1;
	if (data && data->argv)
	{
		while (data->argv[i])
			free_arr(data->argv[i++]);
		free(data->argv);
	}
	if (data && data->catalogs)
		free_arr(data->catalogs);
	if (data && data->fd)
		free(data->fd);
	if (extra)
		free(extra);
	if (data)
		free(data);
	if (status)
		perror("pipex");
	exit(status);
}

static void	val_argv(char **argv)
{
	size_t	x;

	while (*argv)
	{
		x = ft_strlen(*argv);
		if (x == 0)
		{
			write(2, "pipex: wrong arguments\n", 23);
			exit(0);
		}
		argv++;
	}
}

static t_data	*malloc_data(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		i;

	i = 0;
	data = malloc(sizeof(t_data));
	if (!data)
		kill_program(data, 1, NULL);
	data->argv = malloc((argc + 1) * sizeof(char *));
	data->fd = malloc(6 * sizeof(int));
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (envp[i])
		data->catalogs = ft_split(envp[i] + 5, ':');
	else
		data->catalogs = NULL;
	if (!data->fd || !data->catalogs || !data->argv)
		kill_program(data, 1, NULL);
	i = 0;
	while (i++ < argc)
	{
		data->argv[i - 1] = ft_split(argv[i - 1], ' ');
		if (!data->argv[i - 1])
			kill_program(data, 1, NULL);
	}
	return (data);
}

t_data	*init_data(int argc, char **argv, char **envp)
{
	t_data	*data;

	val_argv(argv);
	data = malloc_data(argc, argv, envp);
	data->counter = 1;
	data->error = 0;
	data->safe_word = NULL;
	data->envp = envp;
	data->argv[argc] = NULL;
	data->path = NULL;
	data->status = 0;
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		data->counter++;
		data->safe_word = argv[2];
		if (!ft_strlen(data->safe_word))
			kill_program(data, 1, NULL);
	}
	return (data);
}
