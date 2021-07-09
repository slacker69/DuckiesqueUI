#include "TypeWriterLinux.h"

#ifdef Q_OS_LINUX
extern "C" {
    #include <X11/Xlib.h>
    #include <X11/keysym.h>
    #include <X11/extensions/XTest.h>
    #include <X11/XF86keysym.h>
}

TypeWriterLinux::TypeWriterLinux()
{
    display = (void *)XOpenDisplay(NULL);
}

TypeWriterLinux::~TypeWriterLinux()
{
    XCloseDisplay((Display *)display);
}

void TypeWriterLinux::type_key(QStringList keys){
    QStringList::iterator i;
    for(i = keys.begin(); i != keys.end(); ++i){
        XTestFakeKeyEvent((Display *)display, XKeysymToKeycode((Display *)display, (KeySym)str2unicode(*i)), True, CurrentTime);
    }
    QStringList::reverse_iterator r;
    for(r = keys.rbegin(); r != keys.rend(); ++r){
        XTestFakeKeyEvent((Display *)display, XKeysymToKeycode((Display *)display, (KeySym)str2unicode(*r)), False, CurrentTime);
    }
    XFlush((Display *)display);
}

quint16 TypeWriterLinux::str2unicode(QString in){
    if(in == "MODIFIERKEY_GUI" || in == "MODIFIERKEY_LEFT_GUI" || in == "KEY_LEFT_GUI")
        return XK_Super_L;
    if(in == "MODIFIERKEY_RIGHT_GUI" || in == "KEY_RIGHT_GUI")
        return XK_Super_R;
    if(in == "MODIFIERKEY_ALT" || in == "MODIFIERKEY_LEFT_ALT" || in == "KEY_LEFT_ALT")
        return XK_Alt_L;
    if(in == "MODIFIERKEY_RIGHT_ALT" || in == "KEY_RIGHT_ALT")
        return XK_Alt_R;
    if(in == "MODIFIERKEY_SHIFT" || in == "MODIFIERKEY_LEFT_SHIFT" || in == "KEY_LEFT_SHIFT")
        return XK_Shift_L;
    if(in == "MODIFIERKEY_RIGHT_SHIFT" || in == "KEY_RIGHT_SHIFT")
        return XK_Shift_R;
    if(in == "MODIFIERKEY_CTRL" || in == "MODIFIERKEY_LEFT_CTRL" || in == "KEY_LEFT_CTRL")
        return XK_Control_L;
    if(in == "MODIFIERKEY_RIGHT_CTRL" || in == "KEY_RIGHT_CTRL")
        return XK_Control_R;

    if(in == "KEY_MEDIA_VOLUME_INC")
        return (quint16)XF86XK_AudioRaiseVolume;
    if(in == "KEY_MEDIA_VOLUME_DEC")
        return (quint16)XF86XK_AudioLowerVolume;
    if(in == "KEY_MEDIA_MUTE")
        return (quint16)XF86XK_AudioMute;
    if(in == "KEY_MEDIA_PLAY_PAUSE")
        return (quint16)XF86XK_AudioPlay;
    if(in == "KEY_MEDIA_NEXT_TRACK")
        return (quint16)XF86XK_AudioNext;
    if(in == "KEY_MEDIA_PREV_TRACK")
        return (quint16)XF86XK_AudioPrev;

    if(in == "KEY_A")
        return XK_a;
    if(in == "KEY_B")
        return XK_b;
    if(in == "KEY_C")
        return XK_c;
    if(in == "KEY_D")
        return XK_d;
    if(in == "KEY_E")
        return XK_e;
    if(in == "KEY_F")
        return XK_f;
    if(in == "KEY_G")
        return XK_g;
    if(in == "KEY_H")
        return XK_h;
    if(in == "KEY_I")
        return XK_i;
    if(in == "KEY_J")
        return XK_j;
    if(in == "KEY_K")
        return XK_k;
    if(in == "KEY_L")
        return XK_l;
    if(in == "KEY_M")
        return XK_m;
    if(in == "KEY_N")
        return XK_n;
    if(in == "KEY_O")
        return XK_o;
    if(in == "KEY_P")
        return XK_p;
    if(in == "KEY_Q")
        return XK_q;
    if(in == "KEY_R")
        return XK_r;
    if(in == "KEY_S")
        return XK_s;
    if(in == "KEY_T")
        return XK_t;
    if(in == "KEY_U")
        return XK_u;
    if(in == "KEY_V")
        return XK_v;
    if(in == "KEY_W")
        return XK_w;
    if(in == "KEY_X")
        return XK_x;
    if(in == "KEY_Y")
        return XK_y;
    if(in == "KEY_Z")
        return XK_z;
    if(in == "KEY_0")
        return XK_0;
    if(in == "KEY_1")
        return XK_1;
    if(in == "KEY_2")
        return XK_2;
    if(in == "KEY_3")
        return XK_3;
    if(in == "KEY_4")
        return XK_4;
    if(in == "KEY_5")
        return XK_5;
    if(in == "KEY_6")
        return XK_6;
    if(in == "KEY_7")
        return XK_7;
    if(in == "KEY_8")
        return XK_8;
    if(in == "KEY_9")
        return XK_9;
    if(in == "KEY_ENTER")
        return XK_Return;
    if(in == "KEY_ESC")
        return XK_Escape;
    if(in == "KEY_BACKSPACE")
        return XK_BackSpace;
    if(in == "KEY_TAB")
        return XK_Tab;
    if(in == "KEY_SPACE")
        return XK_space;
    if(in == "KEY_MINUS")
        return XK_minus;
    if(in == "KEY_EQUAL")
        return XK_equal;
    if(in == "KEY_LEFT_BRACE")
        return XK_braceleft;
    if(in == "KEY_RIGHT_BRACE")
        return XK_braceright;
    if(in == "KEY_BACKSLASH")
        return XK_backslash;
    if(in == "KEY_SEMICOLON")
        return XK_semicolon;
    if(in == "KEY_QUOTE")
        return XK_apostrophe;
    if(in == "KEY_TILDE")
        return XK_asciitilde;
    if(in == "KEY_COMMA")
        return XK_comma;
    if(in == "KEY_PERIOD")
        return XK_period;
    if(in == "KEY_SLASH")
        return XK_slash;
    if(in == "KEY_CAPS_LOCK")
        return XK_Caps_Lock;
    if(in == "KEY_F1")
        return XK_F1;
    if(in == "KEY_F2")
        return XK_F2;
    if(in == "KEY_F3")
        return XK_F3;
    if(in == "KEY_F4")
        return XK_F4;
    if(in == "KEY_F5")
        return XK_F5;
    if(in == "KEY_F6")
        return XK_F6;
    if(in == "KEY_F7")
        return XK_F7;
    if(in == "KEY_F8")
        return XK_F8;
    if(in == "KEY_F9")
        return XK_F9;
    if(in == "KEY_F10")
        return XK_F10;
    if(in == "KEY_F11")
        return XK_F11;
    if(in == "KEY_F12")
        return XK_F12;
    if(in == "KEY_PRINTSCREEN")
        return XK_Print;
    if(in == "KEY_SCROLL_LOCK")
        return XK_Scroll_Lock;
    if(in == "KEY_PAUSE")
        return XK_Pause;
    if(in == "KEY_INSERT")
        return XK_Insert;
    if(in == "KEY_HOME")
        return XK_Home;
    if(in == "KEY_PAGEUP")
        return XK_Page_Up;
    if(in == "KEY_DELETE")
        return XK_Delete;
    if(in == "KEY_END")
        return XK_End;
    if(in == "KEY_PAGEDOWN")
        return XK_Page_Down;
    if(in == "KEY_RIGHT")
        return XK_Right;
    if(in == "KEY_LEFT")
        return XK_Left;
    if(in == "KEY_DOWN")
        return XK_Down;
    if(in == "KEY_UP")
        return XK_Up;
    if(in == "KEY_NUM_LOCK")
        return XK_Num_Lock;
    if(in == "KEYPAD_SLASH")
        return XK_KP_Divide;
    if(in == "KEYPAD_ASTERIX")
        return XK_KP_Multiply;
    if(in == "KEYPAD_MINUS")
        return XK_KP_Subtract;
    if(in == "KEYPAD_PLUS")
        return XK_KP_Add;
    if(in == "KEYPAD_ENTER")
        return XK_KP_Enter;
    if(in == "KEYPAD_EQUALS")
        return XK_KP_Equal;
    if(in == "KEYPAD_1")
        return XK_KP_1;
    if(in == "KEYPAD_2")
        return XK_KP_2;
    if(in == "KEYPAD_3")
        return XK_KP_3;
    if(in == "KEYPAD_4")
        return XK_KP_4;
    if(in == "KEYPAD_5")
        return XK_KP_5;
    if(in == "KEYPAD_6")
        return XK_KP_6;
    if(in == "KEYPAD_7")
        return XK_KP_7;
    if(in == "KEYPAD_8")
        return XK_KP_8;
    if(in == "KEYPAD_9")
        return XK_KP_9;
    if(in == "KEYPAD_0")
        return XK_KP_0;
    if(in == "KEYPAD_PERIOD")
        return XK_KP_Decimal;
    if(in == "KEY_MENU")
        return XK_Menu;
    return 0;
}

#endif
