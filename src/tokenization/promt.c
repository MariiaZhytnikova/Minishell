/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:32:49 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/26 16:28:38 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// echo $USER | ls -l $HOME || echo 'Path is $PWD'

int	commands(t_session *session, t_list **token)
{
	t_list	*curr;
	t_count	cnt;
	int		i;

	if (numbers(token, &cnt) < 0)
		return (error_msg("Something wrong numbers", NULL, NULL, NULL), -1);
	session->count = &cnt;
	if (allocate_struct(session, &cnt, 0) < 0)
		return (error_msg("Something wrong with alloc", NULL, NULL, NULL), -1);
	curr = *token;
	i = 0;
	while (curr)
	{
		if (is_del(curr->content) == false)
		{
			if (handle_command(session->cmds[i], &curr, 0) < 0)
				return (error_msg("wrong with strdup\n", NULL, NULL, NULL), -1);
			if (curr && is_del(curr->content) == true)
				get_delimiter(session->cmds[i++], curr);
		}
		if (curr)
			curr = curr->next;
	}
//////////////////////TO DELETE//////////////////////////////////////////////////////////////////////////
	int	j;
	printf("\n-->> WE HAVE COMMANDS!!! <<--\n");
	i = 0;
	j = 0;
	printf("%sThe commands are:%s\n\n", MAGENTA, RESET);
	while (i < cnt.cmd_nb)
	{
		j = 0;
		while (j < cnt.args_nb[i])
		{
			printf("%s%s %s", MAGENTA, session->cmds[i]->args[j], RESET);
			j++;
		}
		if (session->cmds[i]->type == 1)
			printf("%s\ndelimeter is: PIPE%s\n", WHITE, RESET);
		if (session->cmds[i]->type == 2)
			printf("%s\ndelimeter is: AND%s\n", WHITE, RESET);
		if (session->cmds[i]->type == 3)
			printf("%s\ndelimeter is: OR%s\n", WHITE, RESET);
		if (session->cmds[i]->type == 0)
			printf("%s\ndelimeter is: NONE%s\n", WHITE, RESET);
		i++;
	}
	i = 0;
	j = 0;
	printf("\n-->> WE HAVE FILES!!! <<--%s\n", YELLOW);
	while (i < session->count->cmd_nb)
	{
		j = 0;
		if (session->count->red_in_nb[i] > 0)
		{
			printf("IN FILES %d\n", session->count->red_in_nb[i]);
			while (session->cmds[i]->in[j])
				printf("%s: %s\n", session->cmds[i]->command, session->cmds[i]->in[j++]);
		}
		j = 0;
		if (session->count->red_h_doc_nb[i] > 0)
		{
			printf("IN HERE_DOC %d\n", session->count->red_h_doc_nb[i]);
			while (session->cmds[i]->h_doc[j])
				printf("%s: %s\n", session->cmds[i]->command, session->cmds[i]->h_doc[j++]);
		}
		j = 0;
		if (session->count->red_out_nb[i] > 0)
		{
			printf("OUT FILES %d\n", session->count->red_out_nb[i]);
			while (session->cmds[i]->out[j])
				printf("%s: %s\n", session->cmds[i]->command, session->cmds[i]->out[j++]);
		}
		j = 0;
		if (session->count->red_app_nb[i] > 0)
		{
			printf("OUT APPEND FILES %d\n", session->count->red_app_nb[i]);
			while (session->cmds[i]->out_app[j])
				printf("%s: %s\n", session->cmds[i]->command, session->cmds[i]->out_app[j++]);
		}
		i++;
	}
	printf("%s\n", RESET);
/////////////////////////////////////////////////////////////////////////////////////////////////
	return (1);
}

int	lexical_analyzer(t_session *session)
{
	t_list	*token;

	token = NULL;
	if (split_and_check(&token, session->input) < 0)
		return (ft_lstclear(&token, free), -1);
	printf("\nNow tokens are:\n");
	print_linked_list(token);
	printf("-------------\n");
	if (commands(session, &token) < 0)
		return (error_msg("Something wrong commands", NULL, NULL, NULL), -1);
	ft_lstclear(&token, free);
	return (1);
}

void	promt(t_session *session)
{
	char	cwd[1024];
	char	*temp;
	char	*prompt;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		temp = ft_strjoin(GREEN BOLD, cwd);
		prompt = ft_strjoin(temp, "$ " RESET);
		free(temp);
	}
	else
		prompt = ft_strdup(GREEN BOLD "minishell$ " RESET);
	session->input = readline(prompt);
	free(prompt);
	if (session->input && *session->input)
		add_history(session->input);
	if (!session->input)
		error_msg("Something wrong", NULL, NULL, NULL);
}
