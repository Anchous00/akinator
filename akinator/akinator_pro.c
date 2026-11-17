#include "akinator.h"

//TODO эстетик ебейший
//TODO порноакинатор
//#define VOICE


tree_node_t *root = NULL;
tree_node_t *current = root;
extern enum APP_STATE STATE;
Font font = {};

const int bg_cnt = 3;
Texture2D backgrounds[bg_cnt] = {};
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

    backgrounds[0] = LoadTexture("akinator/STARIY_BOG1.png");
    backgrounds[1] = LoadTexture("akinator/STARIY_BOG2.png");
    backgrounds[2] = LoadTexture("akinator/STARIY_BOG3.png");

    SetTargetFPS(60);
    InitButtons();
    STATE = MENU;
    button_t *pressed_button = NULL;
    background = backgrounds[0];
    while (!WindowShouldClose())
    {
        pressed_button = GetPressedButton();
        //printf("%f \n", GetFrameTime());

        if (pressed_button != NULL)
        {
            pressed_button->func();
        }
        BeginDrawing();
        DrawTextureRec(background, Rectangle{0, 0, WINDOW_W, WINDOW_H}, Vector2{0, 0}, WHITE);
        //DrawTexture(background, 0, 0, WHITE);

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
#ifdef VOICE
speak(current->value);
#endif
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
    log_file_close();
    UnloadTexture(backgrounds[0]);
    UnloadTexture(backgrounds[1]);
    UnloadTexture(backgrounds[2]);
    //system("xdg-open log.html");

    exit(0);
}

void yes( void )
{
    if (current->left == NULL && current->right == NULL)
    {
        STATE = ANSWER;
        background = backgrounds[2];
    }

    if (STATE == GAME)
    {
        select_random_background();
        current = current->right;
    }
    else if (STATE == ANSWER)
    {
        STATE = RETURN_TO_MENU;
        background = backgrounds[0];
        reset_buffer();
    }
#ifdef VOICE
speak(current->value);
#endif

    return;
}

void no( void )
{
    if (current->left == NULL && current->right == NULL)
    {
        STATE = ANSWER;
        background = backgrounds[2];
    }

    if (STATE == GAME)
    {
        select_random_background();
        current = current->left;
    }
    else if (STATE == ANSWER)
    {
        STATE = ADD_NODE_ANSWER;
        background = backgrounds[0];
        reset_buffer();
    }
#ifdef VOICE
speak(current->value);
#endif

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

void select_random_background( void )
{
    background = backgrounds[rand() % bg_cnt];

    return;
}

#ifdef VOICE
void speak( const char *str )
{
    char str_b[256] = {};
    sprintf(str_b, "echo \"%s?\" | piper -m akinator/ru_RU-dmitri-medium.onnx --output-file out.wav", str);
    system(str_b);
    system("paplay out.wav");
    system("rm -f out.wav");
    return;
}
#endif
