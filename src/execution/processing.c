/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:38:27 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/25 14:38:51 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_not_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (!S_ISDIR(path_stat.st_mode));
}

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

static char	*get_path(t_command *cmd, t_list *env)
{
	char	**paths;
	char	*cur_cmd;
	t_list	*current;

	current = search_in_env(env, "PATH");
	if (!current)
	{
		cmd->status = 127;
		return (error_msg(ERR_BASH, cmd->args[0], ERR_NO, NULL), NULL);
	}
	paths = ft_split(current->content, ':');
	if (!paths)
		return (error_msg(ERR_BASH, ERR_MALLOC, NULL, NULL), NULL);
	cur_cmd = access_path(paths, cmd->args[0]);
	if (!cur_cmd)
	{
		cmd->status = 127;
		if (paths)
			free_arr(paths);
		return (error_msg(ERR_BASH, cmd->args[0], ERR_CMD, NULL), NULL);
	}
	if (paths)
		free_arr(paths);
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
	if (!access(path, F_OK) && !is_not_directory(path))
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
	status = execve(path, cmd->args, env);
	if (status == -1)
	{
		cmd->status = 127;
		free(path);
		free_arr(env);
		group_free(session);
		error_msg(ERR_BASH, cmd->args[0], ERR_CMD, NULL);
		exit (cmd->status);
	}
}
