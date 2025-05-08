/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:17:32 by ekashirs          #+#    #+#             */
/*   Updated: 2025/05/08 19:29:38 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_only_full_var(t_list *lst)
{
	t_list	*current;
	char	*entry;
	char	*equal_sign;

	current = lst;
	while (current != NULL)
	{
		entry = (char *)current->content;
		equal_sign = ft_strchr(entry, '=');
		if (equal_sign && (*(equal_sign + 1) != '\0'
				|| *(equal_sign + 1) == '\0'))
			printf("%s\n", entry);
		current = current->next;
	}
}

void	env_builtin(t_session *session, t_command *cmd)
{
	if (cmd->args[1])
	{
		error_msg (ERR_ENV, cmd->args[1], ERR_NO, NULL);
		cmd->status = 127;
		return ;
	}
	print_only_full_var(session->env_var);
	cmd->status = 0;
}
