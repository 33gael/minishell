/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:39:23 by gaeducas          #+#    #+#             */
/*   Updated: 2026/04/08 12:36:31 by thbosvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_or_add_env(t_env **env, char *key, char *value)
{
	t_env	*node;

	node = find_env_node(*env, key);
	if (node)
	{
		if (value != NULL)
		{
			if (node->value)
				free(node->value);
			node->value = ft_strdup(value);
		}
	}
	else
	{
		add_back_env(env, create_env_node(key, value));
	}
}

static int	process_export_arg(t_env **env, char *arg)
{
	char	*key;
	char	*value;

	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("minishell: export: not a valid identifier\n", 2);
		return (0);
	}
	key = extract_key(arg);
	value = extract_value(arg);
	update_or_add_env(env, key, value);
	free(key);
	if (value)
		free(value);
	return (1);
}

static int	print_sorted_env(t_env *env)
{
	t_env	**array;
	int		count;
	int		i;

	count = count_env_nodes(env);
	array = create_env_array(env, count);
	if (!array)
		return (1);
	sort_env_array(array, count);
	i = 0;
	while (i < count)
	{
		printf("declare -x ");
		printf("%s", array[i]->key);
		if (array[i]->value)
		{
			printf("=\"");
			printf("%s", array[i]->value);
			printf("\"");
		}
		printf("\n");
		i++;
	}
	free(array);
	return (0);
}

int	ft_export(t_env **env, char **args)
{
	int	i;
	int	exit_status;

	exit_status = 0;
	if (!args[1])
	{
		print_sorted_env(*env);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (!process_export_arg(env, args[i]))
			exit_status = 1;
		if (exit_status == 1)
			break ;
		i++;
	}
	return (exit_status);
}
