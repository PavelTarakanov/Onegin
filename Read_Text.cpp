#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <ctype.h>
#include <assert.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include "Read_Text.h"


int main(int argc, char* argv[])
{
    char** text = NULL;
    FILE* input_address = NULL;
    FILE* output_address = NULL;
    struct stat statistics = {};
    char* buffer = NULL;
    int number_of_str = 1;

    if(check_file_founded(argc, argv[0]))
        return 0;

    if (check_file_opening(argv[1], &input_address))
        return 0;
    if (check_file_opening(argv[2], &output_address))
        return 0;

    read_text(input_address, &statistics, &buffer, &text, &number_of_str);

    booble_sort(text, number_of_str, my_strcmp);
    output_text(output_address, text, number_of_str);

    booble_sort(text, number_of_str, my_reverse_strcmp);
    output_text(output_address, text, number_of_str);

    //printf("%d", my_reverse_strcmp("abc\n", "abcd*&%^**\n"));
    booble_sort(text, number_of_str, my_indicator_cmp);
    output_text(output_address, text, number_of_str);

    free(buffer);
    free(text);

    if (check_file_closing(input_address))
        return 0;
    if (check_file_closing(output_address))
        return 0;

    return 0;
}

void read_text(FILE* input_address, struct stat* statistics, char** buffer, char*** text, int* number_of_str)
{
    fstat(fileno(input_address), statistics);

//    printf("%ld\n", statistics.st_size);

    *buffer = (char*) calloc(statistics->st_size, sizeof(char));
    fread(*buffer, sizeof(char), statistics->st_size, input_address);

    /*
    for (int i = 0; i < statistics.st_size; i++)
    {
        putchar(buffer[i]);
    }
    */

    //*number_of_str = str_counter(*buffer);
    *text = (char**) calloc(*number_of_str, sizeof(char*));
    make_indicator_massive(*text, *buffer, number_of_str);
}

void make_indicator_massive(char* text[], char* buffer, int* number_of_str)
{
    assert(text);
    assert(buffer);
    assert(number_of_str);

    char* str_address = NULL;
    int str_number = 0;

    text[str_number] = buffer;
    str_number++;
    str_address = strchr(buffer, '\n');
    assert(str_address);

    while (str_address != NULL)
    {
        if (str_number > *number_of_str)
        {
            *number_of_str = *number_of_str*2;
            text = (char**) realloc((void*) text, *number_of_str * sizeof(char*));
        }
        text[str_number] = str_address+1;
        //printf("%d\n", str_number);
        str_number++;
        str_address = strchr(str_address+1, '\n');
    }
    *number_of_str = str_number;

    return;
}

void booble_sort(char* text[], int number_of_str, int comparison(const char* str_1, const char* str_2))
{
    assert(text);

    char* swp = 0;

    for (int i = 0; i < number_of_str; i++)
        for (int j = 0; j < number_of_str; j++)
        {
            //printf("%d %d\n", i, j);
            if (comparison(text[i], text[j]) < 0)
            {
                swp = text[i];
                text[i] = text[j];
                text[j] = swp;
            }
        }

    return;
}

int my_strcmp(const char* str_1, const char* str_2)
{
    assert(str_1);
    assert(str_2);

    int i = 0;
    int j = 0;

    while (str_1[i] != '\n' && str_2[j] != '\n')
    {
        if (!isalpha(str_1[i]))
        {
            i++;
            continue;
        }
        else if (!isalpha(str_2[j]))
        {
            j++;
            continue;
        }
        else if (tolower(str_1[i]) > tolower(str_2[j]))
        {
            return 1;
        }
        else if(tolower(str_1[i]) < tolower(str_2[j]))
        {
            return -1;
        }

        i++;
        j++;
    }

    return 0;
}

int my_reverse_strcmp(const char* str_1, const char* str_2)
{
    assert(str_1);
    assert(str_2);

    size_t i = 0;
    size_t j = 0;

    while (str_1[i] != '\n')
    {
        i++;
    }

    while (str_2[j] != '\n')
    {
        j++;
    }

    while (i > 0 && j > 0)
    {
        if (!isalpha(str_1[i]))
        {
            i--;
            continue;
        }
        else if (!isalpha(str_2[j]))
        {
            j--;
            continue;
        }
        else if (tolower(str_1[i]) > tolower(str_2[j]))
        {
            return 1;
        }
        else if(tolower(str_1[i]) < tolower(str_2[j]))
        {
            return -1;
        }

        i--;
        j--;
    }

    if (i == 0 && j == 0)
    {
        return 0;
    }
    else if(i == 0)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

int my_indicator_cmp(const char* ind_1, const char* ind_2)
{
    assert(ind_1);
    assert(ind_2);

    return (int) (ind_1 - ind_2);
}

size_t my_strlen(const char* str)
{
    assert(str);

    int i = 0;
    size_t count = 0;
    while (1)
    {
        if (*(str+i) == '\0' || *(str+i) == '\n')
        {
            return count;
        }
        count++;
        i++;
    }
}

void output_text(FILE* output_address, char* text[], int number_of_str)
{
    assert(output_address);
    assert(text);

    for (int i = 0; i < number_of_str; i++)
        for (int j = 0; j < MAX_STR_LENGTH; j++)
        {
            if (text[i][j] != '\n')
                putc(text[i][j], output_address);
            else
            {
                putc('\n', output_address);
                break;
            }
        }

    fprintf(output_address, "\n\n\n\n\n");

    return;
}

int str_counter(char* buffer)
{
    assert(buffer);

    int count = 0;
    int i = 0;

    while (*(buffer+i) != '\0')
    {
        if (*(buffer+i) == '\n')
        {
            count++;
        }

        i++;
    }

    return count;
}
