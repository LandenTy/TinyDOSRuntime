#ifndef KEYCODE_H
#define KEYCODE_H

typedef enum {
    KEY_NONE = 0,

    /* Alphabet keys */
    KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G,
    KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N,
    KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U,
    KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z,

    /* Number row */
    KEY_1, KEY_2, KEY_3, KEY_4, KEY_5,
    KEY_6, KEY_7, KEY_8, KEY_9, KEY_0,

    /* Symbols (main keyboard) */
    KEY_MINUS,      /* - */
    KEY_EQUALS,     /* = */
    KEY_BACKSPACE,
    KEY_TAB,
    KEY_LBRACKET,   /* [ */
    KEY_RBRACKET,   /* ] */
    KEY_BACKSLASH,  /* \ */
    KEY_SEMICOLON,  /* ; */
    KEY_APOSTROPHE, /* ' */
    KEY_GRAVE,      /* ` */
    KEY_COMMA,      /* , */
    KEY_PERIOD,     /* . */
    KEY_SLASH,      /* / */

    /* Control / function */
    KEY_ESCAPE,
    KEY_ENTER,
    KEY_SPACE,

    KEY_CAPSLOCK,
    KEY_LSHIFT,
    KEY_RSHIFT,
    KEY_LCTRL,
    KEY_RCTRL,
    KEY_LALT,
    KEY_RALT,
    KEY_SYSRQ,      /* Print Screen */
    KEY_SCROLLLOCK,
    KEY_PAUSE,
    KEY_NUMLOCK,

    /* Navigation / arrows */
    KEY_INSERT,
    KEY_DELETE,
    KEY_HOME,
    KEY_END,
    KEY_PAGEUP,
    KEY_PAGEDOWN,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,

    /* Function keys */
    KEY_F1,  KEY_F2,  KEY_F3,  KEY_F4,  KEY_F5,
    KEY_F6,  KEY_F7,  KEY_F8,  KEY_F9,  KEY_F10,
    KEY_F11, KEY_F12,

    /* Keypad (numpad) */
    KEY_KP_0,
    KEY_KP_1,
    KEY_KP_2,
    KEY_KP_3,
    KEY_KP_4,
    KEY_KP_5,
    KEY_KP_6,
    KEY_KP_7,
    KEY_KP_8,
    KEY_KP_9,
    KEY_KP_DECIMAL,
    KEY_KP_ENTER,
    KEY_KP_PLUS,
    KEY_KP_MINUS,
    KEY_KP_MULTIPLY,
    KEY_KP_DIVIDE,

    /* Special Keys */
    KEY_PRINT_SCREEN,  /* same as SYSRQ sometimes */
    KEY_MENU,          /* Windows 95+ keyboard “menu” key */
    KEY_WINDOWS_L,
    KEY_WINDOWS_R,

    KEY_COUNT
} KeyCode;

#endif
