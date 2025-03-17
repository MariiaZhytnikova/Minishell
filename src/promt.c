/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:32:49 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/17 16:07:54 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	if_single_balanced(const char *str) 
{
	int	i;
	int	quote_count;

	i = 0;
	quote_count = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			quote_count++;
		i++;
	}
	return (quote_count % 2 == 0);
}

static int	if_double_balanced(const char *str) 
{
	int	i;
	int	quote_count;

	i = 0;
	quote_count = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			quote_count++;
		i++;
	}
	return (quote_count % 2 == 0);
}

static int	exclusion_check(char *str) // if c == ';' ||  c == '\' || or Unclosed quote-> error EXCLUSION
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (!if_single_balanced(str))
		return (error_msg(ERR_QUOTES), 1);
	if (!if_double_balanced(str))
		return (error_msg(ERR_QUOTES), 1);
	printf("check excl\n");
	while (str[i])
	{
		if (str[i] == ';' || str[i] == '\\')
			return (error_msg(ERR_EXCL), 1);
		else if (str[i] == '(' || str[i] == ')')
			return (error_msg(ERR_EXCL), 1);
		else if (str[i] == '{' || str[i] == '}')
			return (error_msg(ERR_EXCL), 1);
		else if (str[i] == '[' || str[i] == ']')
			return (error_msg(ERR_EXCL), 1);
		else if (str[i] == '&' && str[i + 1] == '&')
			i++;
		else if (str[i] == '&' && str[i + 1] != '&')
			return (error_msg(ERR_EXCL), 1);
		i++;
	}
	return (0);
}

// echo $USER | ls -l $HOME && echo 'Path is $PWD'
bool	delimiter_wrong_pos(char **token, int token_num)
{
	if ((ft_strncmp(token[0], "|", ft_strlen(token[0])) == 0))
		return (error_msg("syntax error near unexpected token `|'"), true);
	if ((ft_strncmp(token[0], "||", ft_strlen(token[0])) == 0))
		return (error_msg("syntax error near unexpected token `||'"), true);
	if ((ft_strncmp(token[0], "&&", ft_strlen(token[0])) == 0))
		return (error_msg("syntax error near unexpected token `&&'"), true);
	if ((ft_strncmp(token[token_num - 1], "<<", ft_strlen(token[0])) == 0))
		return (error_msg("syntax error near unexpected token `newline'"), true);
	if ((ft_strncmp(token[token_num - 1], "<", ft_strlen(token[0])) == 0))
		return (error_msg("syntax error near unexpected token `newline'"), true);
	if ((ft_strncmp(token[token_num - 1], ">>", ft_strlen(token[0])) == 0))
		return (error_msg("syntax error near unexpected token `newline'"), true);
	if ((ft_strncmp(token[token_num - 1], ">", ft_strlen(token[0])) == 0))
		return (error_msg("syntax error near unexpected token `newline'"), true);
	return (false);
}

void	here_doc_input(char **token, char *limiter)
{
	char	*line;
	char	*lim;
	char	*new_token;

	lim = ft_strjoin(limiter, "\n");
	while (1)
	{
		line = get_next_line(0);
		if (limiter && ft_strncmp(line, lim, ft_strlen(lim)) == 0)
		{
			free(line);
			break ;
		}
		printf("%s", line);
		free(*token);
		new_token = ft_strjoin(*token, line);
		if (!new_token)
			return (error_msg("Something wrong with Here_doc"));
		free(*token);
		*token = new_token;
		free(line);
		if (!limiter)
			break ;
	}
	if (limiter)
		free (limiter);
		// Delete this token
	free(lim);
	exit(0);
}

void	delimiter_here_doc(t_session *session, char **token, int token_num)
{
	int	i;

	if ((ft_strncmp(token[token_num], "|", ft_strlen(token[token_num])) == 0)
		|| (ft_strncmp(token[token_num], "||", ft_strlen(token[token_num])) == 0)
		|| (ft_strncmp(token[token_num], "&&", ft_strlen(token[token_num])) == 0))
	{
		here_doc_input(&token[token_num], NULL); // finish input with \n
		// add to token input to command and split to arguments
	}
	i = 0;
	while (token[i])
	{
		if (ft_strncmp(token[i], "<<", ft_strlen(token[0])) && token[i + 1])
		{
			here_doc_input(&token[i], token[i + 1]);
			// add to token input to argument without split
		}
		i++;
	}
}

// static int	is_delimiter (t_session *session, char **token)
// {
// 	while (token[i])
// 	{
// 		if (ft_strncmp(token[i], "|", ft_strlen(token[i])) == 0)
// 			session->tokens[0]->type = PIPE;
// 		else if (session->input[i] == '||')
// 			type = AND;
// 		else if (session->input[i] == '&&')
// 			type = AND;
// 		else if (session->input[i] == '>')
// 			type = REDIRECT_OUTPUT;
// 		else if (session->input[i] == '<')
// 			type = REDIRECT_INPUT;
// 		else if (session->input[i] == '>>')
// 			type = REDIRECT_OUTPUT_APPEND;
// 		else if (session->input[i] == '<<')
// 			type = HEREDOC; // not update history
// 		else
// 			type = NONE; // not update history
// 		i++;
// 	}
// 	return (0);
// }

// echo $USER | ls -l $HOME && echo 'Path is $PWD'

void	lexical_analyzer(t_session *session)
{
	int		i;
	int		token_num;
	//char	**token;
	t_list	*token;

	if (exclusion_check(session->input))
		return (error_msg("Something wrong"));
	token_num = word_count(session->input);
	token = NULL;
	split_input(token, session->input, 0);
	if (!token)
		return (error_msg("split_input wrong"));




		
	if (delimiter_wrong_pos(token, token_num) == true)
		return (error_msg("Something wrong"));
	i = 0;
	delimiter_here_doc(session, token, token_num); // ->>>> here_doc with '>'

	
	printf("everything is wrong");
	
	// while (session->input[i])
	// {
	// 	i = skip_whitespace(session->input);
	// 	is_quotes()
	// 	// normal command
	// 	if (is_special(session->input))
	// 		handle_spesial();
	// 	else
	// 		handle_no_spesial();
	// }
}

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