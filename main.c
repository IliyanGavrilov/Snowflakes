#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * (x))
#endif

FILE* open_file(char *file_name)
{
    FILE *fp;

    fp = fopen(file_name, "r");

    if (fp == NULL)
    {
        perror("Cannot open file\n");
        exit(EXIT_FAILURE);
    }
    return fp;
}

void close_file(FILE *fp)
{
    fclose(fp);
}

int get_lines(FILE *fp)
{
    int lines = 0;
    char c;

    while(!feof(fp))
    {
        c=fgetc(fp);
        if(c == '\n')
        {
            lines++;
        }
    }
    return lines;
}

void clear_Screen()
{
    system("@cls||clear");
}

char snowfall(FILE *fp, int symbol_count, int seconds)
{
    return 0;
}

int main()
{
    char file_name[25];
    int symbol_count;
    int seconds;

    printf("File Name = ");
    gets(file_name);

    FILE *fp = open_file(file_name);

    printf("symbol_count = ");
    scanf("%d", &symbol_count);

    printf("seconds = ");
    scanf("%d", &seconds);
    printf("%d", get_lines(fp));
    //printf("%c\n", snowfall(fp, symbol_count, seconds));

    close_file(fp);

    return 0;
}
