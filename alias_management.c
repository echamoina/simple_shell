#include "shell.h"
#include <stdio.h>
#include <string.h>

typedef struct {
    char* name;
    char* value;
} alias;

alias alias_list[50];
int num_aliases = 0;

int print_alias(program_data *data, char* alias) {
    int i;

    if (alias == NULL) {
        // Print all aliases
        for (i = 0; i < num_aliases; i++) {
            printf("%s='%s'\n", alias_list[i].name, alias_list[i].value);
        }
    } else {
        // Print specific alias
        for (i = 0; i < num_aliases; i++) {
            if (strcmp(alias, alias_list[i].name) == 0) {
                printf("%s='%s'\n", alias_list[i].name, alias_list[i].value);
                return 0;
            }
        }

        // Alias not found
        printf("Alias not found\n");
        return 1;
    }

    return 0;
}

typedef struct {
    char* name;
    char* value;
} alias;

alias alias_list[50];
int num_aliases = 0;

char* get_alias(program_data *data, char* name) {
    int i;

    for (i = 0; i < num_aliases; i++) {
        if (strcmp(name, alias_list[i].name) == 0) {
            return alias_list[i].value;
        }
    }

    return NULL;
}

typedef struct {
    char* name;
    char* value;
} alias;

alias alias_list[50];
int num_aliases = 0;

int set_alias(char* alias_string, program_data* data) {
    int i;
    char* name = strtok(alias_string, "=");
    char* value = strtok(NULL, "=");

    if (name == NULL || value == NULL) {
        printf("Invalid alias format\n");
        return 1;
    }

    for (i = 0; i < num_aliases; i++) {
        if (strcmp(name, alias_list[i].name) == 0) {
            // Alias already exists, overwrite its value
            free(alias_list[i].value);
            alias_list[i].value = strdup(value);
            return 0;
        }
    }

    // Alias does not exist, add it to the list
    alias_list[num_aliases].name = strdup(name);
    alias_list[num_aliases].value = strdup(value);
    num_aliases++;

    return 0;
}
