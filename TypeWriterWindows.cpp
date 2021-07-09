#include "TypeWriterWindows.h"

#ifdef Q_OS_WINDOWS
extern "C" {
    #include <windows.h>
}

TypeWriterWindows::TypeWriterWindows()
{

}

TypeWriterWindows::~TypeWriterWindows()
{

}

void TypeWriterWindows::type_key(QStringList keys){
    unsigned char key;
    QStringList::iterator i;
    for(i = keys.begin(); i != keys.end(); ++i){
        key = str2unicode(*i);
        keybd_event(key, MapVirtualKey(key, 0), 0, 0);
    }
    QStringList::reverse_iterator r;
    for(r = keys.rbegin(); r != keys.rend(); ++r){
        key = str2unicode(*r);
        keybd_event(key, MapVirtualKey(key, 0), KEYEVENTF_KEYUP, 0);
    }
}

unsigned char TypeWriterWindows::str2unicode(QString in){
    if(in == "MODIFIERKEY_GUI" || in == "MODIFIERKEY_LEFT_GUI" || in == "KEY_LEFT_GUI")
        return VK_LWIN;
    if(in == "MODIFIERKEY_RIGHT_GUI" || in == "KEY_RIGHT_GUI")
        return VK_RWIN;
    if(in == "MODIFIERKEY_ALT" || in == "MODIFIERKEY_LEFT_ALT" || in == "KEY_LEFT_ALT")
        return VK_MENU;
    if(in == "MODIFIERKEY_RIGHT_ALT" || in == "KEY_RIGHT_ALT")
        return VK_MENU;
    if(in == "MODIFIERKEY_SHIFT" || in == "MODIFIERKEY_LEFT_SHIFT" || in == "KEY_LEFT_SHIFT")
        return VK_LSHIFT;
    if(in == "MODIFIERKEY_RIGHT_SHIFT" || in == "KEY_RIGHT_SHIFT")
        return VK_RSHIFT;
    if(in == "MODIFIERKEY_CTRL" || in == "MODIFIERKEY_LEFT_CTRL" || in == "KEY_LEFT_CTRL")
        return VK_LCONTROL;
    if(in == "MODIFIERKEY_RIGHT_CTRL" || in == "KEY_RIGHT_CTRL")
        return VK_RCONTROL;

    if(in == "KEY_MEDIA_VOLUME_INC")
        return VK_VOLUME_UP;
    if(in == "KEY_MEDIA_VOLUME_DEC")
        return VK_VOLUME_DOWN;
    if(in == "KEY_MEDIA_MUTE")
        return VK_VOLUME_MUTE;
    if(in == "KEY_MEDIA_PLAY_PAUSE")
        return VK_MEDIA_PLAY_PAUSE;
    if(in == "KEY_MEDIA_NEXT_TRACK")
        return VK_MEDIA_NEXT_TRACK;
    if(in == "KEY_MEDIA_PREV_TRACK")
        return VK_MEDIA_PREV_TRACK;

    if(in == "KEY_A")
        return 0x41;
    if(in == "KEY_B")
        return 0x42;
    if(in == "KEY_C")
        return 0x43;
    if(in == "KEY_D")
        return 0x44;
    if(in == "KEY_E")
        return 0x45;
    if(in == "KEY_F")
        return 0x46;
    if(in == "KEY_G")
        return 0x47;
    if(in == "KEY_H")
        return 0x48;
    if(in == "KEY_I")
        return 0x49;
    if(in == "KEY_J")
        return 0x4a;
    if(in == "KEY_K")
        return 0x4b;
    if(in == "KEY_L")
        return 0x4c;
    if(in == "KEY_M")
        return 0x4d;
    if(in == "KEY_N")
        return 0x4e;
    if(in == "KEY_O")
        return 0x4f;
    if(in == "KEY_P")
        return 0x50;
    if(in == "KEY_Q")
        return 0x51;
    if(in == "KEY_R")
        return 0x52;
    if(in == "KEY_S")
        return 0x53;
    if(in == "KEY_T")
        return 0x54;
    if(in == "KEY_U")
        return 0x55;
    if(in == "KEY_V")
        return 0x56;
    if(in == "KEY_W")
        return 0x57;
    if(in == "KEY_X")
        return 0x58;
    if(in == "KEY_Y")
        return 0x59;
    if(in == "KEY_Z")
        return 0x5a;
    if(in == "KEY_0")
        return 0x30;
    if(in == "KEY_1")
        return 0x31;
    if(in == "KEY_2")
        return 0x32;
    if(in == "KEY_3")
        return 0x33;
    if(in == "KEY_4")
        return 0x34;
    if(in == "KEY_5")
        return 0x35;
    if(in == "KEY_6")
        return 0x36;
    if(in == "KEY_7")
        return 0x37;
    if(in == "KEY_8")
        return 0x38;
    if(in == "KEY_9")
        return 0x39;
    if(in == "KEY_ENTER")
        return VK_RETURN;
    if(in == "KEY_ESC")
        return VK_ESCAPE;
    if(in == "KEY_BACKSPACE")
        return VK_BACK;
    if(in == "KEY_TAB")
        return VK_TAB;
    if(in == "KEY_SPACE")
        return VK_SPACE;
    if(in == "KEY_MINUS")
        return VK_OEM_MINUS;
    if(in == "KEY_EQUAL")
        return VK_OEM_PLUS;
    if(in == "KEY_LEFT_BRACE")
        return VK_OEM_4;
    if(in == "KEY_RIGHT_BRACE")
        return VK_OEM_6;
    if(in == "KEY_BACKSLASH")
        return VK_OEM_5;
    if(in == "KEY_SEMICOLON")
        return VK_OEM_1;
    if(in == "KEY_QUOTE")
        return VK_OEM_7;
    if(in == "KEY_TILDE")
        return VK_OEM_3;
    if(in == "KEY_COMMA")
        return VK_OEM_COMMA;
    if(in == "KEY_PERIOD")
        return VK_OEM_PERIOD;
    if(in == "KEY_SLASH")
        return VK_OEM_2;
    if(in == "KEY_CAPS_LOCK")
        return VK_CAPITAL;
    if(in == "KEY_F1")
        return VK_F1;
    if(in == "KEY_F2")
        return VK_F2;
    if(in == "KEY_F3")
        return VK_F3;
    if(in == "KEY_F4")
        return VK_F4;
    if(in == "KEY_F5")
        return VK_F5;
    if(in == "KEY_F6")
        return VK_F6;
    if(in == "KEY_F7")
        return VK_F7;
    if(in == "KEY_F8")
        return VK_F8;
    if(in == "KEY_F9")
        return VK_F9;
    if(in == "KEY_F10")
        return VK_F10;
    if(in == "KEY_F11")
        return VK_F11;
    if(in == "KEY_F12")
        return VK_F12;
    if(in == "KEY_PRINTSCREEN")
        return VK_SNAPSHOT;
    if(in == "KEY_SCROLL_LOCK")
        return VK_SCROLL;
    if(in == "KEY_PAUSE")
        return VK_PAUSE;
    if(in == "KEY_INSERT")
        return VK_INSERT;
    if(in == "KEY_HOME")
        return VK_HOME;
    if(in == "KEY_PAGEUP")
        return VK_PRIOR;
    if(in == "KEY_PAGEDOWN")
        return VK_NEXT;
    if(in == "KEY_END")
        return VK_END;
    if(in == "KEY_DELETE")
        return VK_DELETE;
    if(in == "KEY_RIGHT")
        return VK_RIGHT;
    if(in == "KEY_LEFT")
        return VK_LEFT;
    if(in == "KEY_DOWN")
        return VK_DOWN;
    if(in == "KEY_UP")
        return VK_UP;
    if(in == "KEY_NUM_LOCK")
        return VK_NUMLOCK;
    if(in == "KEYPAD_SLASH")
        return VK_DIVIDE;
    if(in == "KEYPAD_ASTERIX")
        return VK_MULTIPLY;
    if(in == "KEYPAD_MINUS")
        return VK_SUBTRACT;
    if(in == "KEYPAD_PLUS")
        return VK_ADD;
    if(in == "KEYPAD_ENTER")
        return VK_RETURN;
    if(in == "KEYPAD_0")
        return VK_NUMPAD0;
    if(in == "KEYPAD_1")
        return VK_NUMPAD1;
    if(in == "KEYPAD_2")
        return VK_NUMPAD2;
    if(in == "KEYPAD_3")
        return VK_NUMPAD3;
    if(in == "KEYPAD_4")
        return VK_NUMPAD4;
    if(in == "KEYPAD_5")
        return VK_NUMPAD5;
    if(in == "KEYPAD_6")
        return VK_NUMPAD6;
    if(in == "KEYPAD_7")
        return VK_NUMPAD7;
    if(in == "KEYPAD_8")
        return VK_NUMPAD8;
    if(in == "KEYPAD_9")
        return VK_NUMPAD9;
    if(in == "KEYPAD_PERIOD")
        return VK_DECIMAL;
    if(in == "KEY_APP")
        return VK_APPS;
    if(in == "KEY_EXE")
        return VK_EXECUTE;
    if(in == "KEY_HELP")
        return VK_HELP;
    if(in == "KEY_MENU")
        return VK_RMENU;
    if(in == "KEY_SELECT")
        return VK_SELECT;
    if(in == "KEY_STOP")
        return VK_MEDIA_STOP;
    if(in == "KEY_NON_US_NUM")
        return VK_PACKET;
    /*
    KEYPAD_EQUALS = 103
    KEY_POWER = 0x66
    KEY_AGAIN = 0x79
    KEY_UNDO = 0x7A
    KEY_CUT = 0x7B
    KEY_COPY = 0x7C
    KEY_PASTE = 0x7D
    KEY_FIND = 0x7E
    KEY_SYSTEM_POWER = 0x81
    KEY_SYSTEM_SLEEP = 0x82
    KEY_SYSTEM_WAKE = 0x83
    KEYPAD_PIPE = 0xC9
    */
    return 0;
}

#endif
