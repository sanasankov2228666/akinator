#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "akinator.h"
#include "dot_generator.h"

void dot_node_gen(node_t* root, FILE* dot_file, size_t* number)
{
    if (root == NULL) return;

    if (root->right == NULL && root->left == NULL)
    {
        fprintf(dot_file, "\tnode%zu [label = \"{parent = %p | data = %s| {<left> YES = %p|<right> NO = %p} }\",",
                *number, root->parent, root->val, root->left, root->right);
        fprintf(dot_file, " fillcolor = \"lightgreen\", style = \"filled\"];\n");
    }

    else
    {
        fprintf(dot_file, "\tnode%zu [label = \"{parent = %p | data = %s| {<left> YES = %p|<right> NO = %p} }\",",
                *number, root->parent, root->val, root->left, root->right);
        fprintf(dot_file, " fillcolor = \"wheat\", style = \"filled\"];\n");
    }

    size_t current_number = (*number)++;
    
    if (root->left != NULL)
    {
        dot_node_gen(root->left, dot_file, number);
    }
    
    if (root->right != NULL)
    {
        dot_node_gen(root->right, dot_file, number);
    }
}

void dot_arrw_gen(node_t* root, FILE* dot_file, size_t* number, size_t parent_number)
{
    if (root == NULL) return;

    size_t current_number = (*number)++;
    
    if (root->left != NULL)
    {
        fprintf(dot_file, "\tnode%zu:<left> -> node%zu;\n", 
                current_number, *number);
        dot_arrw_gen(root->left, dot_file, number, current_number);
    }
    
    if (root->right != NULL)
    {
        fprintf(dot_file, "\tnode%zu:<right> -> node%zu;\n", 
                current_number, *number);
        dot_arrw_gen(root->right, dot_file, number, current_number);
    }
}

err_t dump_generator(tree* data, const char* filename, const char* reason)
{
    char dot_filename[200] = {};
    snprintf(dot_filename, sizeof(dot_filename), "dot/%s.dot", filename);
    
    FILE* dot_file = fopen(dot_filename, "w");
    if (!dot_file)
    {
        printf("Error creating DOT file\n");
        return AK_ERROR;
    }
    
    fprintf(dot_file, "digraph Tree\n{\n");
    fprintf(dot_file, "\tnodesep=0.8;\n");
    fprintf(dot_file, "\tranksep=1;\n");
    fprintf(dot_file, "\tnode [shape=record,style=\"rounded,filled\", fillcolor=lightblue];\n");
    fprintf(dot_file, "\tedge [arrowsize=0.8];\n");
    fprintf(dot_file, "\tsplines=ortho;");
    fprintf(dot_file, "\tfontsize = 24;\n");
    fprintf(dot_file, "\tlabel=\"%s\";\n", reason);
    fprintf(dot_file, "\tlabelloc=t;\n\n");

    size_t node_number = 0;
    if (data->root != NULL)
    {
        dot_node_gen(data->root, dot_file, &node_number);
    }

    size_t arrow_number = 0;
    if (data->root != NULL)
    {
        dot_arrw_gen(data->root, dot_file, &arrow_number, 0);
    }

    fprintf(dot_file, "\n}");
    fclose(dot_file);
    
    char command[400];
    snprintf(command, sizeof(command), "dot -Tpng dot/%s.dot -o png/%s.png", filename, filename);
    
    int result = system(command);
    if (result != 0)
    {
        printf("ERROR generating PNG\n");
        return AK_ERROR;
    }
    
    printf("PNG was generated: %s.png\n", filename);

    html_generator(filename, data);

    return SUCCESS;
}

err_t html_generator(const char* filename, tree* data)
{
    fprintf(data->html_out, "<figure>\n");
    fprintf(data->html_out, "\t<img src=\"png/%s.png\"/>\n", filename);
    fprintf(data->html_out, "</figure>\n");
    fprintf(data->html_out, "<br><br><br><br><br><br>\n");

    return 0;
}

void tree_dump(tree* data, const char* reason)
{
    static int dump_count = 0;
    char filename[40] = {};
    snprintf(filename, sizeof(filename), "tree_dump_%d", dump_count++);
    
    if (dump_generator(data, filename, reason) ) printf("PNG generate failed\n");
}