#ifndef SHELL_H
#define SHELL_H

/*******Header files*******/
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h> /* for strtok*/
#include <unistd.h> /* for fork*/
#include <sys/stat.h> /* stat the function*/
#include <sys/types.h> /* for type pid*/
#include <fcntl.h> /* for open files*/
#include <errors.h>
#include <signal.h>
#include <limits.h>

/*******Structures*******/

/**
 * struct details- struct for the program data
 * @prog_name: the name of the executable
 * @input_line: pointer to the input read for _getline
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: number of executed commands
 * @file_descriptor: file descriptor to the input of commands
 * @tokens: pointer to array of tokenized input
 * @env: copy of environment
 * @alias_list: array of pointers with aliases
*/
typedef struct details
{
char *prog_name;
char *input_line;
char *command_name;
int exec_counter;
int file_descriptor;
char **tokens;
char **env;
char **alias_list;
} program_data;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(program_data *data);
} builtins;

/*======= Prototypes ========*/
int _getline(program_data *data);
int check_logic_ops(char *array_commands[], int i, char array_operators[]);
void expand_variables(program_data *data);
void expand_alias(program_data *data);
int buffer_add(char *buffer, char *str_to_add);
void tokenize(program_data *data);
char *_strtok(char *line, char *delim);
int execute(program_data *data);
int builtins_list(program_data *data);
char **tokenize_path(program_data *data);
int find_program(program_data *data);
void free_array_of_pointers(char **directories);
void free_recurrent_data(program_data *data);
void free_all_data(program_data *data);
int builtin_exit(program_data *data);
int builtin_cd(program_data *data);
int set_work_directory(program_data *data, char *new_dir);
int builtin_help(program_data *data);
int builtin_alias(program_data *data);
int builtin_env(program_data *data);
int builtin_set_env(program_data *data);
int builtin_unset_env(program_data *data);
char *env_get_key(char *name, program_data *data);
int env_set_key(char *key, char *value, program_data *data);
int env_remove_key(char *key, program_data *data);
void print_environ(program_data *data);
int _print(char *string);
int _printe(char *string);
int _print_error(int errorcode, program_data *data);
int str_length(char *string);
char *str_duplicate(char *string);
int str_compare(char *string1, char *string2, int number);
char *str_concat(char *string1, char *string2);
void str_reverse(char *string);
int _atoi(char *s);
void long_to_string(long number, char *string, int base);
int count_characters(char *string, char *character);
int print_alias(program_data *data, char *alias);
char *get_alias(program_data *data, char *alias);
int set_alias(char *alias_string, program_data *data);
#endif
