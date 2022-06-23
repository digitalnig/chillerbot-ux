#include "curses_colors.h"

#if defined(CONF_CURSES_CLIENT)

#include <base/curses.h>

int rgb_to_text_color_pair(int r, int g, int b)
{
	// FILE *pFile = fopen("debug.txt", "a");
	// fprintf(pFile, "R G B %d %d %d\n", r, g, b);
	// fclose(pFile);
	if(r > 100 && g > 100 && b < 130)
		return YELLOW_ON_BLACK;
	if(r > 100 && g < 100 && b < 100)
		return RED_ON_BLACK;
	if(r < 100 && g < 100 && b > 100)
		return BLUE_ON_BLACK;
	return WHITE_ON_BLACK;
}

void init_curses_colors()
{
	init_pair(WHITE_ON_BLACK, COLOR_WHITE, COLOR_BLACK);
	init_pair(CYAN_ON_BLACK, COLOR_CYAN, COLOR_BLACK);
	init_pair(RED_ON_BLACK, COLOR_RED, COLOR_BLACK);
	init_pair(GREEN_ON_BLACK, COLOR_GREEN, COLOR_BLACK);
	init_pair(BLUE_ON_BLACK, COLOR_BLUE, COLOR_BLACK);
	init_pair(YELLOW_ON_BLACK, COLOR_YELLOW, COLOR_BLACK);
}

#endif
