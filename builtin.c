#include "shell.h"

/**
 * builtin_env - prints the environment or modifies a variable
 * @data: pointer to the program's data struct
 *
 * Return: zero if successful, non-zero otherwise
 */
int builtin_env(program_data *data)
{
	int i;
	char var_name[50] = {'\0'};
	char *var_copy = NULL;

	/*Check if there are arguments*/
	if (data->tokens[1] == NULL)
	{
		/*No arguments, print the environment*/
		print_environment(data);
	}
	else
	{
		/*Arguments provided, check if they are of the form NAME=VALUE*/
		for (i = 0; data->tokens[1][i]; i++)
		{
			if (data->tokens[1][i] == '=')
			{
				/*Extract the variable name*/
				var_copy = str_duplicate(env_get_variable_name(var_name, data));
				if (var_copy != NULL)
				{
					/*Variable exists, temporarily set its value and print the environment*/
					env_set_key(var_name, data->tokens[1] + i + 1, data);
					print_environment(data);
					if (env_get_key(var_name, data) == NULL)
					{
						/*Variable not found in environment, print the variable*/
						_print(data->tokens[1]);
						_print("\n");
					}
					else
					{
						/*Restore the variable's old value*/
						env_set_key(var_name, var_copy, data);
						free(var_copy);
					}
					return (0);
				}
				/*Variable not found in environment, print error message*/
				errno = 2;
				perror(data->command_name);
				errno = 127;
			}
			/*Extract the variable name*/
			var_name[i] = data->tokens[1][i];
		}
		/*No '=' found, print error message*/
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}
	return (0);
}

/**
 * builtin_set_env - sets an environment variable
 * @data: pointer to the program's data struct
 *
 * Return: zero if successful, non-zero otherwise
 */
int builtin_set_env(program_data *data)
{
	/*Check if there are enough arguments*/
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		/*Too many arguments, print error message*/
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	/*Set the environment variable*/
	env_set_key(data->tokens[1], data->tokens[2], data);
	return (0);
}

/**
 * builtin_unset_env - removes an environment variable
 * @data: pointer to the program's data struct
 *
 * Return: zero if successful, non-zero otherwise
 */
int builtin_unset_env(program_data *data)
{
	/*Check if there is exactly one argument*/
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		/*Too many arguments, print error message*/
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	/*Remove the environment variable*/
	env_remove_key(data->tokens[1], data);
	return (0);
}
