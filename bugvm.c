#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define OP_PUSH  0x0001 // push value on the stack
#define OP_POP   0x0002 // pop value from the stack
#define OP_ADD   0x0003 // add two last value from the stack
#define OP_SUB   0x0004 // sub two last value from the stack
#define OP_MUL   0x0005 // mul two last value from the stack
#define OP_DIV   0x0006 // div two last value from the stack
#define OP_PRINT 0x0007 // print the value from the stack
#define OP_INPUT 0x0008 // read value to rhe stack
#define OP_HALT  0xffff // halt the programm

typedef struct{
    char **tokens;
    int token_count;
} Line;

#define STACK_SIZE (1024 * 64)
int stack[STACK_SIZE];
int sp = -1;
int ip = 0;

void push(int value) {
    if (sp >= STACK_SIZE - 1) {
        printf("Error: stack overflow!\n");
        exit(1);
    }
    stack[++sp] = value;
}

int pop(){
    if (sp < 0){
        printf("Error: stack is empty!");
        exit(1);
    }
    return stack[sp--];
}

int o_add(int a, int b){
    return a + b;
}

int o_sub(int a, int b){
    return a - b;
}

int o_mul(int a, int b){
    return a * b;
} 

int o_div(int a, int b){
    if (b == 0){
        printf("Error: cant divide by zero!");
        exit(1);
    }
    return a / b;
}

int o_cmp(int a, int b){
    return 1;
}

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

int main(){
    FILE *fptr = fopen("bytecode001.bbin", "r");
    if (!fptr)
    {
        perror("Error opening input file 'code.as'");
        return -1;
    }

    Line *lines = NULL;
    int line_count = 0;
    char buffer[1024];

    // ==================== READING AND TOKENIZING PHASE ====================
    printf("=== Reading and tokenizing code.as ===\n");
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

    // ==================== DEBUG: PRINT ALL TOKENS ====================
    printf("\n=== Tokenized lines ===\n");
    for (int i = 0; i < line_count; i++)
    {
        printf("Line %d: ", i);
        for (int j = 0; j < lines[i].token_count; j++)
        {
            printf("[%s] ", lines[i].tokens[j]);
        }
        printf("\n");
    }

    char *value;

    // ==================== EXECUTE LOOP ====================
    printf("\n=== Execution ===\n");
    for (ip = 0; ip < line_count; ip++) {
        if (lines[ip].token_count == 0) continue;

        char *cmd = lines[ip].tokens[0];
        int opcode = (int)strtol(cmd, NULL, 0);

        switch (opcode) {
            case OP_PUSH: {
                if (lines[ip].token_count < 2) {
                    printf("Error: OP_PUSH requires an argument!\n");
                    return 1;
                }
                int val = (int)strtol(lines[ip].tokens[1], NULL, 0);
                push(val);
                break;
            }
            case OP_POP:
                pop();
                break;

            case OP_ADD: {
                int b = pop();
                int a = pop();
                push(o_add(a, b));
                break;
            }
            case OP_SUB: {
                int b = pop();
                int a = pop();
                push(o_sub(a, b));
                break;
            }
            case OP_MUL: {
                int b = pop();
                int a = pop();
                push(o_mul(a, b));
                break;
            }
            case OP_DIV: {
                int b = pop();
                int a = pop();
                push(o_div(a, b));
                break;
            }
            case OP_PRINT:
                if (sp < 0) {
                    printf("Error: Stack is empty, nothing to print!\n");
                } else {
                    printf("%d\n", stack[sp]);
                }
                break;

            case OP_INPUT: {
                int input_val;
                printf("");
                if (scanf("%d", &input_val) != 1) {
                    printf("Error: invalid input!\n");
                    return 1;
                }
                push(input_val);
                break;
            }
            case OP_HALT:
                printf("Program halted successfully.\n");
                ip = line_count;
                break;

            default:
                printf("Unknown instruction opcode: 0x%04X (string: %s)\n", opcode, cmd);
                return 1;
        }
        
        if (opcode == OP_HALT) break;
    }

    // ==================== CLEANUP PHASE ====================
    // Free all allocated memory to prevent leaks
    for (int i = 0; i < line_count; i++) {
        for (int j = 0; j < lines[i].token_count; j++) {
            free(lines[i].tokens[j]);
        }
        free(lines[i].tokens);
    }
    free(lines);
    fclose(fptr);

    return 0;

}