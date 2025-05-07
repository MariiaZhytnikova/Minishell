/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:38:27 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/05/07 13:31:07 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*access_path(char **paths, char *cmd)
{
	int		i;
	char	*cur_path;
	char	*cur_cmd;

	i = 0;
	while (paths[i])
	{
		cur_path = ft_strjoin(paths[i++], "/");
		if (!cur_path)
			return (error_msg(ERR_BASH, ERR_MALLOC, NULL, NULL), NULL);
		cur_cmd = ft_strjoin(cur_path, cmd);
		if (!cur_cmd)
			return (free(cur_path), NULL);
		free(cur_path);
		if (access(cur_cmd, F_OK | X_OK) == 0)
			return (cur_cmd);
		free(cur_cmd);
	}
	return (NULL);
}

static char	**split_path(t_command *cmd, t_list *current)
{
	char	**paths;
	char	**temp;

	temp = ft_split(current->content, '=');
	if (!temp)
		return (error_msg(ERR_BASH, ERR_MALLOC, NULL, NULL), NULL);
	if (!temp[1] && !is_directory(cmd->args[0]))
	{
		free_arr(temp);
		return (error_msg(ERR_BASH, cmd->args[0], ERR_ISADIR, 0), NULL);
	}
	else if (!temp[1])
	{
		free_arr(temp);
		return (error_msg(ERR_BASH, cmd->args[0], ERR_NO, 0), NULL);
	}
	paths = ft_split(temp[1], ':');
	free_arr(temp);
	if (!paths)
		return (error_msg(ERR_BASH, ERR_MALLOC, NULL, NULL), NULL);
	return (paths);
}

static char	*get_path(t_command *cmd, t_list *env)
{
	char	**paths;
	char	*cur_cmd;
	t_list	*current;

	current = search_in_env(env, "PATH");
	if (!current || !current->content)
		return (get_current_path(cmd));
	paths = split_path(cmd, current);
	if (!paths)
		return (NULL);
	cur_cmd = access_path(paths, cmd->args[0]);
	free_arr(paths);
	if (!cur_cmd)
	{
		cmd->status = 127;
		return (error_msg(ERR_BASH, cmd->args[0], ERR_CMD, NULL), NULL);
	}
	return (cur_cmd);
}

static char	*path_check(t_command *cmd, t_list *env)
{
	char	*path;

	if (!ft_strchr(cmd->args[0], '/'))
		return (get_path(cmd, env));
	path = ft_strdup(cmd->args[0]);
	if (!path)
		return (error_msg(ERR_BASH, ERR_MALLOC, NULL, NULL), NULL);
	if (!access(path, F_OK) && !is_directory(path))
	{
		cmd->status = 126;
		return (error_msg(ERR_BASH, path, ERR_ISADIR, NULL), free(path), NULL);
	}
	if (access(path, F_OK | X_OK) == 0)
		return (path);
	else if (!access(path, F_OK) && cmd->args[0][0] == '.'
			&& cmd->args[0][1] == '/')
	{
		cmd->status = 126;
		return (free(path), error_msg(ERR_BASH, cmd->args[0], ERR_PE, 0), NULL);
	}
	else
	{
		cmd->status = 127;
		return (free(path), error_msg(ERR_BASH, cmd->args[0], ERR_NO, 0), NULL);
	}
}

void	exec_norm(t_session *session, t_command *cmd)
{
	char	*path;
	char	**env;
	int		status;

	path = path_check(cmd, session->env_var);
	if (!path)
	{
		session->status_last = cmd->status;
		group_free(session);
		exit (session->status_last);
	}
	env = list_to_arr(session->env_var);
	if (execve(path, cmd->args, env) == -1)
	{
		error_msg(ERR_BASH, cmd->args[0], ERR_CMD, NULL);
		status = 127;
		free(path);
		free_arr(env);
		group_free(session);
		exit (status);
	}
}
