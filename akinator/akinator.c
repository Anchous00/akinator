#include "../tree.h"
#include <locale.h>

void ask_question( tree_node_t *node );
void add_node( tree_node_t *node );
void quit( void );
void Menu( void );
//TODO свой инпут
//TODO эстетик ебейший
//TODO порноакинатор
//TODO терминал

tree_node_t *root = NULL;

int main( void )
{
    setlocale(LC_ALL, "");
    system("stty iutf8");
    system("rm -rf logs");
    system("mkdir logs");
    log_file_open("log.html");
    LOG(myLOG_DEFAULT, "<pre>");
    LOG(myLOG_DEFAULT, "ебейший квиз");


    root = create_node("Egorka d");
    log_file_open("log.html");
    Menu();


    ON_LOG(log_file_close();
    system("xdg-open log.html");)

    return 0;
}

void Menu( void )
{
    char str[100] = {};
    char c = 0;
    printf("q - quit\n1 - start session\n2 - save db\n3 - load db\n4 - draw tree\n");

    while ((c = (char)getchar()))
    {
        switch (c)
        {
            case 'q':
                quit();
                return;
            case '1':
                ask_question(root);
                break;
            case '2':
                printf("Enter file name\n");
                scanf("%s", str);
                load_tree(&root, str);
                break;
            case '3':
                printf("Enter file name\n");
                scanf("%s", str);
                load_tree(&root, str);
                break;
            case '4':
                tree_draw_graph(root);
                log_file_close();
                system("xdg-open log.html");
                break;
            default:
                break;
        }
        //printf("q - quit\n1 - start session\n2 - save db\n3 - load db\n4 - draw tree\n");
    }

    return;
}

void quit( void )
{
    destroy_node(root);
    ON_LOG(log_file_close();
    system("xdg-open log.html");)

    exit(0);

    return;
}

void ask_question( tree_node_t *node )
{
    char c = 0;

    if (node->right == NULL || node->left == NULL)
    {
        printf("ты загадал %s?\n", node->value);
        while((c = (char)getchar()))
        {
            switch (c)
            {
                case 'y':
                    printf("Вы осеменили %s\n", node->value);
                    Menu();
                    break;
                case 'n':
                    printf("я таких не знаю\nкого ты загадал?\n");
                    add_node(node);
                    Menu();
                default:
                    break;
            }
        }
    }


    printf("%s?\n", node->value);

    while ((c = (char)getchar()))
        switch (c)
        {
            case 'y':
                ask_question(node->right);
                break;
            case 'n':
                ask_question(node->left);
                break;
            default:
                break;
        }

    return;
}

void add_node( tree_node_t *node )
{
    char question[256] = {};
    char answer[256] = {};
    printf("кого ты загадал?\n");
    getchar();
    scanf("%[^\n]", answer);
    printf("что его отличает от %s?\n", node->value);
    getchar();
    scanf("%[^\n]", question);

    link_node(&node->right, answer);
    link_node(&node->left, node->value);
    free(node->value);
    node->value = strdup(question);

    return;
}

