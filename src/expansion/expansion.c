/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:18:00 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/20 10:46:55 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
CASE ''
Meta-characters not interpreted inside single quotes:

	$ (dollar sign) — No variable expansion.
	\ (backslash) — No escaping.
	* (asterisk) — No wildcard expansion.
	? (question mark) — No wildcard expansion.
	[ ] (square brackets) — No pattern matching.
	& (ampersand) — No background process operator.
	| (pipe) — No pipe (cannot send output from one command to another).
	; (semicolon) — No command separator.
	< > (redirection operators) — No input/output redirection.
	( ) (parentheses) — No process grouping.
	{ } (curly braces) — No block grouping.
	' (single quote) — Cannot be directly included (you must escape or close and reopen the quotes).
	" (double quote) — No double quotes inside single quotes.

CASE ""
Meta-characters not interpreted inside double quotes:

	* (asterisk) — No wildcard expansion (e.g., * stays as *).
	? (question mark) — No wildcard expansion (e.g., ? stays as ?).
	[ ] (square brackets) — No pattern matching (e.g., [a-z] stays as [a-z]).
	& (ampersand) — No background process operator.
	| (pipe) — No pipe (cannot send output from one command to another).
	; (semicolon) — No command separator.
	< > (redirection operators) — No input/output redirection.
	{ } (curly braces) — No block grouping.
	' (single quote) — No single quote inside double quotes unless escaped (\').
	
Meta-characters still interpreted inside double quotes:

	$ (dollar sign) — Variable expansion (e.g., $USER).
	\ (backslash) — Escape characters (e.g., \" to include a double quote inside double quotes).
	" (double quote) — If escaped with a backslash, it can be included inside double quotes.
	( ) (parentheses) — Command substitution (e.g., $(command)).
	\n (newline) — Interpreted as a newline when using \n inside double quotes.

*/