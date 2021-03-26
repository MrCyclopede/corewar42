# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    clean.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amamy <amamy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/22 23:51:03 by nivergne          #+#    #+#              #
#    Updated: 2020/07/02 15:10:33 by amamy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

clean:
	@make --no-print-directory -C libft clean
	@/bin/rm -fr obj

fclean: clean
	@make --no-print-directory -C libft fclean
	@echo "$(CYAN)$(BOLD)COREWAR			$(BLUE)bin$(END)$(RED)		[delete]$(END)"
	@/bin/rm -f $(ASM) $(VM)