#include "shell.h"

/**
 * builtins_list - searches for a match and executes the associated builtin function
 * @data: a struct containing program data
 *
 * Return: returns the return value of the executed function if there is a match,
 * otherwise returns -1.
 **/
int builtins_list(program_data *data)
{
    int i; /*declare an integer variable called i*/

    /*define an array of builtins structures called options which contains the names of built-in commands and their associated functions.*/
    builtins options[] = {
        {"exit", builtin_exit}, /*exit command with associated function*/
        {"help", builtin_help}, /*help command with associated function*/
        {"cd", builtin_cd}, /*cd command with associated function*/
        {"alias", builtin_alias}, /*alias command with associated function*/
        {"env", builtin_env}, /*env command with associated function*/
        {"setenv", builtin_set_env}, /*setenv command with associated function*/
        {"unsetenv", builtin_unset_env}, /*unsetenv command with associated function*/
        {NULL, NULL} /*end of list*/
    };

    /*iterate through the builtins list*/
    for (i = 0; options[i].builtin != NULL; i++)
    {
        /*check if the given command matches a builtin*/
        if (str_compare(options[i].builtin, data->command_name, 0))
        {
            /*execute the function associatedwith the matching builtin and return its return value*/
            return (options[i].function(data));
        }
    }

    /*if there is no match, return -1*/
    return (-1);
}
