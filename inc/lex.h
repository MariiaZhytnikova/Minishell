/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:02:13 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/12 11:05:30 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Utils
void	error_msg(char *msg);
size_t	ft_strlen(const char *str);

// Parsing
void	promt(t_session *session);
TokenType	lexical_analyzer(t_session *session);