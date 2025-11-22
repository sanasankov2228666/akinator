#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "akinator.h"
#include "dot_generator.h"
#include "read_tree.h"
#include "interface.h"
#include "stack1.h"

typedef node_t* type;

int main(void)
{
    tree data = {};

    data.html_out = fopen("html_dump.html", "w");
    if (data.html_out == NULL)
    {
        printf("file open error\n");
        return 1;
    }
    
    if (read_tree(&data)) return 1;

    printf("================START===================\n\n");

    printf("this is program for guessing objects choose variant\n\n");
    say("this is program for guessing objects choose variant");

    open_program(&data);

    printf("=================END====================\n\n");

    FILE* stream_out = fopen("tree_data.txt", "w");
    if (stream_out == NULL)
    {
        printf("file open error\n");
        return 1;
    }

    save_tree(data.root, stream_out);

    fclose(stream_out);
    deleter(data.root);

    return 0;
}

//!функция поздания узла
node_t* node_creator(tree_t val)
{
    node_t* node = (node_t*) calloc (1, sizeof(node_t));

    if (node == NULL)
    {
        printf("node = NULL\n");
        return NULL;
    }

    node->val = strdup(val);
    if (node->val == NULL) 
    {
        printf(" node val = NULL, STRDUP ERROR\n");
        free(node);

        return NULL;
    }

    return node;
}

//!функция добавления неугаданного элемента
err_t tree_adder(node_t* parent, tree_t val, tree_t difference)
{
    tree_t old_val = parent->val;
    
    parent->val = strdup(difference);
    if (parent->val == NULL)
    {
        printf("error strdup\n");
        return AK_ERROR;
    }

    parent->left  = node_creator(val);
    parent->right = node_creator(old_val);
    parent->left->parent = parent;
    parent->right->parent = parent;

    if (parent->left == NULL || parent->right == NULL)
    {
        printf("problems with node create\n");
        return AK_ERROR;
    }

    free(old_val);

    return SUCCESS;
}

//!функция угадыватель
err_t guesser(tree* data)
{
    node_t* current_node = data->root;
    char anwsear[SIZE_ANS] = {};

    getchar();
    while(current_node != NULL)
    {
        input_str(anwsear, SIZE_ANS, current_node->val);
        
        if (strcasecmp(anwsear, "yes") == 0 )
        {
            if (current_node->left == NULL && current_node->right == NULL)
            {
                printf("guessed\n");
                say("guessed");

                return SUCCESS;
            }

            current_node = current_node->left;
        }
        
        else if (strcasecmp(anwsear, "no") == 0 )
        {
            if (current_node ->left == NULL && current_node->right == NULL)
            {
                char* new_val = (char*) calloc(SIZE_OBJ, sizeof(char));
                char* diff    = (char*) calloc(SIZE_OBJ, sizeof(char));
                if (new_val == NULL || diff == NULL )
                {
                    printf("zero pointer after calloc\n");
                    return AK_ERROR;
                }

                load_new(current_node, new_val, diff );

                return SUCCESS;
            }

            current_node = current_node->right;
        }
    }

    return SUCCESS;
}

//!функция для определений
err_t defenition_func(node_t* root)
{   
    getchar();
    char object[SIZE_OBJ] = {}; 
    input_str(object, SIZE_OBJ, "write object for definition");

    node_t* def_node = search_leaf(root, object);
    if (def_node == NULL) return SUCCESS;

    printf("defenition for %s:\n", def_node->val); 
    do
    {
        if (def_node->parent->left == def_node)
        {
            def_node = def_node->parent;
            size_t len = strlen(def_node->val);
            printf("%.*s, ", (int)len - 1, def_node->val);
            
        }
        else
        {
            def_node = def_node->parent;
            size_t len = strlen(def_node->val);
            printf("not %.*s, ", (int)len - 1, def_node->val);
        }

    }
    while (def_node != root);

    return SUCCESS;
}

err_t compare_func(node_t* root)
{
    getchar();
    char object_1[SIZE_OBJ] = {};
    char object_2[SIZE_OBJ] = {}; 

    input_str(object_1, SIZE_OBJ, "write first object for definition");
    input_str(object_2, SIZE_OBJ, "write second object for definition");

    node_t* node1 = search_leaf(root, object_1);
    if (node1 == NULL) return SUCCESS;

    node_t* node2 = search_leaf(root, object_2);
    if (node2 == NULL) return SUCCESS;

    stk way_1 = search_way(root, node1);
    stk way_2 = search_way(root, node2);

    size_t s1 = way_1.size - 1;
    size_t s2 = way_2.size - 1;

    printf("\nsimmilar:\n");

    while(stack_mass(&way_1, s1) == stack_mass(&way_2, s2 ) && lr_pos(stack_mass(&way_1, s1 )) == lr_pos(stack_mass(&way_2, s2 )))
    {
        if (lr_pos(stack_mass(&way_1, s1)) == 0) printf("they both are - %s\n", stack_mass(&way_1, s1)->parent->val);
        else printf("they both arent - %s\n", stack_mass(&way_1, s1)->parent->val);
        s1--;
        s2--;
    }

    printf("\ndifferent:\n");

    while(1)
    {
        if (lr_pos(stack_mass(&way_1, s1)) == 0) printf("%s - %s\n", node1->val, stack_mass(&way_1, s1)->parent->val);
        else printf("%s - not %s\n", node1->val, stack_mass(&way_1, s1)->parent->val);

        if(s1 == 0) break;
        s1--;
    }

    while(1)
    {
        if (lr_pos(stack_mass(&way_2, s2)) == 0) printf("%s - %s\n", node2->val, stack_mass(&way_2, s2)->parent->val);
        else printf("%s - not %s\n", node2->val, stack_mass(&way_2, s2)->parent->val);

        if(s2 == 0) break;
        s2--;
    }

    stack_deleter(&way_1);
    stack_deleter(&way_2);

    return SUCCESS;
}

// err_t compare_func(node_t* root)
// {
//     getchar();
//     char object_1[SIZE_OBJ] = {};
//     char object_2[SIZE_OBJ] = {}; 

//     input_str(object_1, SIZE_OBJ, "write first object for definition");
//     input_str(object_2, SIZE_OBJ, "write second object for definition");

//     node_t* node1 = search_leaf(root, object_1);
//     if (node1 == NULL) return SUCCESS;

//     node_t* node2 = search_leaf(root, object_2);
//     if (node2 == NULL) return SUCCESS;

//     stk way_1 = search_way(root, node1);
//     stk way_2 = search_way(root, node2);

//     node_t* pop1 = stack_pop(&way_1);
//     node_t* pop2 = stack_pop(&way_2);

//     node_t* pop1 = stack_mass(&way1, )
//     node_t* pop2 = stack_pop(&way_2);

//     printf("\nsimmilar:\n");

//     while(pop1 == pop2 && lr_pos(pop1) == lr_pos(pop2))
//     {
//         if (lr_pos(pop1) == 0) printf("they both are - %s\n", pop1->parent->val);
//         else printf("they both arent - %s\n", pop1->parent->val);
//         pop1 = stack_pop(&way_1);
//         pop2 = stack_pop(&way_2);
//     }

//     printf("\ndifferent:\n");

//     while(1)
//     {
//         if (lr_pos(pop1) == 0) printf("%s - %s\n", node1->val, pop1->parent->val);
//         else printf("%s - not %s\n", node1->val, pop1->parent->val);

//         if(way_1.size == 0) break;
//         pop1 = stack_pop(&way_1);
//     }

//     while(1)
//     {
//         if (lr_pos(pop2) == 0) printf("%s - %s\n", node2->val, pop2->parent->val);
//         else printf("%s - not %s\n", node2->val, pop2->parent->val);

//         if(way_2.size == 0) break;
//         pop2 = stack_pop(&way_2);
//     }

//     stack_deleter(&way_1);
//     stack_deleter(&way_2);

//     return SUCCESS;
// }

struct stk search_way(node_t* root, node_t* node)
{
    if(root == NULL || node == NULL)
    {
        printf("root or node = null\n");
    }

    stk way = {};
    stack_creator(&way, 100);

    while(node != root)
    {
        stack_push(&way, node);
        node = node->parent;
    }

    return way;
}

int lr_pos(node_t* node)
{
    if(node == NULL) return -1;

    if (node->parent->left == node) return 0;

    else if (node->parent->right == node) return 1;

    return -1;
}

node_t* search_leaf(node_t* leaf, char* object)
{
    stk data = {};
    stack_creator(&data, 100);

    stack_push(&data, leaf);

    node_t* current = NULL;
    int check = 1;

    while(check != 0 && data.size != 0)
    {
        current = stack_pop(&data);

        if (current->left == NULL && current->right == NULL)
            check = strcasecmp(current->val, object);

        if (current->left != NULL)
            stack_push(&data, current->left);
            
        if (current->right != NULL)
            stack_push(&data, current->right); 
    }

    if (check != 0)
    {
        printf("Object %s doesent exist in tree\n", object);
        stack_deleter(&data);
        return NULL;
    }

    stack_deleter(&data);
    return current;
}

//!функция ввода
char* input_str(char* answer, size_t size, const char* question)
{   
    printf("%s\n", question);
    say(question);

    printf("answer: ");
    
    if (fgets(answer, (int) size, stdin) == NULL)
    {
        printf("error, fgets\n");
        return NULL;
    }

    size_t len = strlen(answer);
    if (len > 0 && answer[len-1] == '\n')
        answer[len-1] = '\0';

    return answer;
}

//!функция загрузки нового элмента
err_t load_new(node_t* parent, char* new_val, char* diff)
{   
    input_str(new_val, SIZE_OBJ, "didnt guess, what is it?");

    printf("what difference between %s and %s,(write without no)\ncontinue: he/she/it ...\n", new_val, parent->val);
    input_str(diff, SIZE_OBJ, " ");

    diff[strlen(diff)] = '?';

    tree_adder(parent, new_val, diff);

    free(new_val);
    free(diff);
    
    return SUCCESS;
}

//!функция вывода в файл
void save_tree(node_t* root, FILE* stream)
{
    if (root == NULL)
    {
        fprintf(stream, "nill ");
        return;
    }

    fprintf(stream, "( \"%s\" ", root->val);

    save_tree(root->left, stream);
    save_tree(root->right, stream);

    fprintf(stream, ")");

    return;
}

void say(const char* str)
{
    char command[500] = {};
    
    snprintf(command, sizeof(command), 
         "powershell -Command \"Add-Type -AssemblyName System.Speech; "
         "$speech = New-Object System.Speech.Synthesis.SpeechSynthesizer; "
         "$speech.SelectVoice('Microsoft David Desktop'); "
         "$speech.Speak('%s')\"", str);
    
    system(command);
}

//!функция удаления дерева
void deleter(node_t* root)
{   
    if (root == NULL) return;
    
    deleter(root->left);
    deleter(root->right);
    
    free(root->val);
    free(root);

}