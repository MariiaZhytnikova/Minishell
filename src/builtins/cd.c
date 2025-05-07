/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:17:00 by ekashirs          #+#    #+#             */
/*   Updated: 2025/05/07 13:43:11 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_prev_pwd(t_list *env_var)
{
	t_list	*current;
	char	*prev_pwd;

	prev_pwd = NULL;
	current = env_var;
	while (current)
	{
		if (!ft_strncmp(current->content, "PWD=", 4))
		{
			prev_pwd = current->content;
			break ;
		}
		current = current->next;
	}
	return (prev_pwd);
}

static void	update_oldpwd(t_list *env_var, t_command *cmd)
{
	t_list	*current;
	char	*prev_pwd;

	prev_pwd = find_prev_pwd(env_var);
	if (!prev_pwd)
		return ;
	current = env_var;
	while (current)
	{
		if (!ft_strncmp(current->content, "OLDPWD=", 7))
		{
			free(current->content);
			current->content = NULL;
			current->content = ft_strjoin("OLDPWD=", prev_pwd + 4);
			if (current->content == NULL)
			{
				error_msg(ERR_BASH, ERR_MALLOC, NULL, NULL);
				cmd->status = 1;
			}
			return ;
		}
		current = current->next;
	}
}

static void	update_pwd(t_list *env_var, t_command *cmd, char *cur_dir)
{
	t_list	*current;

	current = env_var;
	while (current)
	{
		if (!ft_strncmp(current->content, "PWD=", 4))
		{
			free(current->content);
			current->content = NULL;
			current->content = ft_strjoin("PWD=", cur_dir);
			if (current->content == NULL)
			{
				error_msg(ERR_BASH, ERR_MALLOC, NULL, NULL);
				cmd->status = 1;
			}
			return ;
		}
		current = current->next;
	}
}

void	update_env(t_list *env_var, t_command *cmd)
{
	char	cur_dir[LEN_PATH];

	if (!getcwd(cur_dir, LEN_PATH))
	{
		error_msg(ERR_GETCWD, ERR_NO, NULL, NULL);
		cmd->status = 1;
		return ;
	}
	update_oldpwd(env_var, cmd);
	if (cmd->status == 1)
		return ;
	update_pwd(env_var, cmd, cur_dir);
	if (cmd->status == 1)
		return ;
}

void	cd_builtin(t_session *session, t_command *cmd)
{
	if (!cmd->args[1])
	{
		cd_no_path(session, cmd);
		return ;
	}
	if (cmd->args[2])
	{
		error_msg(ERR_BASH, cmd->args[0], ERR_MANY_ARGS, NULL);
		cmd->status = 1;
		return ;
	}
	if (chdir(cmd->args[1]) == -1)
	{
		error_msg(ERR_CD, cmd->args[1], ": ", strerror(errno));
		cmd->status = 1;
		return ;
	}
	update_env(session->env_var, cmd);
	if (cmd->status == 1)
		return ;
	cmd->status = 0;
}
