#ifndef READ_TEXT_H
#define READ_TEXT_H

const int NUMBER_OF_FILES = 2;
const int MAX_STR_LENGTH = 200;

int check_file_founded(int argc, const char *input_address);
int check_file_opening(const char *input_address, FILE** file_ptr);
int check_file_closing(FILE* input_address);

void make_indicator_massive(char* text[], char* buffer, int* number_of_str);

int str_counter(char* buffer);

size_t my_strlen(const char* str);
int my_strcmp(const char* str_1, const char* str_2);
void booble_sort(char* text[], int number_of_str, int comparison(const char* str_1, const char* str_2));
int my_reverse_strcmp(const char* str_1, const char* str_2);
int my_indicator_cmp(const char* ind_1, const char* ind_2);

void output_text(FILE* input_address, char* text[], int number_of_str);

void read_text(FILE* input_address, struct stat* statistics, char** buffer, char*** text, int* number_of_str);
#endif //READ_TEXT_H
