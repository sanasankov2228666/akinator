#ifndef READ_TREE_H_

#include <stdio.h>
#include "akinator.h"


err_t read_tree(tree* data);

node_t* read_note(char** cur_pose_ptr, node_t* parent);

long int size_file(FILE* stream);

size_t file_read(FILE* stream, char** buffer);

#endif