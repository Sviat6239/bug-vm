#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct{
    char **tokens;
    int token_count;
} Line;

int stach[1024];
int sp = -1;
int ip = 0;

void parse_line(const char *buffer, Line *line){

}

int main(){
    FILE *fptr = fopen("bytecode001.bin", "r");
    if (!fptr)
    {
        perror("Error opening input file 'code.as'");
        return -1;
    }

    Line *lines = NULL;
    int line_count = 0;
    char buffer[1024];
}