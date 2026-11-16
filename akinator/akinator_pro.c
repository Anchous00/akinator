#include "akinator.h"

//TODO эстетик ебейший
//TODO порноакинатор


tree_node_t *root = NULL;
tree_node_t *current = root;
extern enum APP_STATE STATE;
Font font = {};
Texture2D background = {};
char buffer[MAX_STR_LEN] = {};
int char_cnt = 0;

int main( void )
{
    root = create_node("Egorka d");
    current = root;
    SetTraceLogLevel(LOG_NONE);
    InitWindow(WINDOW_W, WINDOW_H, "АКИНАТОР В ПОПЕ ВИБРАТОР");
    font = LoadCustomFont("akinator/arial.ttf");

    background = LoadTexture("akinator/STARIY_BOG.png");

    SetTargetFPS(60);
    InitButtons();
    STATE = MENU;
    button_t *pressed_button = NULL;

    while (!WindowShouldClose())
    {
        pressed_button = GetPressedButton();
        //printf("%f \n", GetFrameTime());


        if (pressed_button != NULL)
        {
            printf("pressed %s\n", pressed_button->str);
            pressed_button->func();
        }
        BeginDrawing();
        DrawTexture(background, 0, 0, WHITE);

        DrawApp();

        EndDrawing();
    }

    quit();

    return 0;
}

void start_session( void )
{
    current = root;
    STATE = GAME;

    return;
}

void return_to_menu( void )
{
    STATE = MENU;

    return;
}

void quit( void )
{
    CloseWindow();
    destroy_node(root);
    ON_LOG(log_file_close();
    system("xdg-open log.html");)

    exit(0);
}

void yes( void )
{
    if (current->left == NULL && current->right == NULL)
        STATE = ANSWER;

    if (STATE == GAME)
        current = current->right;
    else if (STATE == ANSWER)
    {
        STATE = RETURN_TO_MENU;
        reset_buffer();
    }

    return;
}

void no( void )
{
    if (current->left == NULL && current->right == NULL)
        STATE = ANSWER;

    if (STATE == GAME)
        current = current->left;
    else if (STATE == ANSWER)
    {
        STATE = ADD_NODE_ANSWER;
        reset_buffer();
    }

    return;
}

void save_db( void )
{
    reset_buffer();
    STATE = SAVING_DB;

    return;
}

void load_db( void )
{
    reset_buffer();
    STATE = LOADING_DB;

    return;
}
