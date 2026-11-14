#include "akinator.h"

extern tree_node_t *current;

int buttons_cnt = 0;
button_t buttons[7] = {};
enum APP_STATE STATE = MENU;
extern Font font;

void DrawApp( void )
{
    ClearBackground(BLACK);

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
        default:
            break;
    }

    Draw();

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

    DrawButtons();

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

    for (int i = 32; i < 127; i++) codepoints[count++] = i;
    for (int i = 0x400; i < 0x4FF; i++) codepoints[count++] = i;

    return LoadFontEx(font_file_name, 256, codepoints, count);
}

void DrawCenteredText( const char *str )
{
    int fontSize = 30;
    int strWidth = MeasureText(str, fontSize);

    DrawTextEx(font, str, (Vector2){ (float)(WINDOW_W - strWidth) / 2.0f, (float)WINDOW_H / 4.0f }, 30, 2, WHITE);
    //DrawText(str, (WINDOW_W - strWidth) / 2, WINDOW_H / 4, fontSize, WHITE);

    return;
}

void DrawButtons( void )
{
    for (int i = 0; i < buttons_cnt; i++)
    {
        if (buttons[i].is_active)
        {
            //printf("%s", buttons[i].str);
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
        for (int i = 0; i < buttons_cnt; i++)
        {
            if(buttons[i].is_active &&
            CheckCollisionPointRec(GetMousePosition(), Rectangle{ (float)buttons[i].x, (float)buttons[i].y, (float)BUTTON_W, (float)BUTTON_H }))
                return &buttons[i];
        }
    }

    return NULL;
}
void nul( void )
{
    printf("nul\n");
    return;
}
void InitButtons( void )
{
    AddButton((WINDOW_W - BUTTON_W)/2, 3 * WINDOW_H / 8, "начать игру", start_session);
    AddButton((WINDOW_W - BUTTON_W)/2, 4 * WINDOW_H / 8, "загрузить данные", nul     );
    AddButton((WINDOW_W - BUTTON_W)/2, 5 * WINDOW_H / 8, "сохранить игру", nul       );
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
