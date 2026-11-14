#include "tree.h"

int main( void )
{
    system("rm -rf logs");
    system("mkdir logs");
    log_file_open("log.html");
    LOG(myLOG_DEFAULT, "<pre>");

    tree_node_t *root = create_node("pisun");
    // link_right_node(root, "zz");
    // link_right_node(root->right, "10");
    //link_left_node(root, "left");
    link_node(&root->right, "left");

    // save_tree(root, "tree.txt");
    // tree_draw_graph(root);
    // destroy_node(root);

//     tree_node_t *root = NULL;
//
//     load_tree(&root, "tree.txt");
//     //save_tree(root, "tree2.txt");
//     //printf("ZZ");
    tree_draw_graph(root);
    destroy_node(root);


    log_file_close();
    system("xdg-open log.html");

    return 0;
}
