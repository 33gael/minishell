/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 14:11:42 by thbosvie          #+#    #+#             */
/*   Updated: 2026/04/08 20:51:00 by thbosvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*copy_env(char *envp, t_env *env)
{
	char	**argv;
	t_env	*node;
	t_env	*first;

	first = env;
	argv = ft_split(envp, '=');
	if (argv)
	{
		node = create_node(argv[0], argv[1]);
		if (!env)
			env = node;
		else
			add_back_copy(env, node);
		free_array(argv);
	}
	if (!first)
		return (env);
	return (first);
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	int		i;
	char	*cwd;

	if (!envp || !envp[0])
	{
		cwd = getcwd(NULL, 0);
		env = create_node("PWD", cwd);
		if (cwd)
			free(cwd);
		add_back_copy(env, create_node("SHLVL", "1"));
		add_back_copy(env, create_node("_", "/usr/bin/env"));
		return (env);
	}
	env = NULL;
	i = 0;
	while (envp[i])
	{
		env = copy_env(envp[i], env);
		i++;
	}
	return (env);
}

char	*ft_get_env(t_env *env, char *var_name)
{
	int		size;
	char	*tmp;

	if (ft_strncmp(var_name, "?", 2) == 0)
	{
		tmp = ft_itoa(g_signal);
		return (tmp);
	}
	while (env)
	{
		size = ft_strlen(var_name);
		if (ft_strlen(env->key) > (size_t)size)
			size = ft_strlen(env->key);
		if (ft_strncmp(env->key, var_name, size) == 0)
		{
			if (env->value)
			{
				tmp = ft_strdup(env->value);
				return (tmp);
			}
			return (NULL);
		}
		env = env->next;
	}
	return (NULL);
}

char	**list_to_array(t_env *env)
{
	char	**array;
	char	*tmp;
	int		i;

	i = 0;
	array = malloc(sizeof(char *) * (get_env_size(env) + 1));
	if (!array)
		return (NULL);
	while (env)
	{
		if (env->value)
		{
			tmp = ft_strjoin(env->key, "=");
			array[i] = ft_strjoin(tmp, env->value);
			free(tmp);
		}
		else
			array[i] = ft_strdup(env->key);
		i++;
		env = env->next;
	}
	array[i] = NULL;
	return (array);
}

void	increment_shlvl(t_env **env)
{
	t_env	*node;
	int		num;
	char	*new_val;

	node = find_env_node(*env, "SHLVL");
	if (!node)
	{
		add_back_env(env, create_env_node("SHLVL", "1"));
		return ;
	}
	num = ft_atoi(node->value);
	num++;
	new_val = ft_itoa(num);
	free(node->value);
	node->value = new_val;
}
