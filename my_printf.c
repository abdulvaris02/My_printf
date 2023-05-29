#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>     
#include <stdlib.h>
#include <string.h>    
#define hexNums "0123456789abcdef"             
int set_char(char c){
    write(1, &c, 1);
    return 1;
}
int set_str(char* soz)
{
   int count = 0;
   for(int i = 0; soz[i] != '\0'; i++)
   {
       count += set_char(soz[i]);
   }
   return count;
}

char* set_dec(int raqam)
{
   char * lst = malloc(sizeof(char)*100);
   int count = 0;
   int minus = 0;
   if(raqam == 0) return "0";
   if(raqam < 0){
       minus++;
       raqam = raqam * (-1);
   }
   while(raqam > 0){
       lst[count++] = raqam % 10 + '0';
       raqam = raqam / 10;
   }
   int j = 0;
   char* answer = malloc(sizeof(char)*count);
   if(minus){ answer[0] = '-';
     }
   for(int i = count - 1; i >= 0; i--, j++)
   {
       answer[j] = lst[i];
   }
   return answer;
}

char* set_octal(int raqam)
{
   char * lst = malloc(sizeof(char)*100);
   int count = 0;
   int minus = 0;
   if(raqam == 0) return "0";
   if(raqam < 0){
       minus++;
       raqam = raqam * (-1);
   }

   while(raqam > 0){
       lst[count++] = raqam % 8 + '0';
       raqam = raqam / 8;
   }
   int j = 0;
   char* answer = malloc(sizeof(char)*count);
   if(minus){ answer[0] = '-';
     }
   for(int i = count - 1; i >= 0; i--, j++)
   {
       answer[j] = lst[i];
   }
   return answer;
}

char* set_unsigndec(int raqam)
{
   char * lst = malloc(sizeof(char)*100);
   int count = 0, minus = 0;
   if(raqam == 0) return "0";
   if(raqam < 0){
       minus++;
       raqam = raqam * (-1);
   }

   while(raqam != 0){
       lst[count++] = raqam % 10 + '0';
       raqam = raqam / 10;
   }
   int j = 0;
   char* answer = malloc(sizeof(char)*count);

   for(int i = count - 1; i >= 0; i--, j++)
   {
       answer[j] = lst[i];
   }
   
   return answer;  
}   

int set_xdec(long pointer, int numXdec){
    int ret = 0;
    int isNegative = 0;
    char buf[32] = {0};
    int i = 30;
    while(pointer && i ){
        pointer /= numXdec;
        buf[i] = hexNums[pointer % numXdec];
        --i;
    }
    if(isNegative) {
        set_str("-");
        ret++;
    }
    set_str(&buf[i+1]);
    ret += (int)strlen(&buf[i+1]);
    return ret;
}

int my_printf(const char*  param_1, ...)
 {
    va_list lst_of_params;  
    char *str, character; 
    int counter = 0, digits = 0;
    intptr_t pointer;
    va_start(lst_of_params, param_1);

    for(int i = 0; param_1[i] != '\0'; i++)
    {
       if(param_1[i] == '%')
       {   
           i++;
           if(param_1[i] == 'u')
           {
               digits = va_arg(lst_of_params, unsigned int);
               str = set_unsigndec(digits);
               counter += set_str(str);
           }
           
           else if(param_1[i] == 'x')
           {
               digits = va_arg(lst_of_params, unsigned int);
               counter += set_xdec(digits ,16);
               
           }
           else if(param_1[i] == 's')
           {
               str = va_arg(lst_of_params, char*);
               counter += set_str(str);
           }
           else if(param_1[i] == 'c')
            {
               character = va_arg(lst_of_params, int);
               counter += set_char(character);           
            }
            else if(param_1[i] == 'p')
            {
               pointer = va_arg(lst_of_params, intptr_t);
                set_str("0x");
                counter+= 2;
                counter += set_xdec(pointer, 16);
            }
            else if(param_1[i] == 'd')
            {
                digits = va_arg(lst_of_params, int);
                str = set_dec(digits);
                counter += set_str(str);
            }
            else if(param_1[i] == 'o')
            {
                digits = va_arg(lst_of_params, unsigned int);
                str = set_octal(digits);
                counter += set_str(str);

            }
            else
            {
                counter += set_char('%');
            }
       }
       else if(param_1[i] != '%')
       { 
           counter += set_char(param_1[i]);       
       }
    }
    va_end(lst_of_params);
    return counter;

 } 

/*int main(){
    void* t = malloc(12);
    int j = my_printf("%p\n", t);
    printf("%d\n", j);
    return 0;
}*/
