#ifndef TREE_H
#define TREE_H

#include <string.h>
#include <ctype.h>
#include "logger.h"
#include "utils.h"

typedef char* tree_elem_t;
#define tree_spec "s"

struct tree_node_t
{
    tree_elem_t value;
    tree_node_t *left, *right;
};

void link_node   ( tree_node_t **node, tree_elem_t value);
void destroy_node( tree_node_t *node                    );
tree_node_t* create_node( tree_elem_t value );

void tree_draw_graph( tree_node_t *root                           );
bool draw_node      ( tree_node_t *node, FILE *graph, size_t rank );

void save_tree( tree_node_t *root, const char *filename );
void save_node( tree_node_t *node, FILE *file           );

void load_tree( tree_node_t **root, const char *filename );
void load_node( tree_node_t **node, char **buffer        );


#endif
