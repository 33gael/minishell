/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:45:20 by gaeducas          #+#    #+#             */
/*   Updated: 2026/04/09 17:24:35 by thbosvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	free_heredoc_signal(char *input, int fd, int save_stdin)
{
	if (input)
		free(input);
	close(fd);
	dup2(save_stdin, STDIN_FILENO);
	close(save_stdin);
	init_signals();
	return (1);
}

int	signal_heredoc(char *input, char *end_of_file)
{
	if (!input || ft_strcmp(input, end_of_file) == 0)
	{
		if (!input)
			printf("minishell: warning: heredoc delimited by EOF\n");
		else
			free(input);
		return (1);
	}
	return (0);
}

void	end_heredoc(int save_stdin, int fd)
{
	close(fd);
	dup2(save_stdin, STDIN_FILENO);
	close(save_stdin);
	init_signals();
}

void	write_heredoc(int fd, char *input)
{
	write(fd, input, ft_strlen(input));
	write(fd, "\n", 1);
	free(input);
}

int	ft_heredoc(char *end_of_file, int need_to_expand, t_shell *shell)
{
	int		fd;
	char	*input;
	int		save_stdin;

	g_signal = 0;
	fd = open("/tmp/tempfile", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	save_stdin = dup(STDIN_FILENO);
	init_signals_heredoc();
	while (1)
	{
		input = readline("heredoc> ");
		if (g_signal == 130)
			if (free_heredoc_signal(input, fd, save_stdin))
				return (1);
		if (signal_heredoc(input, end_of_file))
			break ;
		if (need_to_expand == 0 && check_dollar(input))
			input = expand_token(input, shell);
		write_heredoc(fd, input);
	}
	end_heredoc(save_stdin, fd);
	return (0);
}
