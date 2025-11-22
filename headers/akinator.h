#ifndef TREE_H_
#define TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE_OBJ 70
#define SIZE_ANS 10

typedef int err_t;

typedef char* tree_t;

enum
{
    SUCCESS = 0,
    AK_ERROR   = 1,
};

//-----------СТРУКТУРЫ-------------

struct node_t
{
    node_t* parent = NULL;
    tree_t val  = 0;
    node_t* right = NULL;
    node_t* left = NULL;
};

struct tree
{
    node_t* root    = NULL;
    size_t size     = 0;
    size_t error    = 0;
    FILE*  html_out = NULL;
};



//-------------------------------------------------------РАБОТА-С-ДЕРЕВОМ-----------------------------------------------------------


node_t* node_creator(tree_t val);

void deleter(node_t* root);

void save_tree(node_t* root, FILE* stream);

//----------------------------------------------------------АКИНАТОР--------------------------------------------------------------------


char* input_str(char* answer, size_t size, const char* question);

err_t load_new(node_t* parent, char* new_val, char* diff);

err_t guesser(tree* data);

err_t tree_adder(node_t* parent, tree_t val, tree_t difference);

err_t defenition_func(node_t* root);

err_t compare_func(node_t* root);

int lr_pos(node_t* node);

struct stk search_way(node_t* root, node_t* node);

node_t* search_leaf(node_t* root, char* object);

void say(const char* str);

#endif