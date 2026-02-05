/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 07:40:10 by alusnia           #+#    #+#             */
/*   Updated: 2025/12/02 07:42:14 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_data	*give_birth(t_data *data, int argc)
{
	while (data->counter < argc - 2)
	{
		if (pipe(data->fd + 1) == -1)
			kill_program(data, 1, NULL);
		data->pid = fork();
		if (data->pid < 0)
			kill_program(data, 1, NULL);
		else if (data->pid == 0)
		{
			dup2(data->fd[0], 0);
			if (data->safe_word != NULL && data->counter == 2)
				close(data->fd[0]);
			if (data->counter < argc - 3)
				dup2(data->fd[2], 1);
			else
				dup2(data->fd[3], 1);
			break ;
		}
		if (data->safe_word == NULL || data->counter >= 2)
			close(data->fd[0]);
		close(data->fd[2]);
		data->fd[0] = data->fd[1];
		data->counter++;
	}
	return (data);
}

static int	verify_files(t_data **data, char *f, int wr)
{
	if (!wr && access(f, F_OK) == -1)
		return (0);
	else if (!wr && access(f, R_OK) == -1)
		return (0);
	if (wr && access(f, F_OK) == -1)
		errno = 0;
	else if (wr && access(f, W_OK) == -1)
	{
		(*data)->error = 126;
		return (0);
	}
	if (!wr)
		return (open(f, O_RDONLY));
	if ((*data)->safe_word == NULL)
		return (open(f, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else
		return (open(f, O_WRONLY | O_CREAT | O_APPEND, 0644));
}

static void	export_file(t_data *data)
{
	char	*str;
	size_t	len;

	str = get_next_line(0);
	len = ft_strlen(str) - 1;
	if (len == 0)
		len = 1;
	while (ft_strncmp(str, data->safe_word, len)
		|| len != ft_strlen(data->safe_word))
	{
		ft_putstr_fd(str, data->fd[4]);
		free(str);
		str = get_next_line(0);
		len = ft_strlen(str) - 1;
		if (len == 0)
			len = 1;
	}
	free(str);
	close(data->fd[4]);
}

static t_data	*make_fd(t_data *data, char *f1, char *f2)
{
	int	fd[2];

	if (data->counter != 2)
		data->fd[0] = verify_files(&data, f1, 0);
	else
	{
		if (pipe(fd) == -1)
			kill_program(data, 1, NULL);
		data->fd[0] = fd[0];
		data->fd[4] = fd[1];
		export_file(data);
	}
	data->fd[3] = verify_files(&data, f2, 1);
	if ((data->fd[0] < 0 || data->fd[3] < 0))
		kill_program(data, 0, NULL);
	if (errno)
	{
		perror("pipex");
		data = handle_error(data);
	}
	return (data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	pid_t	pid;
	int		status;

	if (argc < 5)
	{
		write(2, "pipex: too few arguments\n", 25);
		exit(0);
	}
	data = init_data(argc, argv, envp);
	data = make_fd(data, argv[1], argv[argc - 1]);
	data = give_birth(data, argc);
	if (data->pid == 0)
		open_function(data, data->argv[data->counter + 1]);
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (pid == data->pid)
		{
			if (WIFEXITED(status))
				data->status = WEXITSTATUS(status);
		}
		pid = waitpid(-1, &status, 0);
	}
	kill_program(data, data->status, NULL);
}
