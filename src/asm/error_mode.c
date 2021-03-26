/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 02:29:58 by amamy             #+#    #+#             */
/*   Updated: 2020/08/03 21:08:45 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include "ft_printf.h"

/*
** ==================== read_errors_in_line ====================
** Go though tokens one by one and displays matching text for error.
*/

static void		read_errors_in_line
	(t_token *token, char error_table[TOKEN_ERRORS_NUMBER][80])
{
	while (token)
	{
		if (token->error)
		{
			ft_printf("\t- %s : |", error_table[token->error]);
			ft_putstrn(&token->code_line->line[token->position], token->length);
			ft_printf("|\n");
		}
		token = token->next;
	}
}

/*
** ==================== loading_error_table ====================
** Loads an array of known errors that are needed to display
** good information on errors.
*/

static void		loading_error_table(char error_table[TOKEN_ERRORS_NUMBER][80])
{
	ft_bzero((void*)error_table, sizeof(char[TOKEN_ERRORS_NUMBER][80]));
	ft_strcpy(error_table[UNKNOWN_TOKEN], "Unknow token");
	ft_strcpy(error_table[MEMORY_ALLOCATION_ERROR], "Could not allocate \
memory");
	ft_strcpy(error_table[BAD_OP_CODE], "Unrecognized instruction");
	ft_strcpy(error_table[WRONG_PARAMETER_NUMBER], "Wrong number of \
parameters for this instruction type");
	ft_strcpy(error_table[INVALID_REGISTER], "Invalid register number, only \
exist r1 to r16");
	ft_strcpy(error_table[WRONG_ARGUMENT_TYPE], "This instruction does not \
take this type of parameter");
	ft_strcpy(error_table[NOT_ARGUMENT_TYPE], "This is not a valid argument \
for any instruction");
	ft_strcpy(error_table[MISSING_SEPARATOR], "Parameter given to instruction \
must be separated with a coma ','");
	ft_strcpy(error_table[MISS_PLACED_SEPARATOR], "Coma ',' are only used to \
separate instruction arguments");
	ft_strcpy(error_table[LABEL_REDEFINITION], "LABEL_REDEFINITON : you \
cannot define same label twice");
	ft_strcpy(error_table[TOKEN_AFTER_OP], "TOKEN_AFTER_OP : Unecessary \
token found after operation");
	ft_strcpy(error_table[UNDECLARED_LABEL_CALL], "Use of undeclared label");
}

/*
** ==================== error_mode ====================
** Receives the first node of t_code_line list (aka first
** line of code). Reads lines one by one. If the line contains
** errors, displays it and go to next line.
*/

void			error_mode(t_code_line **c_line)
{
	t_code_line		*tmp;
	char			error_table[TOKEN_ERRORS_NUMBER][80];

	tmp = (*c_line);
	loading_error_table(error_table);
	ft_printf("%s\n", "=============== ERROR(S) FOUND(S) ===============");
	while (tmp)
	{
		if (tmp->errors)
		{
			ft_printf("\n%s\n", "=========");
			ft_printf("line %d : ", tmp->nb_line);
			ft_printf("|%s|\n\n", tmp->line);
			if (tmp->errors == LINE_ERROR_LEXICAL)
				ft_printf("Lexical error(s) :\n");
			else if (tmp->errors == LINE_ERROR_SYNTAX)
				ft_printf("Syntax error(s) :\n");
			else
				ft_printf("Lexical and Syntax errors :\n");
			read_errors_in_line(tmp->token, error_table);
		}
		tmp = tmp->next;
	}
	ft_printf("\n%s\n", "============ END OF ERROR DISPLAY ============\n");
}
