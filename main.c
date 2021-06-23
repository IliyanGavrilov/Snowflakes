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
    file_name[strlen(file_name)-1] = '\0';
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

void free_grid(char **arr, int lines)
{
    for(int i=0;i<lines;i++)
    {
        free(arr[i]);
    }
    free(arr);
}

int get_lines(FILE *fp)
{
    int lines = 0;
    char c;

    while(!feof(fp))
    {
        c = fgetc(fp);
        if(c == '\n')
        {
            lines++;
        }
    }

    return lines;
}

void init_grid(char **arr, int symbol_count, int lines)
{
    for(int i = 0; i < lines; i++)
    {
        for(int j = 0; j < symbol_count; j++)
        {
            arr[i][j] = ' ';
        }
    }
}

void init_ground(char *arr, int symbol_count)
{
    for(int i = 0; i < symbol_count; i++)
    {
        arr[i] = ' ';
    }
}

char **create_grid(FILE *fp, int symbol_count, int lines)
{
    char **arr = (char **)malloc(lines * sizeof(char *));
    for(int i = 0; i<lines; i++)
    {
         arr[i] = (char *)malloc(symbol_count * sizeof(char));
    }
    init_grid(arr, symbol_count, lines);

    fseek(fp, 0, SEEK_SET);

    int row = 0, col = 0;
    char c;

    while(!feof(fp))
    {
        c = fgetc(fp);
        if(c == ' ' || c == '*')
        {
            if(col + 1 < symbol_count)
            {
                arr[row][col++] = c;
            }
        }
        else if(c == '\n')
        {
            row++;
            col = 0;
            if(row >= lines)
            {
                break;
            }
        }
    }

    return arr;
}

void print_grid(char **arr, int arr_rows, char *ground, int symbol_count, int lines, int seconds)
{
    int end = 0;
    if(lines + 1 >= seconds) {
        end = lines - seconds + 2;
    }

    for(int i = lines; i >= end; i--)
    {
        if(i < arr_rows)
        {
            for(int j = 0; j < symbol_count; j++)
            {
                printf("%c", arr[i][j]);
            }
        }

        printf("\n");
    }
    if(lines + 2 >= seconds)
    {
        for(int i = 0; i < symbol_count; i++)
        {
            printf("%c", ground[i]);
        }

        for(int i = 0; i < symbol_count; i++)
        {
            if(arr[end][i] == '*')
            {
                ground[i] = '*';
            }
        }
    }

}

void clear_screen()
{
    system("@cls||clear");
}

char snowfall(FILE *fp, int symbol_count, int seconds)
{
    int lines = get_lines(fp);

    char **arr = create_grid(fp, symbol_count, lines);
    char ground[symbol_count];
    init_ground(ground, symbol_count);

    clear_screen();
    for(int i = 0; i < lines + seconds - 1; i++)
    {
        print_grid(arr, lines, ground, symbol_count, i, seconds);
        sleep(1);
        if(i != lines + seconds - 1)
        {
            clear_screen();
        }
    }
    free_grid(arr, lines);
    return 0;
}

int main()
{
    char file_name[25];
    int symbol_count;
    int seconds;

    printf("File Name = ");
    fgets(file_name,25,stdin);

    FILE *fp = open_file(file_name);

    printf("symbol_count = ");
    scanf("%d", &symbol_count);

    printf("seconds = ");
    scanf("%d", &seconds);

    printf("%c\n", snowfall(fp, symbol_count, seconds));

    close_file(fp);

    return 0;
}
