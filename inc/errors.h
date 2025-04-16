/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:17:22 by ekashirs          #+#    #+#             */
/*   Updated: 2025/04/16 15:20:05 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "minishell.h"

# define ERR_USAGE "Usage: ./minishell"
# define ERR_EXCL "Handling of special characters like ';', '\\', '{}', '()', '[]', '&' is not supported"
# define ERR_QUOTES "Quotes are not closed correctly"
# define ERR_SYNT_END "syntax error: unexpected end of file"
# define ERR_EOF_HEREDOC "warning: here-document delimited by end-of-file"

# define ERR_BASH "minishell: "
# define ERR_ENV "env: "
# define ERR_EXPORT "export: "
# define ERR_CD "minishell: cd: "
# define ERR_PIPE "Pipe creation failed"
# define ERR_FORK "Fork failed"
# define ERR_CMD ": command not found"
# define ERR_PERM ": Permission denied"
# define ERR_NOFILE ": No such file or directory"
# define ERR_NUM ": numeric argument required"
# define ERR_IDEN ": not a valid identifier"
# define ERR_CRASH " error in : "
# define ERR_DIR "cannot open directory "

# define ERR_MALLOC "Memory allocation failed"
# define ERR_DUP "dup2 function has failed"
# define ERR_CLOSE "close function has failed"
# define ERR_EXECVE "execve function has failed"
# define ERR_SPLIT "ft_split function has failed"
# define ERR_GETCWD "pwd: error retrieving current directory: getcwd: cannot access parent directories"

# define ERR_MANY_ARGS ": too many arguments" // If a built-in command like exit or cd receives more arguments than expected. (bash: cd: too many arguments)
# define ERR_EXIT_USAGE "exit: numeric argument required"
# define ERR_SYNTAX "syntax error near unexpected token "
# define ERR_REDIR " ambiguous redirect"
# define ERR_ISADIR ": Is a directory"


#endif