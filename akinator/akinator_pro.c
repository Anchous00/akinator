#include "akinator.h"
//TODO свой инпут
//TODO эстетик ебейший
//TODO порноакинатор
//TODO терминал

tree_node_t *root = NULL;
tree_node_t *current = root;
extern enum APP_STATE STATE;
Font font = {};

int main( void )
{
    root = create_node("Egorka d");
    current = root;
    //SetTraceLogLevel(LOG_NONE);
    InitWindow(WINDOW_W, WINDOW_H, "АКИНАТОР В ПОПЕ ВИБРАТОР");
    font = LoadCustomFont("akinator/arial.ttf");

    SetTargetFPS(60);
    InitButtons();
    STATE = MENU;
    button_t *pressed_button = NULL;
    while (!WindowShouldClose())
    {
        pressed_button = GetPressedButton();
        if (pressed_button != NULL)
        {
            printf("pressed %s\n", pressed_button->str);
            pressed_button->func();
        }
        BeginDrawing();
        DrawApp();
        EndDrawing();
    }

    return 0;
}

// void Menu( void )
// {
//     char str[100] = {};
//     int b = -1;
//     bool textEditMode = false;
//     while (!WindowShouldClose())
//     {
//         DrawMenu();
//         //b = wait_for_action();
//         switch (b)
//         {
//             case QUIT:
//                 quit();
//                 return;
//             case START_SESSION:
//                 DrawGame();
//                 ask_question(root);
//                 break;
//             case SAVE_DB:
//                 textEditMode = false;
//                 while (!IsKeyPressed(KEY_ENTER))
//                 {
//                     if (WindowShouldClose())
//                     {
//                         quit();
//                     }
//                     BeginDrawing();
//                     if (GuiTextBox((Rectangle){ 50, 200, WINDOW_W - 50, 120 }, str, 512, textEditMode))
//                     {
//                         textEditMode = !textEditMode;
//                     }
//                     EndDrawing();
//                 }
//                 save_tree(root, str);
//                 break;
//             case LOAD_DB:
//                 textEditMode = false;
//                 while (!IsKeyPressed(KEY_ENTER))
//                 {
//                     if (WindowShouldClose())
//                     {
//                         quit();
//                     }
//                     BeginDrawing();
//                     if (GuiTextBox((Rectangle){ 50, 200, WINDOW_W - 50, 120 }, str, 512, textEditMode))
//                     {
//                         textEditMode = !textEditMode;
//                     }
//                     EndDrawing();
//                 }
//                 load_tree(&root, str);
//                 break;
//             case '4':
//                 tree_draw_graph(root);
//                 log_file_close();
//                 system("xdg-open log.html");
//                 break;
//             default:
//                 break;
//         }
//     }
//
//     return;
// }

void start_session( void )
{
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

// void return_to_menu( const char *str )
// {
// int b = -1;
//     while (b < 0)
//     {
//         DrawReturnToMenu();
//         //b = wait_for_action();
//         switch (b)
//         {
//             case MAIN_MENU:
//                 Menu();
//                 return;
//             default:
//                 break;
//         }
//     }
//
//     return;
// }

void yes( void )
{
    if (current->left == NULL && current->right == NULL)
        STATE = ANSWER;

    if (STATE == GAME)
        current = current->right;
    else if (STATE == ANSWER)
    {
        printf("i win work in progress\n");
        STATE = RETURN_TO_MENU;
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
        printf("add node work in progress\n");

    return;
}

// void ask_question( tree_node_t *node )
// {
//     int b = -1;
//     char str[256];
//     Vector2 inputPosition = {0, 0};
//     if (node->right == NULL || node->left == NULL)
//     {
//         sprintf(str, "ты загадал %s?\n", node->value);
//         ClearBackground(BLUE);
//         DrawCenteredText(str);
//         DrawButtons();
//         Draw();
//         while(b < 0)
//         {
//             inputPosition = GetMousePosition();
//             if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
//             {
//                 printf("%d %d\n", (int)inputPosition.x, (int)inputPosition.y);
//                 b = ButtonPressed((int)inputPosition.x, (int)inputPosition.y);
//                 SkipMultiClick();
//             }
//
//             BeginDrawing();
//
//             EndDrawing();
//         }
//         switch (b)
//         {
//             case YES:
//                 return_to_menu("Thats right, i win");
//             while(b < 0)
//             {
//                 inputPosition = GetMousePosition();
//                 if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
//                 {
//                     printf("%d %d\n", (int)inputPosition.x, (int)inputPosition.y);
//                     b = ButtonPressed((int)inputPosition.x, (int)inputPosition.y);
//                     SkipMultiClick();
//                 }
//
//                 BeginDrawing();
//
//                 EndDrawing();
//             }
//                 break;
//             case NO:
//                 ClearBackground(BLUE);
//                 DrawCenteredText("i don't know this character\nwhat do you mean?");
//                 DrawButtons();
//                 Draw();
//                 add_node(node);
//                 break;
//             default:
//                 break;
//         }
//         return;
//     }
//
//
//     sprintf(str, "%s?\n", node->value);
//     ClearBackground(BLUE);
//     DrawCenteredText(str);
//     DrawButtons();
//     Draw();
//
//
//     while (b < 0)
//     {
//         inputPosition = GetMousePosition();
//         if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
//         {
//             printf("%d %d\n", (int)inputPosition.x, (int)inputPosition.y);
//             b = ButtonPressed((int)inputPosition.x, (int)inputPosition.y);
//             SkipMultiClick();
//         }
//         BeginDrawing();
//
//         EndDrawing();
//     }
//     switch (b)
//     {
//         case YES:
//             ask_question(node->right);
//             break;
//         case NO:
//             ask_question(node->left);
//             break;
//         default:
//             break;
//     }
//
//     return;
// }

// void add_node( tree_node_t *node )
// {
//     char question[256] = {};
//     char answer[256] = {};
//     // printf("кого ты загадал?\n");
//     // getchar();
//     // scanf("%[^\n]", answer);
//     // printf("что его отличает от %s?\n", node->value);
//     // getchar();
//     // scanf("%[^\n]", question);
//
//     bool textEditMode = false;
//     while (!IsKeyPressed(KEY_ENTER))
//     {
//         if (WindowShouldClose())
//         {
//             quit();
//         }
//         BeginDrawing();
//         if (GuiTextBox((Rectangle){ 50, 200, WINDOW_W - 50, 120 }, answer, 512, textEditMode))
//         {
//             textEditMode = !textEditMode;
//         }
//         EndDrawing();
//     }
//     printf("1");
//     //while (IsKeyPressed(KEY_ENTER));
//     printf("2");
//     BeginDrawing();
//     ClearBackground(BLUE);
//     DrawCenteredText("What is the differense?");
//     DrawButtons();
//     Draw();
//
//     textEditMode = false;
//     while (!IsKeyPressed(KEY_ENTER))
//     {
//         if (WindowShouldClose())
//             {
//                 quit();
//             }
//         BeginDrawing();
//         if (GuiTextBox((Rectangle){ 50, 200, WINDOW_W - 50, 120 }, question, 512, textEditMode))
//         {
//             textEditMode = !textEditMode;
//         }
//         EndDrawing();
//     }
//
//     link_node(&node->right, answer);
//     link_node(&node->left, node->value);
//     free(node->value);
//     node->value = strdup(question);
//
//     return;
// }

