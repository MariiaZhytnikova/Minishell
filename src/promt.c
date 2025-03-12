/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:32:49 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/12 10:37:00 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	quotes_balanced(const char *str) 
// {
// 	int	i;
// 	int	quote_count;

// 	i = 0;
// 	quote_count = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'')
// 			quote_count++;
// 		i++;
// 	}
// 	return (quote_count % 2 == 0);
// }

// static int	exclusion_check(char *str) // if c == ';' ||  c == '\' || or Unclosed quote-> error EXCLUSION
// {
// 	int	i;

// 	i = 0;
// 	if (!str)
// 		return (1);
// 	while (str[i])
// 	{
// 		if (str[i] == ';' || str[i] == '\\' || !quotes_balanced)
// 			return (error_msg(EXCLUSION), 1);
// 		i++;
// 	}
// 	return (0);
// }

// static int	skip_whitespace(const char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (!str)
// 		return (0);
// 	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r')
// 	{
// 		i++;
// 	}
// 	return (i);
// }

// static bool	is_special (const char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (!str)
// 		return (1);
// 	while (str[i])
// 	{
// 		if (str[i] == '|')
// 			type = PIPE;
// 		else if (str[i] == '&')
// 			type = AND;
// 		else if (str[i] == '>')
// 			type = REDIRECT_OUTPUT;
// 		else if (str[i] == '<')
// 			type = REDIRECT_INPUT;
// 		else if (str[i] == '>>')
// 			type = REDIRECT_OUTPUT_APPEND;
// 		else if (str[i] == '<<')
// 			type = HEREDOC; // not update history
// 		i++;
// 	}
// 	return (0);
// }

// TokenType	lexical_analyzer(t_session *session) // in loop set type?
// {
// 	int i;
// 	TokenType	token;
	
// 	if (exclusion_check(session->input))
// 		free_and_exit(1);
// 	i = 0;
// 	while (session->input[i])
// 	{
// 		i = skip_whitespace(session->input);
// 		if (is_special(session->input))
// 			handle_spesial();
// 		else
// 			handle_no_spesial();
// 	}
// 	return (token);
// }

void	promt(t_session *session)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)  // Get the current working directory
	{
		session->len_input = ft_strlen(cwd);
		printf("%s%s%s$ %s", GREEN, BOLD, cwd, RESET); // Green prompt with current directory
	}
	else
	{
		session->len_input = ft_strlen("minishell$ ");
		printf("%s%sminishell$ %s", GREEN, BOLD, RESET); // Green prompt with minishell$ 
	}
	session->input = readline(""); // Read from stdin, returns allocated string or NULL
	if (session->input && *session->input)
		add_history(session->input);
	if (!session->input)
		error_msg("Something wrong");
}
