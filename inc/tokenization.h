/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:inc/tokenization.h
/*   Created: 2025/03/17 16:43:38 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/17 16:45:57 by mzhitnik         ###   ########.fr       */
=======
/*   Created: 2025/03/12 11:02:13 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/17 14:05:27 by ekashirs         ###   ########.fr       */
>>>>>>> af99a88 (add some builtin funcs):inc/lex.h
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

<<<<<<< HEAD:inc/tokenization.h
# include "minishell.h"
=======
// Utils
void	error_msg(char *beginning, char *details, char *error);
size_t	ft_strlen(const char *str);
>>>>>>> af99a88 (add some builtin funcs):inc/lex.h

void	promt(t_session *session);
void	lexical_analyzer(t_session *session);



#endif