#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct
{
    char **tokens;
    int token_count;
} Line;

typedef struct
{
    bool mutability;
    char *type;
    char *name;
    char *value;
} Variable;

typedef struct
{
    char **lines;
    int count;
    int capacity;

    char **globals;
    int global_count;
    int global_capacity;

    int tmp_count;
    int str_count;
} Output_Code;

void init_output_code(Output_Code *oc)
{
    oc->lines = NULL;
    oc->count = 0;
    oc->capacity = 0;
}

int next_register = 1;

int allocate_register() {
    return next_register++;
}

int reset_register(){
    return next_register = 1;
}

int current_merge_id = 0;

int current_if_id = 0;
int next_check_label = 0;

void parse_line(const char *buffer, Line *line)
{
    char temp[1024]; // temporary buffer for building current token
    int temp_idx = 0;
    bool in_quotes = false;
    char quote_type = 0;

    for (int i = 0; buffer[i] != '\0'; i++)
    {
        char c = buffer[i];

        // Handle quote characters (start/end of string literals)
        if ((c == '"' || c == '\'') && (i == 0 || buffer[i - 1] != '\\'))
        {
            if (!in_quotes)
            {
                in_quotes = true;
                quote_type = c;
            }
            else if (c == quote_type)
            {
                in_quotes = false;
            }
            else
            {
                temp[temp_idx++] = c;
            }
        }
        // Handle parentheses as separate tokens when outside quotes
        else if (!in_quotes && (c == '(' || c == ')'))
        {
            if (temp_idx > 0)
            {
                temp[temp_idx] = '\0';
                line->tokens = realloc(line->tokens, (line->token_count + 1) * sizeof(char *));
                line->tokens[line->token_count++] = strdup(temp);
                temp_idx = 0;
            }
            line->tokens = realloc(line->tokens, (line->token_count + 1) * sizeof(char *));
            char bracket[2] = {c, '\0'};
            line->tokens[line->token_count++] = strdup(bracket);
        }
        // Whitespace delimiters (outside quotes)
        else if (!in_quotes && (c == ' ' || c == '\t' || c == '\n' || c == '\r'))
        {
            if (temp_idx > 0)
            {
                temp[temp_idx] = '\0';
                line->tokens = realloc(line->tokens, (line->token_count + 1) * sizeof(char *));
                line->tokens[line->token_count++] = strdup(temp);
                temp_idx = 0;
            }
        }
        else
        {
            temp[temp_idx++] = c;
        }
    }

    // Add the last token if any remains
    if (temp_idx > 0)
    {
        temp[temp_idx] = '\0';
        line->tokens = realloc(line->tokens, (line->token_count + 1) * sizeof(char *));
        line->tokens[line->token_count++] = strdup(temp);
    }
}

void add_variable(Variable **vars, int *count, bool mut, char *type, char *name, char *val)
{
    *vars = realloc(*vars, (*count + 1) * sizeof(Variable));

    Variable *v = &((*vars)[*count]);
    v->mutability = mut;
    v->type = strdup(type);
    v->name = strdup(name);
    v->value = strdup(val);

    (*count)++;
}

void add_line_to_code(Output_Code *oc, const char *text)
{
    if (oc->count >= oc->capacity)
    {
        oc->capacity = (oc->capacity == 0) ? 10 : oc->capacity * 2;
        oc->lines = realloc(oc->lines, oc->capacity * sizeof(char *));
    }

    oc->lines[oc->count] = strdup(text);
    oc->count++;
}

int main(){
    FILE *fptr = fopen("code001.bug", "r");
    if (!fptr){
        perror("Error opening input file 'code.bg'");
        return -1;
    }

    Line *lines = NULL;
    int line_count = 0;
    char buffer[1024];

    Output_Code myCode;
    myCode.lines = NULL;
    myCode.count = 0;
    myCode.capacity = 0;
    myCode.globals = NULL;
    myCode.global_count = 0;
    myCode.global_capacity = 0;
    myCode.tmp_count = 0;
    myCode.str_count = 0;

    while (fgets(buffer, sizeof(buffer), fptr))
    {
        // Remove comments (everything after //)
        char *comment_ptr = strstr(buffer, "//");
        if (comment_ptr)
            *comment_ptr = '\0';

        // Remove semicolon if present (simple statement terminator)
        char *semi = strchr(buffer, ';');
        if (semi)
            *semi = '\0';

        // Skip empty lines
        if (strspn(buffer, " \t\n\r\f\v") == strlen(buffer))
            continue;

        // Allocate new Line structure
        lines = realloc(lines, (line_count + 1) * sizeof(Line));
        lines[line_count].tokens = NULL;
        lines[line_count].token_count = 0;

        parse_line(buffer, &lines[line_count]);
        line_count++;
    }

    for (int i = 0; i < line_count; i++)
    {
        printf("Line %d: ", i);
        for (int j = 0; j < lines[i].token_count; j++)
        {
            printf("[%s] ", lines[i].tokens[j]);
        }
        printf("\n");
    }
}