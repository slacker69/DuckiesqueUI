#include "TypeWriterMacOS.h"

#ifdef Q_OS_MACOS
extern "C" {
    #include <ApplicationServices/ApplicationServices.h>
}

TypeWriterMacOS::TypeWriterMacOS()
{
    source = (void *)CGEventSourceCreate(kCGEventSourceStateCombinedSessionState);
}

TypeWriterMacOS::~TypeWriterMacOS()
{

}

void TypeWriterMacOS::type_key(QStringList keys){
    bool isMod;
    int flags = 0;
    QStringList::iterator i;
    for(i = keys.begin(); i != keys.end(); ++i){
        quint16 key_code = str2unicode(&isMod, (*i));
        if(isMod){
            if(key_code == 0x38)
                flags |= kCGEventFlagMaskShift;
            else if(key_code == 0x3B)
                flags |= kCGEventFlagMaskControl;
            else if(key_code == 0x3A)
                flags |= kCGEventFlagMaskAlternate;
            else if(key_code == 0x37)
                flags |= kCGEventFlagMaskCommand;
        }else{
            CGEventRef ev = CGEventCreateKeyboardEvent((CGEventSourceRef)source, (CGKeyCode)key_code, true);
            CGEventSetFlags(ev,flags);
            CGEventPost(kCGHIDEventTap,ev);
            CFRelease(ev);
        }
    }
    QStringList::reverse_iterator r;
    for(r = keys.rbegin(); r != keys.rend(); ++r){
        quint16 key_code = str2unicode(&isMod, (*r));
        if(!isMod){
            CGEventRef ev = CGEventCreateKeyboardEvent((CGEventSourceRef)source, (CGKeyCode)key_code, false);
            CGEventSetFlags(ev,flags);
            CGEventPost(kCGHIDEventTap,ev);
            CFRelease(ev);
        }
    }
}

quint16 TypeWriterMacOS::str2unicode(bool *mod, QString in){
    (*mod) = true;
    if(in == "MODIFIERKEY_SHIFT" || in == "MODIFIERKEY_LEFT_SHIFT" || in == "KEY_LEFT_SHIFT")
        return 0x38;
    if(in == "MODIFIERKEY_RIGHT_SHIFT" || in == "KEY_RIGHT_SHIFT")
        return 0x3C;
    if(in == "MODIFIERKEY_CTRL" || in == "MODIFIERKEY_LEFT_CTRL" || in == "KEY_LEFT_CTRL")
        return 0x3B;
    if(in == "MODIFIERKEY_RIGHT_CTRL" || in == "KEY_RIGHT_CTRL")
        return 0x3E;
    if(in == "MODIFIERKEY_ALT" || in == "MODIFIERKEY_LEFT_ALT" || in == "KEY_LEFT_ALT")
        return 0x3A;
    if(in == "MODIFIERKEY_RIGHT_ALT" || in == "KEY_RIGHT_ALT")
        return 0x3D;
    if(in == "MODIFIERKEY_GUI" || in == "MODIFIERKEY_LEFT_GUI" || in == "KEY_LEFT_GUI")
        return 0x37;
    if(in == "MODIFIERKEY_RIGHT_GUI" || in == "KEY_RIGHT_GUI")
        return 0x36;
    (*mod) = false;

    if(in == "KEY_A")
        return 0x00;
    if(in == "KEY_S")
        return 0x01;
    if(in == "KEY_D")
        return 0x02;
    if(in == "KEY_F")
        return 0x03;
    if(in == "KEY_H")
        return 0x04;
    if(in == "KEY_G")
        return 0x05;
    if(in == "KEY_Z")
        return 0x06;
    if(in == "KEY_X")
        return 0x07;
    if(in == "KEY_C")
        return 0x08;
    if(in == "KEY_V")
        return 0x09;
    if(in == "KEY_B")
        return 0x0B;
    if(in == "KEY_Q")
        return 0x0C;
    if(in == "KEY_W")
        return 0x0D;
    if(in == "KEY_E")
        return 0x0E;
    if(in == "KEY_R")
        return 0x0F;
    if(in == "KEY_Y")
        return 0x10;
    if(in == "KEY_T")
        return 0x11;
    if(in == "KEY_1")
        return 0x12;
    if(in == "KEY_2")
        return 0x13;
    if(in == "KEY_3")
        return 0x14;
    if(in == "KEY_4")
        return 0x15;
    if(in == "KEY_6")
        return 0x16;
    if(in == "KEY_5")
        return 0x17;
    if(in == "KEY_EQUAL")
        return 0x18;
    if(in == "KEY_9")
        return 0x19;
    if(in == "KEY_7")
        return 0x1A;
    if(in == "KEY_MINUS")
        return 0x1B;
    if(in == "KEY_8")
        return 0x1C;
    if(in == "KEY_0")
        return 0x1D;
    if(in == "KEY_RIGHT_BRACE")
        return 0x1E;
    if(in == "KEY_O")
        return 0x1F;
    if(in == "KEY_U")
        return 0x20;
    if(in == "KEY_LEFT_BRACE")
        return 0x21;
    if(in == "KEY_I")
        return 0x22;
    if(in == "KEY_P")
        return 0x23;
    if(in == "KEY_L")
        return 0x25;
    if(in == "KEY_J")
        return 0x26;
    if(in == "KEY_QUOTE")
        return 0x27;
    if(in == "KEY_K")
        return 0x28;
    if(in == "KEY_SEMICOLON")
        return 0x29;
    if(in == "KEY_BACKSLASH")
        return 0x2A;
    if(in == "KEY_COMMA")
        return 0x2B;
    if(in == "KEY_SLASH")
        return 0x2C;
    if(in == "KEY_N")
        return 0x2D;
    if(in == "KEY_M")
        return 0x2E;
    if(in == "KEY_PERIOD")
        return 0x2F;
    if(in == "KEY_TILDE")
        return 0x32;
    if(in == "KEYPAD_PERIOD")
        return 0x41;
    if(in == "KEYPAD_ASTERIX")
        return 0x43;
    if(in == "KEYPAD_PLUS")
        return 0x45;
    if(in == "KEY_NUM_LOCK")
        return 0x47;
    if(in == "KEYPAD_SLASH")
        return 0x4B;
    if(in == "KEYPAD_ENTER")
        return 0x4C;
    if(in == "KEYPAD_MINUS")
        return 0x4E;
    if(in == "KEYPAD_EQUALS")
        return 0x51;
    if(in == "KEYPAD_0")
        return 0x52;
    if(in == "KEYPAD_1")
        return 0x53;
    if(in == "KEYPAD_2")
        return 0x54;
    if(in == "KEYPAD_3")
        return 0x55;
    if(in == "KEYPAD_4")
        return 0x56;
    if(in == "KEYPAD_5")
        return 0x57;
    if(in == "KEYPAD_6")
        return 0x58;
    if(in == "KEYPAD_7")
        return 0x59;
    if(in == "KEYPAD_8")
        return 0x5B;
    if(in == "KEYPAD_9")
        return 0x5C;
    if(in == "KEY_ENTER")
        return 0x24;
    if(in == "KEY_TAB")
        return 0x30;
    if(in == "KEY_SPACE")
        return 0x31;
    if(in == "KEY_BACKSPACE")
        return 0x33;
    if(in == "KEY_ESC")
        return 0x35;
    if(in == "KEY_CAPS_LOCK")
        return 0x39;
    if(in == "KEY_F1")
        return 0x7A;
    if(in == "KEY_F2")
        return 0x78;
    if(in == "KEY_F3")
        return 0x63;
    if(in == "KEY_F4")
        return 0x76;
    if(in == "KEY_F5")
        return 0x60;
    if(in == "KEY_F6")
        return 0x61;
    if(in == "KEY_F7")
        return 0x62;
    if(in == "KEY_F8")
        return 0x64;
    if(in == "KEY_F9")
        return 0x65;
    if(in == "KEY_F10")
        return 0x6D;
    if(in == "KEY_F11")
        return 0x67;
    if(in == "KEY_F12")
        return 0x6F;
    if(in == "KEY_MEDIA_VOLUME_INC")
        return 0x48;
    if(in == "KEY_MEDIA_VOLUME_DEC")
        return 0x49;
    if(in == "KEY_MEDIA_MUTE")
        return 0x4A;
    if(in == "KEY_HOME")
        return 0x73;
    if(in == "KEY_END")
        return 0x77;
    if(in == "KEY_PAGEUP")
        return 0x74;
    if(in == "KEY_DELETE")
        return 0x75;
    if(in == "KEY_PAGEDOWN")
        return 0x79;
    if(in == "KEY_LEFT")
        return 0x7B;
    if(in == "KEY_RIGHT")
        return 0x7C;
    if(in == "KEY_DOWN")
        return 0x7D;
    if(in == "KEY_UP")
        return 0x7E;
    qDebug() << "NOT FOUND: " << in;
    /*
    kVK_Function                  = 0x3F,
    kVK_F17                       = 0x40,
    kVK_F18                       = 0x4F,
    kVK_F19                       = 0x50,
    kVK_F20                       = 0x5A,
    kVK_F13                       = 0x69,
    kVK_F16                       = 0x6A,
    kVK_F14                       = 0x6B,
    kVK_F15                       = 0x71,
    kVK_Help                      = 0x72,
    */

    return 0xFFFF;
}

#endif
;
