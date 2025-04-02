/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:32:49 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/01 13:01:31 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// echo $USER | ls -l $HOME || echo 'Path is $PWD'

static int	is_unfinished(char *input)
{
	int	i;

	i = ft_strlen(input) - 1;
	while (i >= 0 && (input[i] == ' ' || input[i] == '\t'))
		i--;
	if (i >= 0 && (input[i] == '|' || input[i] == '<'))
	{
		if (input[i] == '<' && i > 0 && input[i - 1] == '<')
			return (1);
		else if (input[i] == '|')
			return (1);
	}
	return (0);
}

static char	*create_prompt(void)
{
	char	cwd[1024];
	char	*prompt;
	char	*temp;

	prompt = NULL;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		temp = ft_strjoin("\001" GREEN BOLD "\002", cwd);
		prompt = ft_strjoin(temp, "\001" GREEN BOLD "\002$ \001" RESET "\002");
		free(temp);
	}
	else
		ft_strdup(PROMPT);
	return (prompt);
}

static int	add_clean(t_session *session)
{
	char	*clean_command;

	clean_command = ft_strtrim(session->input, " \t\n");
	if (clean_command && *clean_command)
	{
		add_history(clean_command);
		free(clean_command);
		return (0);
	}
	else
	{
		free(clean_command);
		return (-1);
	}
}

static int	read_multiline_input(t_session *session)
{
	char	*new_line;
	char	*temp;

	while (session->input && is_unfinished(session->input))
	{
		new_line = readline("> ");
		if (!new_line)
			return (-1);
		temp = ft_strjoin(session->input, " ");
		if (!temp)
		{
			free(new_line);
			free(session->input);
			return (-1);
		}
		free(session->input);
		session->input = ft_strjoin(temp, new_line);
		free(temp);
		free(new_line);
		if (!session->input)
			return (-1);
	}
	return (0);
}

int	prompt(t_session *session)
{
	char	*prompt_str;
	int		status;

	prompt_str = create_prompt();
	session->input = readline(prompt_str);
	free(prompt_str);
	if (!session->input || *session->input == '\0')
		return (-1);
	status = read_multiline_input(session);
	if (status < 0)
		return (-1);
	return (add_clean(session));
}

