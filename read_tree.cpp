#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include "read_tree.h"
#include "dot_generator.h"


err_t read_tree(tree* data)
{
    FILE* stream = fopen("tree_data.txt", "r");
    if (!stream)
    {
        printf("stream = NULL\n");
        return AK_ERROR;
    }
    
    char* buffer = NULL;
    file_read(stream, &buffer);
    char* buffer_copy = buffer;
    
    data->root = read_note(&buffer, NULL);

    free(buffer_copy);
    fclose(stream);

    return SUCCESS;
}

node_t* read_note(char** cur_pose_ptr, node_t* parent)
{
    char* cur_pose = *cur_pose_ptr;

    if (cur_pose == NULL) return NULL;

    while (*cur_pose == ' ') cur_pose++;

    if (*cur_pose == '(')
    {
        cur_pose++;

        while (*cur_pose != '"' && *cur_pose != '\0') cur_pose++;
        if (*cur_pose == '\0') return NULL;
        
        cur_pose++;

        char* value_start = cur_pose;
        
        while (*cur_pose != '"' && *cur_pose != '\0') cur_pose++;
        if (*cur_pose == '\0') return NULL;
        
        *cur_pose = '\0';
        node_t* node = node_creator(value_start);
        node->parent = parent;

        printf("str = %s\n", value_start );

        cur_pose++;
        
        *cur_pose_ptr = cur_pose;

        node->left  = read_note(cur_pose_ptr, node);
        node->right = read_note(cur_pose_ptr, node);

        cur_pose = *cur_pose_ptr;

        if (*cur_pose == ')') cur_pose++;
        else printf("unrecognize format\n");

        *cur_pose_ptr = cur_pose;
        
        return node;
    }

    else if (strncmp(cur_pose, "nill", 4) == 0)
    {
        cur_pose += 4;
        
        while (*cur_pose == ' ') cur_pose++;

        *cur_pose_ptr = cur_pose;

        return NULL;
    }

    printf("unrecognize format\n");

    return NULL; 
}

//!количетсво символов
long int size_file(FILE* stream)
{
    if (stream == NULL)
    {
        printf("error in size_file stream adres\n");
        return 0;
    }

    struct stat file = {};
    int descriptor = fileno(stream);
    fstat(descriptor, &file);
    
    return file.st_size;
}

//!чтение в один большой массив
size_t file_read(FILE* stream, char** buffer)
{
    long int number = size_file(stream);
    *buffer = (char*) calloc ((size_t)(number+1), sizeof(**buffer));

    if (*buffer == NULL)
    {
        printf("error in file read\n");
        return 0;
    }

    size_t check = fread(*buffer, sizeof(char), (size_t)number, stream);
    if ((long int)check != number)
    {
        printf("error in fread\n");
        return 0;
    }

    return (size_t)number;
}