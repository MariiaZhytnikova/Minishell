/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:26:21 by ekashirs          #+#    #+#             */
/*   Updated: 2025/04/08 18:22:06 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	var_name_validation(char *var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[i]) && var[i] != '_')
		return (0);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	export_content(t_session *s, t_command *cmd, char *val, char *var)
{
	size_t	len;
	t_list	*ptr;

	len = ft_var_name_len(var);
	ptr = s->env_var;
	while (ptr)
	{
		if (!ft_strncmp(ptr->content, var, len)
			&& ((char *)ptr->content)[len] == '=')
		{
			free(ptr->content);
			ptr->content = val;
			return ;
		}
		ptr = ptr->next;
	}
	add_new_var(s, cmd, val);
	if (cmd->status == 1)
		return ;
}

static void	prepare_add_var(t_session *session, t_command *cmd, char *var)
{
	t_list	*ptr;
	char	*new_value;

	new_value = ft_strdup(var);
	if (!new_value)
	{
		error_msg(ERR_BASH, ERR_MALLOC, NULL, NULL);
		cmd->status = 1;
		return ;
	}
	export_content(session, cmd, new_value, var);
	if (cmd->status == 1)
	{
		free(new_value);
		return ;
	}
}

void	handle_args(t_session *session, t_command *cmd)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		if (var_name_validation(cmd->args[i]))
		{
			prepare_add_var(session, cmd, cmd->args[i]);
			if (cmd->status == 1)
				return ;
		}
		else
		{
			error_msg(ERR_BASH, ERR_EXPORT, cmd->args[i], ERR_IDEN);
			cmd->status = 1;
			return ;
		}
		i++;
	}
	cmd->status = 0;
}
