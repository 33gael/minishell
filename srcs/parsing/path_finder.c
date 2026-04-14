/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 16:47:27 by thbosvie          #+#    #+#             */
/*   Updated: 2026/04/06 19:24:56 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_path(char **strs, char *cmd)
{
	char	*str;
	char	*tmp;
	int		i;

	i = 0;
	while (strs[i])
	{
		tmp = ft_strjoin(strs[i], "/");
		if (!tmp)
			return (NULL);
		str = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(str, F_OK | X_OK) == 0)
			return (str);
		else
			free(str);
		i++;
	}
	return (NULL);
}

int	verif_dot_slash(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != '.' && cmd[i] != '/')
			return (0);
		i++;
	}
	return (1);
}

char	*path_finder(char *cmd, char *path)
{
	char	**strs;
	char	*str;

	if (verif_dot_slash(cmd))
		return (NULL);
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	if (!path || path[0] == '\0')
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
		return (NULL);
	strs = ft_split(path, ':');
	if (!strs)
		return (NULL);
	str = check_path(strs, cmd);
	free_array(strs);
	if (str)
		return (str);
	return (NULL);
}
