/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 17:09:11 by thbosvie          #+#    #+#             */
/*   Updated: 2026/04/08 14:17:08 by thbosvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_fill_init(t_token *token, t_cmd *cmd)
{
	cmd->next = NULL;
	cmd->infile = NULL;
	cmd->append = NULL;
	cmd->heredoc = NULL;
	cmd->args = cmd_args_init(token);
	cmd->outfile = NULL;
}

static t_cmd	*cmd_fill(t_token **token)
{
	t_cmd	*cmd;
	int		i;
	char	*tmp_arg;

	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd_fill_init(*token, cmd);
	i = -1;
	if ((*token)->type == PIPE)
		*token = (*token)->next;
	while (*token && (*token)->type != PIPE)
	{
		if ((*token)->type != WORD)
			cmd_other_type(token, &cmd);
		else if ((*token)->type == WORD && check_space_tab((*token)->content)
			&& (*token)->quote == 0)
			cmd->args = create_cmd_expand(token, &i, cmd->args);
		else
		{
			tmp_arg = create_cmd_arg(token, &i);
			cmd->args[i] = tmp_arg;
		}
	}
	cmd->args[i + 1] = NULL;
	return (cmd);
}

static void	add_back_cmd(t_cmd *cmd, t_cmd *node)
{
	while (cmd->next)
		cmd = cmd->next;
	cmd->next = node;
}

t_cmd	*create_cmd(t_token **token, t_cmd *cmd)
{
	t_cmd	*next;

	next = cmd_fill(token);
	if (cmd != NULL)
		add_back_cmd(cmd, next);
	return (next);
}
