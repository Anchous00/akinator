#ifndef AKINATOR_H
#define AKINATOR_H

#include "../tree.h"
#include <locale.h>
#include <raylib.h>

typedef void(*func_t)(void);

enum BUTTON
{
    START_SESSION   = 0,
    LOAD_DB         = 1,
    SAVE_DB         = 2,
    QUIT            = 3,
    YES             = 4,
    NO              = 5,
    MAIN_MENU       = 6
};

enum APP_STATE
{
    GAME = 0,
    MENU = 1,
    ANSWER = 2,
    RETURN_TO_MENU = 3
};

const int WINDOW_W = 1000;
const int WINDOW_H = 1000;

const int BUTTON_W = 400;
const int BUTTON_H = 100;

struct button_t
{
    int x;
    int y;
    const char *str;
    bool is_active;
    func_t func;
};

void ask_question( tree_node_t *node );
void add_node( tree_node_t *node );
Font LoadCustomFont( const char *font_file_name );
void Menu( void );
//void return_to_menu( const char *str );
void start_session ( void );
void yes           ( void );
void no            ( void );
void return_to_menu( void );
void quit          ( void ) __attribute__((noreturn));

void InitButtons( void );
button_t* GetPressedButton( void );
void AddButton( int x, int y, const char *str, func_t func );

void DrawButton ( button_t btn );
void DrawButtons( void );

int ButtonPressed( int x, int y );
void DrawCenteredText( const char *str );
void SkipMultiClick( void );

void DrawApp         ( void );
void DrawMenu        ( void );
void DrawGame        ( void );
void DrawReturnToMenu( void );
void Draw            ( void );


#endif
