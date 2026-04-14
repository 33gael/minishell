/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 14:11:39 by thbosvie          #+#    #+#             */
/*   Updated: 2026/04/12 00:04:21 by thbosvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node(t_env *env)
{
	free(env->key);
	free(env->value);
	env->next = NULL;
	free(env);
}

void	free_env(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		free_node(env);
		env = next;
	}
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
	}
	if (array)
		free(array);
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->outfile)
			free(tmp->outfile);
		if (tmp->infile)
			free(tmp->infile);
		if (tmp->heredoc)
			free(tmp->heredoc);
		if (tmp->append)
			free(tmp->append);
		if (tmp->args)
			free_array(tmp->args);
		free(tmp);
	}
}

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->content);
		free(tmp);
	}
}
