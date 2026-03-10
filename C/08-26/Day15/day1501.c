#include <stdio.h>

int main() {
    char input;
    printf("Enter your choice: ");
    scanf("%c", &input);
    switch (input)
    {
    case 'a':
    case 'A':
    case 'b':
    case 'B':
    case 'd':
    case 'D':
        printf("Ooooops,try again\n");
        break;
    
    case 'c':
    case 'C':
        printf("Bingo~you are right!\n");
        break;
    
    default:
        printf("Invalid input\n");
        break;
    }
    return 0;
}