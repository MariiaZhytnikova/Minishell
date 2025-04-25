/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:47:31 by ekashirs          #+#    #+#             */
/*   Updated: 2025/04/25 12:47:02 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_plus_var(t_session *session, char *name, char *value)
{
	char	*content;
	t_list	*new;

	content = ft_strjoin(name, value);
	if (!content)
		return (1);
	new = ft_lstnew(content);
	if (!new)
	{
		free(content);
		return (1);
	}
	ft_lstadd_back(&session->env_var, new);
	return (0);
}

static void	add_new_plus(t_session *s, t_command *cmd, char *var, size_t len)
{
	char	*name;
	char	*value;
	int		status;

	name = ft_substr(var, 0, len);
	if (!name)
	{
		cmd->status = 1;
		return ;
	}
	value = ft_substr(var, len + 1, ft_strlen(var) - len - 1);
	if (!value)
	{
		cmd->status = 1;
		free(name);
		return ;
	}
	status = create_plus_var(s, name, value);
	if (status)
		cmd->status = 1;
	free(name);
	free(value);
}

int	check_for_plus(char *var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[i]) && var[i] != '_')
		return (0);
	i++;
	while (var[i] && var[i] != '+' && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	if (var[i] == '+' && var[i + 1] == '=')
		return (1);
	else
		return (0);
}

void	append_env(t_session *session, t_command *cmd, char *var)
{
	size_t	len;
	t_list	*ptr;
	char	*new_content;

	len = ft_var_name_len(var);
	ptr = session->env_var;
	while (ptr)
	{
		if (!ft_strncmp(ptr->content, var, len)
			&& ((char *)ptr->content)[len] == '=')
		{
			new_content = ft_strjoin(ptr->content, var + len + 2);
			if (!new_content)
			{
				cmd->status = 1;
				return ;
			}
			free(ptr->content);
			ptr->content = new_content;
			return ;
		}
		ptr = ptr->next;
	}
	add_new_plus(session, cmd, var, len);
}
