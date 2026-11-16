#include "akinator.h"

extern tree_node_t *root;
extern tree_node_t *current;

int buttons_cnt = 0;
button_t buttons[7] = {};
enum APP_STATE STATE = MENU;
extern Font font;
extern char buffer[MAX_STR_LEN];
extern int char_cnt;

void DrawApp( void )
{
    switch (STATE)
    {
        case MENU:
            DrawMenu();
            break;
        case GAME:
            DrawGame();
            break;
        case RETURN_TO_MENU:
            DrawReturnToMenu();
            break;
        case ANSWER:
            DrawGame();
            break;
        case ADD_NODE_ANSWER:
            DrawAddAnswer();
            break;
        case ADD_NODE_QUESTION:
            DrawAddQuestion();
            break;
        case SAVING_DB:
            DrawSavingDB();
            break;
        case LOADING_DB:
            DrawLoadingDB();
            break;
        default:
            break;
    }

    return;
}

void DrawMenu( void )
{
    int i = 0;
    for (; i < 4; i++)
        buttons[i].is_active = 1;
    for (; i < buttons_cnt; i++)
        buttons[i].is_active = 0;


    DrawButtons();

    return;
}

void DrawGame( void )
{
    int i = 0;
    for (; i < 4; i++)
        buttons[i].is_active = 0;
    for (; i < 6; i++)
        buttons[i].is_active = 1;
    buttons[6].is_active = 0;

    DrawButtons();
    DrawCenteredText(current->value);

    return;
}

void DrawReturnToMenu( void )
{
    int i = 0;
    for (; i < 6; i++)
        buttons[i].is_active = 0;
    buttons[6].is_active = 1;
    DrawCenteredText("Старый бог здесь");
    DrawButtons();

    return;
}

void DrawAddAnswer( void )
{
    int i = 0;
    for (; i < 7; i++)
        buttons[i].is_active = 0;

    DrawCenteredText("Кого ты загадал?");

    if (InputBox((WINDOW_W - BUTTON_W) / 2, 400, BUTTON_W, BUTTON_H))
    {
        link_node(&current->right, buffer);
        STATE = ADD_NODE_QUESTION;
        reset_buffer();
    }



    return;
}

void DrawAddQuestion( void )
{
    int i = 0;
    for (; i < 7; i++)
        buttons[i].is_active = 0;
    char str[256] = {};
    sprintf(str, "Что его отличает от %s", current->value);
    DrawCenteredText(str);

    if (InputBox((WINDOW_W - BUTTON_W) / 2, 400, BUTTON_W, BUTTON_H))
    {
        link_node(&current->left, current->value);
        free(current->value);
        current->value = strdup(buffer);
        reset_buffer();
        STATE = MENU;
    }

    return;
}

void DrawLoadingDB( void )
{
    int i = 0;
    for (; i < 7; i++)
        buttons[i].is_active = 0;

    DrawCenteredText("Введи название файла");

    if (InputBox((WINDOW_W - BUTTON_W) / 2, 400, BUTTON_W, BUTTON_H))
    {
        load_tree(&root, buffer);
        STATE = MENU;
    }

    return;
}

void DrawSavingDB( void )
{
    int i = 0;
    for (; i < 7; i++)
        buttons[i].is_active = 0;

    DrawCenteredText("Введи название файла");

    if (InputBox((WINDOW_W - BUTTON_W) / 2, 400, BUTTON_W, BUTTON_H))
    {
        save_tree(root, buffer);
        STATE = MENU;
    }

    return;

    return;
}

void Draw( void )
{
    EndDrawing();
    BeginDrawing();

    return;
}

Font LoadCustomFont( const char *font_file_name )
{
    int codepoints[512] = {};
    int count = 0;

    for (int i = 32; i <= 127; i++) codepoints[count++] = i;
    for (int i = 0x400; i <= 0x4FF; i++) codepoints[count++] = i;

    return LoadFontEx(font_file_name, 256, codepoints, count);
}

void DrawCenteredText( const char *str )
{
    int fontSize = 30;
    int strWidth = MeasureText(str, fontSize);

    DrawTextEx(font, str, (Vector2){ (float)(WINDOW_W - strWidth) / 2.0f, (float)WINDOW_H / 4.0f }, 30, 2, WHITE);

    return;
}

void DrawButtons( void )
{
    for (int i = 0; i < buttons_cnt; i++)
    {
        if (buttons[i].is_active)
        {
            DrawButton(buttons[i]);
        }
    }
}

void DrawButton( button_t btn )
{
    DrawRectangle(btn.x, btn.y, BUTTON_W, BUTTON_H, GRAY);
    DrawTextEx(font, btn.str, (Vector2){ (float)btn.x, (float)btn.y }, 30, 2, BLACK);
    //DrawText(btn.str, btn.x, btn.y, 30, BLACK);
}

button_t* GetPressedButton( void )
{
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        SkipMultiClick();

        for (int i = 0; i < buttons_cnt; i++)
        {
            if(buttons[i].is_active &&
            CheckCollisionPointRec(GetMousePosition(), Rectangle{ (float)buttons[i].x, (float)buttons[i].y, (float)BUTTON_W, (float)BUTTON_H }))
                return &buttons[i];
        }
    }

    return NULL;
}

void InitButtons( void )
{
    AddButton((WINDOW_W - BUTTON_W)/2, 3 * WINDOW_H / 8, "начать игру", start_session);
    AddButton((WINDOW_W - BUTTON_W)/2, 4 * WINDOW_H / 8, "загрузить данные", load_db     );
    AddButton((WINDOW_W - BUTTON_W)/2, 5 * WINDOW_H / 8, "сохранить игру", save_db       );
    AddButton((WINDOW_W - BUTTON_W)/2, 6 * WINDOW_H / 8, "выход", quit               );

    AddButton(WINDOW_W/2 - BUTTON_W, WINDOW_H / 2, "да", yes   );
    AddButton(WINDOW_W/2 + 100,      WINDOW_H / 2, "нет", no   );

    AddButton((WINDOW_W - BUTTON_W)/2, WINDOW_H / 2, "меню", return_to_menu);

    return;
}

int ButtonPressed( int x, int y )
{
    for (int i = 0; i < buttons_cnt; i++)
    {
        if (buttons[i].is_active && x > buttons[i].x && y > buttons[i].y && x < buttons[i].x + BUTTON_W && y < buttons[i].y + BUTTON_H)
            return i;
    }

    return -1;
}

void AddButton( int x, int y, const char *str, func_t func )
{
    buttons[buttons_cnt].x = x;
    buttons[buttons_cnt].y = y;
    buttons[buttons_cnt].str = str;
    buttons[buttons_cnt].func = func;
    buttons_cnt++;

    return;
}

void SkipMultiClick( void )
{
    while (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        BeginDrawing();
        EndDrawing();
    }

    return;
}

int InputBox( int x, int y, int width, int height)
{
    Rectangle text_box = {(float)x, (float)y, (float)width, (float)height};
    int font_size = (int)(height * 0.4 + 2);
    DrawRectangleRec(text_box, WHITE);
    char *draw_buffer = buffer;
    ;
    while (MeasureTextEx(font, draw_buffer, font_size, 2).x > width)
    {
        draw_buffer++;
        if ((*draw_buffer & 0xC0) == 0x80)
            draw_buffer++;
    }
    DrawTextEx(font, draw_buffer, (Vector2){ (float)x, (float)y }, font_size, 2, BLACK);

    if (CheckCollisionPointRec(GetMousePosition(), text_box))
    {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        int key= GetCharPressed();
        while (key > 0)
        {
            if ((((key >= 32) && (key <= 0x4FF))) && (char_cnt < MAX_STR_LEN - 1))
            {

                int len = 0;
                const char *utf8 = CodepointToUTF8(key, &len);

                if (char_cnt + len < MAX_STR_LEN - 1)
                {
                    memcpy(&buffer[char_cnt], utf8, len);
                    char_cnt += len;
                }
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE))
        {
            int i = char_cnt - 1;
            while (i > 0 && (buffer[i] & 0xC0) == 0x80)
            {
                i--;
            }
            char_cnt = i < 0 ? 0 : i;
            buffer[char_cnt] = '\0';
            buffer[char_cnt + 1] = '\0';
        }
        if (IsKeyPressed(KEY_ENTER))
        {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            return 1;
        }
    }
    else
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    return 0;

}

void reset_buffer( void )
{
    for (int i = 0; i < MAX_STR_LEN; i++)
        buffer[i] = '\0';
    char_cnt = 0;
}
