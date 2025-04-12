/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:38:27 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/11 16:16:57 by mzhitnik         ###   ########.fr       */
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
			return (error_msg("cur_path in access_path dead", NULL, NULL, NULL), NULL);
		cur_cmd = ft_strjoin(cur_path, cmd);
		if (!cur_cmd)
			return (free(cur_path), error_msg("cur_cmd in access_path dead", NULL, NULL, NULL), NULL);
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
		return (error_msg("bash: /user/ls: No such file or directory", NULL, NULL, NULL), NULL);
	}
	paths = ft_split(current->content, ':');
	if (!paths)
		return (error_msg("ft_split in get_path return NULL", NULL, NULL, NULL), NULL);
	cur_cmd = access_path(paths, cmd->args[0]);
	if (!cur_cmd)
	{
		cmd->status = 127;
		return (free_arr(paths), error_msg("Command not found:  ...", NULL, NULL, NULL), NULL);
	}
	return (free_arr(paths), cur_cmd);
}

static char	*path_check(t_command *cmd, t_list *env)
{
	char	*path;

	if (!ft_strchr(cmd->args[0], '/'))
		return (get_path(cmd, env));
	path = ft_strdup(cmd->args[0]);
	if (!path)
		return (error_msg("ft_strdup failed ...", NULL, NULL, NULL), NULL);
	if (access(path, F_OK | X_OK) == 0)
		return (path);
	else if (cmd->args[0][0] == '.' && cmd->args[0][1] == '/')
	{
		cmd->status = 126;
		return (error_msg("Permission denied for file: ...", NULL, NULL, NULL), NULL);
	}
	else
	{
		cmd->status = 127;
		return (error_msg("No such file or directory: ...", NULL, NULL, NULL), NULL);
	}
}

void	exec_norm(t_session *session, t_command *cmd)
{
	char	*path;
	char	**env;

	ft_putstr_fd("The command in exec_norm: ", 2);
	ft_putendl_fd(cmd->args[0], 2);
	ft_putendl_fd(" ", 2);
	path = path_check(cmd, session->env_var);
	if (!path)
	{
		exit (cmd->status);
	}
	env = list_to_arr(session->env_var);
	if (execve(path, cmd->args, env) == -1)
	{
		cmd->status = 127;
		free(path);
		free_arr(env);
		ft_lstclear(&session->env_var, free);
		free_session(session); // NOT everything FREED
		rl_clear_history();
		return (error_msg("Command not found:  ...", NULL, NULL, NULL));
		exit (cmd->status);
	}
}
