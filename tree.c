#include "tree.h"

tree_node_t* create_node( tree_elem_t value )
{
    tree_node_t *node = (tree_node_t*)calloc(1, sizeof(tree_node_t));
    if (node == NULL)
        return node;
    node->value = strdup(value);
    node->left  = NULL;
    node->right = NULL;

    return node;
}

void link_node( tree_node_t **node, tree_elem_t value)
{
    *node = create_node(value);

    return;
}

__attribute__((no_sanitize_address))
void destroy_node( tree_node_t *node )
{
    if (node == NULL)
        return;
    destroy_node(node->left);
    destroy_node(node->right);

    free(node->value);
    free(node);
    node->value = (tree_elem_t)0;
    node = NULL;

    return;
}

void save_tree( tree_node_t *root, const char *filename )
{
    FILE* save_file = fopen(filename, "w");
    if (save_file == NULL)
    {
        printf("ZZZZZOVV");
        return;
    }
    save_node(root, save_file);

    if (fclose(save_file)) printf("can't close save file\n");
    return;
}

void save_node( tree_node_t *node, FILE *file )
{
    if (node == NULL)
    {
        fprintf(file, "(nil)");
        return;
    }
    fprintf(file, "(%" tree_spec, node->value);
    save_node(node->left, file);
    save_node(node->right, file);
    fprintf(file, ")");

    return;
}

void load_tree( tree_node_t **root, const char *file_name )
{
    FILE *source_file = fopen(file_name, "r");
    if (source_file == NULL)
    {
        printf("can't open file\n");
        return;
    }

    char *buffer = NULL;
    input_text_from_file(source_file, &buffer, file_name);

    // printf("%s\n", buffer);
    // sscanf(buffer, "(%s", buffer);
    // printf("%s\n", buffer);
    char *buffer_tmp = buffer;

    destroy_node(*root);
    load_node(root, &buffer_tmp);

    free(buffer);

    return;
}

void load_node(tree_node_t **node, char **buffer)
{
    char str_tmp[256] = {0};

    (*buffer)++;

    size_t i = 0;
    while (**buffer != ')' && **buffer != '(' && **buffer != '\0')
    {
        str_tmp[i] = **buffer;
        i++;
        (*buffer)++;
    }
    str_tmp[i] = '\0';
    if (strcmp(str_tmp, "nil") == 0)
    {
        //printf("node: %s\n", "nil");
        *node = NULL;
        (*buffer)++;
        return;
    }

    *node = create_node(str_tmp);
    // printf("node: %s\n", str_tmp);
    // printf("left is:\n");
    load_node(&(*node)->left,  buffer);
    //printf("right is:\n");
    load_node(&(*node)->right, buffer);

    (*buffer)++;

    return;
}

void tree_draw_graph( tree_node_t *root )
{
    time_t t = time(NULL);
    struct tm *time_info = localtime(&t);

    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);  // или timespec_get(&ts, TIME_UTC)

    char time_str[64] = {};
    strftime(time_str, sizeof(time_str), "%d%m%Y%H%M%S", time_info);

    char file_path[256] = {};
    snprintf(file_path, sizeof(file_path), "logs/%s%ld.gv", time_str, ts.tv_nsec);

    FILE *graph = fopen(file_path, "w");
    if (graph == NULL)
    {
        printf("can't open graph file\n");
        return;
    }


    fprintf(graph,  "digraph Tree{\n"
                    "bgcolor=\"transparent\";\n"
                    "rankdir=TB;\n"
                    "node [shape=record, fontname=\"Courier\"];\n"
                    "edge [color=\"#4d9ae2\"];\n"
                    "splines=\"ortho\"\n"
            );

    draw_node(root, graph, 0);


    fprintf(graph, "}\n");

    if (fclose(graph))
        printf("can't close graph file\n");

    char dot_cmd[1024] = {};
    snprintf(dot_cmd, sizeof(dot_cmd), "dot -Tsvg logs/%s%ld.gv -o logs/%s%ld.svg", time_str, ts.tv_nsec, time_str, ts.tv_nsec);

    system(dot_cmd);

    LOG(myLOG_DEFAULT, "<img src=\"logs/%s%ld.svg\" style=\"width: 100%%; height: auto;\">", time_str, ts.tv_nsec);

    return;
}

bool draw_node( tree_node_t *node, FILE *graph, size_t rank )
{
    if (graph == NULL || node == NULL)
        return 0;
    fprintf(graph, "%llu [label=\"{ value = %" tree_spec" | address = %llu | {<left> left = %llu | <right> right = %llu}}\", style=\"rounded,filled\", fillcolor=\"#4ce372\", rank=%zu];\n", (unsigned long long)node, node->value, (unsigned long long)node, (unsigned long long)node->left, (unsigned long long)node->right, rank);

    if (draw_node(node->right, graph, rank + 1))
        fprintf(graph, "%llu:right->%llu;\n", (unsigned long long)node, (unsigned long long)node->right);
    if (draw_node(node->left, graph, rank + 1))
        fprintf(graph, "%llu:left->%llu;\n", (unsigned long long)node, (unsigned long long)node->left);

    return 1;
}
