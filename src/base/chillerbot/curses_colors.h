#ifndef BASE_CHILLERBOT_CURSES_COLORS_H
#define BASE_CHILLERBOT_CURSES_COLORS_H

#if defined(CONF_CURSES_CLIENT)

int rgb_to_text_color_pair(int r, int g, int b);
void init_curses_colors();

enum
{
	WHITE_ON_BLACK = 1,
	CYAN_ON_BLACK,
	RED_ON_BLACK,
	GREEN_ON_BLACK,
	BLUE_ON_BLACK,
	YELLOW_ON_BLACK,
};

#endif

#endif
