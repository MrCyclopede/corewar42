/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 01:52:25 by rcourtoi          #+#    #+#             */
/*   Updated: 2020/07/26 06:33:04 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H
# include <stdint.h>
# include "op.h"
# include "libft.h"
# include "ft_printf.h"

typedef struct			s_player
{
	int				in_use;
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	int				player_code;
	unsigned int	champion_size;
	char			champion[CHAMP_MAX_SIZE + 1];
}						t_player;

typedef	struct			s_event
{
	int		instruction_size;
	char	op_code;
	char	encoding_byte;
	int		og_args[3];
	int		args[3];
}						t_event;

typedef struct			s_props
{
	char	*name;
	int		cost;
	int		has_encoding_byte;
	int		direct_size;
	int		args_type[3];
	int		nb_args;
}						t_props;

typedef struct			s_process
{
	int					execute_in;
	int					parent;
	int					id;
	int					reg[REG_NUMBER + 1];
	int					pc;
	int					last_alive;
	char				carry;
	int					schedule_index;
	t_event				event;
	struct s_process	*next_process;
	struct s_process	*next_event;
}						t_process;

typedef struct			s_vm
{
	int				colored;
	int				step_by_step;
	int				color_arena[MEM_SIZE];
	int				print_scheduler;
	int				verbose;
	int				dump_cycle;
	int				process_max_id;
	int				last_alive;
	unsigned char	arena[MEM_SIZE];
	int				nb_players;
	t_player		players[MAX_PLAYERS];
	int				round_size;
	int				checks_since_decrementation;
	int				nb_round;
	int				lives_this_round;
	int				nb_cycle;
	t_process		*process_list;
}						t_vm;

typedef void			(*t_inst_func)(t_vm*, t_process*);
void					relocate_player(t_vm *vm, int player);
void					print_index_access_arena(char *str, int pos, int i,
						t_process *process);
int						process_highlight_print(t_vm *vm,
							int arena_index, char c);
int						highlight_print(char c, int color);
void					print_args(t_vm *vm,
							t_process *process, t_props *props);
int						find_available_player_slot(t_vm *vm, int wished);
void					sanitize_encoding_byte(char *byte, t_props *props);
int						parse_arguments(t_vm *vm, t_process *process);
void					prepare_arguments(t_process *process, t_props *props);
void					free_and_exit(t_vm *vm, int ret, const char *message);
void					remove_from_schedule(t_vm *vm, t_process *process);
int						get_arguments(t_vm *vm, t_process *process);
t_props					*instructions_properties(int instruction);
void					init_processes(t_vm *vm);
void					game_loop(t_vm *vm);
void					schedule_next_instruction(t_vm *vm, t_process *process);
void					do_cycle(t_vm *vm);
void					dump_arena(t_vm *vm);
int						encoding_byte_null(t_process *process, t_props *props);
int						encoding_byte_valid(t_process *process, t_props *props);
int						get_encoded_size(t_process *process, t_props *props);
void					read_encoding_byte(t_vm *vm,
							t_process *process, t_props *props);
t_arg_type				get_encoding_type(unsigned char encoding_byte, int i);
void					create_process(t_vm *vm,
							int player_number, int pc, t_process *src);
void					set_to_arena(t_vm *vm, int index, int value, int color);
int						get_from_arena(t_vm *vm, int index, int size_of);
void					print_scheduler(t_vm *vm);
void					parse_instruction(t_vm *vm, t_process *process);
void					parsing(t_vm *vm, int argc, char **argv);
void					load_bin_to_arena(t_vm *vm);
void					print_instruction(t_vm *vm, t_process *process);
void					print_process_move(t_vm *vm,
							t_process *process, int old_pc);
void					print_bin_byte(unsigned char byte);
void					set_no_op(t_process *process, int size);
int						registers_valid(t_process *process, t_props *props);
t_arg_type				get_encoding_type(unsigned char encoding_byte, int i);
void					set_encoding_type(char *encoding_byte,
							int i, t_arg_type type);
unsigned int			get_champion_size(char *buffer);
int						magic_number_is_valid(char *buffer);
int						paddings_are_zero(char *buffer);
int						read_file(const char *path, char (*buffer)
							[16 + PROG_NAME_LENGTH
							+ COMMENT_LENGTH + CHAMP_MAX_SIZE + 1]);
void					no_op(t_vm *vm, t_process *process);
void					inst_live(t_vm *vm, t_process *process);
void					inst_ld(t_vm *vm, t_process *process);
void					inst_st(t_vm *vm, t_process *process);
void					inst_add(t_vm *vm, t_process *process);
void					inst_sub(t_vm *vm, t_process *process);
void					inst_and(t_vm *vm, t_process *process);
void					inst_or(t_vm *vm, t_process *process);
void					inst_xor(t_vm *vm, t_process *process);
void					inst_zjmp(t_vm *vm, t_process *process);
void					inst_ldi(t_vm *vm, t_process *process);
void					inst_sti(t_vm *vm, t_process *process);
void					inst_fork(t_vm *vm, t_process *process);
void					inst_lld(t_vm *vm, t_process *process);
void					inst_lldi(t_vm *vm, t_process *process);
void					inst_lfork(t_vm *vm, t_process *process);
void					inst_aff(t_vm *vm, t_process *process);
#endif
