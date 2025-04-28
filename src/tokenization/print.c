/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:21:09 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/28 12:42:15 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_linked_list(t_list *lst)
{
	t_list	*current;

	current = lst;
	while (current != NULL)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
}

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
	int num_red;

	printf("\n-->> WE HAVE COMMANDS!!! <<--\n");
	i = 0;
	j = 0;
	printf("%sThe commands are:%s\n\n", MAGENTA, RESET);
	while (i < session->count->cmd_nb)
	{
		j = 0;
		while (j < session->count->args_nb[i])
		{
			printf("%s>%s< %s", MAGENTA, session->cmds[i]->args[j], RESET);
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
		num_red = session->count->red_in_nb[i] + \
			session->count->red_out_nb[i] + session->count->red_app_nb[i];
		
		j = 0;
		if (num_red > 0)
		{
			printf("FILES\n");
			while (session->cmds[i]->files[j])
				printf("%s\n", session->cmds[i]->files[j++]->name);
		}
		j = 0;
		printf("IN_FILE is: %s\n", session->cmds[i]->last_in->name);
		printf("IN_FILE is: %s\n", session->cmds[i]->last_out->name);
		// if (session->count->red_h_doc_nb[i] > 0)
		// {
		// 	printf("IN HERE_DOC %d\n", session->count->red_h_doc_nb[i]);
		// 	while (session->cmds[i]->h_doc[j])
		// 		printf("%s\n", session->cmds[i]->h_doc[j++]);
		// }
		i++;
	}
	printf("%s\n", RESET);
/////////////////////////////////////////////////////////////////////////////////////////////////
}
