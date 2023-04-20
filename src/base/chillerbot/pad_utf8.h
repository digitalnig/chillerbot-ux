#ifndef GAME_CLIENT_COMPONENTS_CHILLERBOT_TERMINALUI_PAD_UTF8_H
#define GAME_CLIENT_COMPONENTS_CHILLERBOT_TERMINALUI_PAD_UTF8_H

#include <base/system.h>

/*
    Function: str_pad_right_utf8

    Pad string with spaces supporting more than ascii
    But CJK lanuages (Chinese, Japanese, and Korean)
    are not supported. Because full width characters
    might be rendered too wide by your terminal emulator
*/
void str_pad_right_utf8(char *pStr, int size, int pad_len);

#endif
