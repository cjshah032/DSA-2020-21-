#include "stack.h"

int main(int argc, char* argv[])    //lab assignment
{
    FILE* fptr = fopen(argv[1], "r");
    stack* top = createStack();

    while(!feof(fptr))
    {
        int temp;
        fscanf(fptr, "%d", &temp);
        push(top, temp);
    }

    fclose(fptr);
    fptr = fopen("stack_output.txt", "w");

    while(!isEmpty(top))
    {
        printf("%d\n", peek(top));
        fprintf(fptr, "%d", pop(top));
        fprintf(fptr, "\n");
    }

    fclose(fptr);
    return 0;
}