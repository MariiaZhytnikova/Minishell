/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:26:21 by ekashirs          #+#    #+#             */
/*   Updated: 2025/05/12 14:01:23 by ekashirs         ###   ########.fr       */
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
			&& (((char *)ptr->content)[len] == '='
			|| ((char *)ptr->content)[len] == '\0'))
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

static void	without_equal(t_session *session, t_command *cmd, char *var)
{
	char	*new_value;

	if (search_in_env(session->env_var, var))
		return ;
	new_value = ft_strdup(var);
	if (!new_value)
	{
		error_msg(ERR_BASH, ERR_MALLOC, NULL, NULL);
		cmd->status = 1;
		return ;
	}
	add_new_var(session, cmd, new_value);
	if (cmd->status == 1)
		free(new_value);
}

static void	prepare_add_var(t_session *session, t_command *cmd, char *var)
{
	char	*new_value;

	if (!ft_strchr(var, '='))
	{
		without_equal(session, cmd, var);
		return ;
	}
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
		if (check_for_plus(cmd->args[i]))
		{
			append_env(session, cmd, cmd->args[i]);
			return ;
		}
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
