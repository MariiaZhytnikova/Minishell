/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:32:49 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/08 18:55:26 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_me_num(t_count *count)
{
	int	i;

	///////////////////////TO DELETE///////////////////////////////////////////
	printf("\n ***--- Statistic ---***\n");
	printf("%scmd_number         : %d\n", CYAN, count->cmd_nb);
	printf("delimiter_number   : %d\n", count->delimiter_nb);
	i = 0;
	while (i < count->cmd_nb)
	{
		printf("\nCommand %i: \n", i);
		printf("args_number         : %d\n", count->args_nb[i]);
		printf("red_in_nb           : %d\n", count->red_in_nb[i]);
		printf("red_out_nb          : %d\n", count->red_out_nb[i]);
		printf("red_append_nb       : %d\n", count->red_app_nb[i]);
		printf("red_here_doc_nb     : %d\n", count->red_h_doc_nb[i]);
		i++;
	}
	printf("DONE...%s\n", RESET);
	//////////////////////////////////////////////////////////////////
}

void	print_me(t_session *session)
{
//////////////////////TO DELETE//////////////////////////////////////////////////////////////////////////
	int	i;
	int	j;
	printf("\n-->> WE HAVE COMMANDS!!! <<--\n");
	i = 0;
	j = 0;
	printf("%sThe commands are:%s\n\n", MAGENTA, RESET);
	while (i < session->count->cmd_nb)
	{
		j = 0;
		while (j < session->count->args_nb[i])
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
}

int	commands(t_session *session, t_list **token)
{
	t_list	*curr;
	t_count	*cnt;
	int		i;

	cnt = ft_calloc(1, sizeof(t_count));
	if (!cnt)
		return (-1);
	if (numbers(session, token, cnt) < 0)
		return (error_msg("Something wrong numbers", NULL, NULL, NULL), -1);
	session->count = cnt;
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
	print_me(session);
	return (1);
}

int	split_and_check(t_session *session, t_list **token, char *src)
{
	char	*input;
	int		status;

	input = add_spaces(session, src);
	if (!input)
		return (error_msg("Something wrong add_spaces", NULL, NULL, NULL), -1);
	if (split_input(session, token, input) < 0)
		return (free(input), error_msg("Something wrong split_input", NULL, NULL, NULL), -1);
	free(input);
	if (delimiter_wrong_pos(*token) == true)
		return (error_msg("Something wrong delimiter_wrong_pos", NULL, NULL, NULL), -1);
	if (consecutive_delimiters(*token) == true)
		return (error_msg("Something wrong consecutive_delimiters", NULL, NULL, NULL), -1);
	status = here_doc_lim(session, token);
	if (status < 0)
		return (error_msg("Herre doc no lim problem", NULL, NULL, NULL), -1);
	if (status == 2 || status == 3)
		return (2);
	status = here_doc_no_lim(session, token);
	if (status < 0)
		return (error_msg("Herre doc lim problem", NULL, NULL, NULL), -1);
	if (status > 0)
		return (status);
	if (wild(token) < 0)
		return (error_msg("Wild problem", NULL, NULL, NULL), -1);
	return (1);
}

int	lexical_analyzer(t_session *session)
{
	t_list	*token;
	int		status;

	token = NULL;
	status = split_and_check(session, &token, session->input);
	if (status < 0)
	{
		free(session->input);
		if (token)
			ft_lstclear(&token, free);
		return (error_msg("Something wrong split_input", NULL, NULL, NULL), -1);
	}
	if (status == 3)
	{
		if (session->input)
			free(session->input);
		if (token)
			ft_lstclear(&token, free);
		return (3);
	}
	if (signalnum == 2)
	{
		if (session->input)
			free(session->input);
		if (token)
			ft_lstclear(&token, free);
		return (-1);
	}	
	if (commands(session, &token) < 0)
	{
		ft_lstclear(&token, free);
		free_session(session);
		return (error_msg("Something wrong commands", NULL, NULL, NULL), -1);
	}
	ft_lstclear(&token, free);
	return (1);
}
