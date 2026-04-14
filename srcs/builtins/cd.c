/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 13:55:52 by gaeducas          #+#    #+#             */
/*   Updated: 2026/04/10 10:29:57 by thbosvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_add_new_env(t_env *last_node, char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (1);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	if (!new_node->key || !new_node->value)
	{
		free(new_node->key);
		free(new_node->value);
		free(new_node);
		return (1);
	}
	last_node->next = new_node;
	return (0);
}

static int	ft_update_env(t_env *env, char *key_name, char *new_value)
{
	t_env	*current;

	if (!env || !key_name || !new_value)
		return (1);
	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, key_name) == 0)
		{
			if (current->value)
				free(current->value);
			current->value = ft_strdup(new_value);
			if (!current->value)
				return (1);
			return (0);
		}
		if (!current->next)
			break ;
		current = current->next;
	}
	if (ft_add_new_env(current, key_name, new_value) != 0)
		return (1);
	return (0);
}

static void	ft_update_pwd(t_env *env, char *old_pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (old_pwd)
	{
		ft_update_env(env, "OLDPWD", old_pwd);
		free(old_pwd);
	}
	if (new_pwd)
	{
		ft_update_env(env, "PWD", new_pwd);
		free(new_pwd);
	}
}

void	free_target(char *target, int n_arg)
{
	if (n_arg == 1)
		free(target);
}

int	ft_cd(char **path, t_env *env)
{
	char	*old_pwd;
	char	*target;
	int		n_arg;

	n_arg = n_arg_init(path);
	if (check_arg_cd(n_arg))
		return (1);
	target = path[1];
	if (n_arg == 1 || !target)
		target = ft_get_env(env, "HOME");
	if (!target)
	{
		ft_putstr_fd("error: cd: HOME not set\n", 2);
		return (1);
	}
	old_pwd = getcwd(NULL, 0);
	if (chdir(target) == -1)
	{
		ft_putstr_fd("error: cd: No such file or directory\n", 2);
		free(old_pwd);
		return (1);
	}
	free_target(target, n_arg);
	ft_update_pwd(env, old_pwd);
	return (0);
}
