#include "akinator.h"
#include "dot_generator.h"
#include "interface.h"

//!функция открытия программы
err_t open_program(tree* data)
{
    int choose = 1;

    while(choose)
    {
        input_interface_func(&choose);

        switch (choose)
        {
        case 0:
            ;
            break;

        case 1:
        
            printf("\n===================AKINATOR====================\n");
            guesser(data);
            printf("\n===================AKINATOR====================\n");
        
            break;
                
        case 2:
            
            printf("\n===================CHECK=TREE====================\n");
            tree_dump(data, "your tree now");
            printf("\n===================CHECK=TREE====================\n");

            break;
        
        case 3:
            
            printf("\n===================DEFENITION====================\n");
            defenition_func(data->root);
            printf("\n===================DEFENITION====================\n");

            break;

        case 4:
            
            printf("\n=====================COMPARE=====================\n");
            compare_func(data->root);
            printf("\n=====================COMPARE=====================\n");

            break;

        default:

            printf("\nvariant doesnt exist\n");
            say("variant doesnt exist");
            break;
        }
    }    

    return SUCCESS;
}

//!функция для ввода в интерфейсе
err_t input_interface_func(int* choose)
{
    printf("Choose program\n");
    printf("1 - akinator 2 - see tree 3 - defenition 4 - compare\n0 - exit  \n");
    printf("anwser:");

    int check = scanf("%d", choose);
    while(check == 0)
    {
        while (getchar() != '\n');
        printf("try again\n");
        printf("anwser:");
        check = scanf("%d", choose);
    }

    return SUCCESS;
}