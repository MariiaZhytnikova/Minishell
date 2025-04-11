/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:17:22 by ekashirs          #+#    #+#             */
/*   Updated: 2025/04/11 14:06:37 by ekashirs         ###   ########.fr       */
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

# define ERR_MALLOC "Memory allocation failed"
# define ERR_DUP "dup2 function has failed"
# define ERR_CLOSE "close function has failed"
# define ERR_EXECVE "execve function has failed"
# define ERR_SPLIT "ft_split function has failed"
# define ERR_GETCWD "pwd: error retrieving current directory: getcwd: cannot access parent directories"

# define ERR_MANY_ARGS ": too many arguments provided" // If a built-in command like exit or cd receives more arguments than expected. (bash: cd: too many arguments)
# define ERR_ENV_NOT_FOUND ": unbound variable" // (bash: UNSET_VAR: unbound variable)
# define ERR_EXIT_USAGE "exit: numeric argument required" // VAR="hello" exit $VAR (bash: exit: hello: numeric argument required)
# define ERR_REDIR_SYNTAX "Syntax error: Unexpected token after redirection" // E.g., echo hello > without specifying a file.
# define ERR_REDIR_PERM "Redirection error: Permission denied" // If attempting to redirect to a file without proper permissions.
# define ERR_SIGNAL "Failed to handle signal" // If sigaction() or related functions fail.



#endif