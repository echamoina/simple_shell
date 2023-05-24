#include "shell.h"

/**
 * print_alias - prints the value of an alias or all aliases
 * @data: pointer to the program's data struct
 * @alias_name: name of the alias to print, or NULL to print all aliases
 *
 * Return: zero if successful, non-zero otherwise
 */
int print_alias(program_data *data, char *alias_name)
{
	int i, j, alias_length;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		/*Calculate the length of the alias name (if specified)*/
		alias_length = str_length(alias_name);
		/*Iterate through the list of aliases*/
		for (i = 0; data->alias_list[i]; i++)
		{
			/*Check if the alias name matches (if specified)*/
			if (!alias_name || (str_compare(data->alias_list[i], alias_name, alias_length)
				&&	data->alias_list[i][alias_length] == '='))
			{
				/*Extract the alias name and value from the alias string*/
				for (j = 0; data->alias_list[i][j]; j++)
				{
					buffer[j] = data->alias_list[i][j];
					if (data->alias_list[i][j] == '=')
						break;
				}
			Continuation:

				/*Add quotes around the value and add to the buffer*/
				buffer[j + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, data->alias_list[i] + j + 1);
				buffer_add(buffer, "'\n");
				/*Print the alias value with quotes*/
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias - returns the value of an alias
 * @data: pointer to the program's data struct
 * @alias_name: name of the alias to retrieve
 *
 * Return: pointer to the value of the alias, or NULL if not found
 */
char *get_alias(program_data *data, char *alias_name)
{
	int i, alias_length;

	/*Validate the arguments*/
	if (alias_name == NULL || data->alias_list == NULL)
		return (NULL);

	/*Calculate the length of the alias name*/
	alias_length = str_length(alias_name);

	/*Iterate through the list of aliases*/
	for (i = 0; data->alias_list[i]; i++)
	{
		/*Check if the alias name matches*/
		if (str_compare(alias_name, data->alias_list[i], alias_length) &&
			data->alias_list[i][alias_length] == '=')
		{
			/*Return the value of the alias*/
			return (data->alias_list[i] + alias_length + 1);
		}
	}

	/*Alias not found, return NULL*/
	return (NULL);
}

/**
 * set_alias - adds or updates an alias
 * @alias_string: string containing the name and value of the alias to set
 * @data: pointer to the program's data struct
 *
 * Return: zero if successful, non-zero otherwise
 */
int set_alias(char *alias_string, program_data *data)
{
	int i, j;
	char buffer[250] = {'0'}, *temp = NULL;

	/*Validate the arguments*/
	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);

	/*Extract the alias name from the alias string*/
	for (i = 0; alias_string[i]; i++)
	{
		if (alias_string[i] != '=')
			buffer[i] = alias_string[i];
		else
		{
			/*Check if the alias value is another alias*/
			temp = get_alias(data, alias_string + i + 1);
			break;
		}
	}

	/*Iterate through the list of aliases*/
	for (j = 0; data->alias_list[j]; j++)
	{
		/*Check if the alias name matches*/
		if (str_compare(buffer, data->alias_list[j], i) &&
			data->alias_list[j][i] == '=')
		{
			/*Alias already exists, free its oldvalue and update it with the new value*/
			free(data->alias_list[j]);
			break;
		}
	}

	/*Add the new alias*/
	if (temp)
	{
		/*Alias value is another alias, construct the new alias string*/
		buffer_add(buffer, "=");
		buffer_add(buffer, temp);
		data->alias_list[j] = str_duplicate(buffer);
	}
	else
	{
		/*Alias value is not another alias, use the provided alias string*/
		data->alias_list[j] = str_duplicate(alias_string);
	}

	return (0);
}
