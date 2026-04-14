/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:30:09 by gaeducas          #+#    #+#             */
/*   Updated: 2026/04/08 13:05:21 by thbosvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	unset_variable(t_env **env_list, char *var_name)
{
	t_env	*current;
	t_env	*prev;

	if (!env_list || !*env_list || !var_name)
		return ;
	current = *env_list;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, var_name) == 0)
		{
			if (prev == NULL)
				*env_list = current->next;
			else
				prev->next = current->next;
			free(current->key);
			if (current->value)
				free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_unset(t_env **env_list, char **args)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (args[i])
	{
		unset_variable(env_list, args[i]);
		i++;
	}
	return (status);
}
