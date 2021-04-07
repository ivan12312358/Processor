#include "../Libraries/Onegin.h"


/**
 * @brief Calls other fuctions
 *
 * @param argc Number of arguments
 * @param argv Sorting and sorted file
 *	
 * @return Program exit status
 */


char* f_open(char** f_asm, int* sym_cnt, int* str_cnt){

	FILE* asm_file = fopen(*f_asm, "r+");

	assert(asm_file);

	fseek(asm_file, 0, SEEK_END);
	*sym_cnt = ftell(asm_file);
	rewind(asm_file);
	
	char *symbols = (char*)calloc(*sym_cnt, sizeof(char));

	fread(symbols, sizeof(char), *sym_cnt, asm_file);

	for(int i = 0; i < *sym_cnt; i++){
		if(symbols[i] == ' ' ||  symbols[i] == '\n'){
			symbols[i] = '\0';
			(*str_cnt)++;
		}
	}

	fclose(asm_file);

	return symbols;
}

void txt_str(str* string, unsigned char* symbols, unsigned sym_cnt)
{
    unsigned pointer = 0, j = 0;

    for(unsigned i = 0; i < sym_cnt; i++)
    {
        if(symbols[i] == '\0')
        {
            string[j].len = strlen((char*)symbols + pointer);
            string[j].point = symbols + pointer;
            pointer = i + 1;
            j++;
        }
    }
}
 

int str_compare(const void* str_1, const void* str_2)
{
    str *str1 = (str*)str_1, *str2 = (str*)str_2;

    unsigned i = 0, j = 0;
    int f_sym = 0, s_sym = 0;
    while(i < str1->len && j < str2->len)
    {
        if(!isalpha((unsigned char)str1->point[i]))
        {
            i++;
            continue;
        }
        else 
            f_sym = tolower((unsigned char)str1->point[i]);
        

        if(!isalpha((unsigned char)str2->point[j]))
        {
            j++;
            continue;
        }
        else 
            s_sym = tolower((unsigned char)str2->point[j]);

        if(f_sym > s_sym)
            return 1;
        else if(f_sym == s_sym)
        {
            i++;
            j++;
        }
        else
            return -1;
    } 

    return str1->len - str2->len;
}


int rv_str_compare(const void* str_1, const void* str_2)
{
    str* str1 = (str*)str_1;
    str* str2 = (str*)str_2;

    unsigned i = str1->len, j = str2->len;
    int f_sym = 0, s_sym = 0;
    while(i > 0 && j > 0)
    {
        if(!isalpha((unsigned char)str1->point[i]))
        {
            i--;
            continue;
        }
        else
            f_sym = tolower(str1->point[i]);


        if(!isalpha(str2->point[j]))
        {
            j--;
            continue;
        }
        else
            s_sym = tolower(str2->point[j]);        
        
   
        if(f_sym > s_sym)
            return 1;
        else if(f_sym == s_sym)
        {
            i--;
            j--;
        }
        else
            return -1;
    }

    return str1->len - str2->len;
}


void my_qsort(str* strings, unsigned long start, unsigned long end, int comparator(const void*, const void*))
{
    unsigned long pivot = (start + end) / 2;
    str pivot_str = strings[pivot];

    unsigned long l = start, r = end;

    while (l <= r)
    {
        while (comparator(&pivot_str, strings + l) >=  1) 
            l++;
        while (comparator(&pivot_str, strings + r) <= -1)
            r--;
        if (l <= r)
        {
            swap(strings + l, strings + r);
            l++;
            r--;
        }
    }

    if (start < r)
        my_qsort(strings, start, r, comparator);
    if (l < end)
        my_qsort(strings, l, end, comparator);
}


void swap (str* str1, str* str2)
{
    assert(str1 && str2);

    str temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}


void text_print(str* string, unsigned str_cnt, const char* mode, char* file_name)
{
    FILE* file = fopen(file_name, mode);
    assert(file != NULL);
    for(unsigned i = 0; i < str_cnt; i++)
    {    
    	for(unsigned j = 0; j < string[i].len; j++)
        {    
            if(isalpha(string[i].point[j]))
            {
                fprintf(file, "%s\n", string[i].point + j);
                break;
            }
        }
    }

    fprintf(file, "\n\n\n\n\n");
    fclose(file);
}


void print_Onegin(unsigned char* symbols, unsigned sym_cnt, char* file_name)
{
    FILE* file = fopen(file_name, "a+");
    assert(file != NULL);
 
    for(unsigned i = 0; i < sym_cnt; i++)
    {  
        if(symbols[i] == '\0')
            fprintf(file, "%s\n", symbols + i + 1);
        if(i == 0)
            fprintf(file, "%s\n", symbols + i);
    }
    
    fclose(file);
}