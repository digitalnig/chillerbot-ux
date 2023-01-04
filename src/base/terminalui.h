#ifndef BASE_TERMINALUI_H
#define BASE_TERMINALUI_H

#include "system.h"

#if defined(CONF_CURSES_CLIENT)

#include <base/curses.h>

#define CHILLER_LOGGER_WIDTH 1024 * 4
#define CHILLER_LOGGER_HEIGHT 128

class CTermWindow
{
	char m_aTextTop[128];

public:
	CTermWindow();
	void SetTextTop(const char *pText);
	void DrawBorders();
	void DrawBorders(int x, int y, int w, int h);

	WINDOW *m_pCursesWin;
};

extern CTermWindow g_LogWindow;
extern CTermWindow g_GameWindow;
extern CTermWindow g_InfoWin;
extern CTermWindow g_InputWin;

extern int g_ParentX;
extern int g_ParentY;
extern int g_NewX;
extern int g_NewY;
extern char g_aInfoStr[1024];
extern char g_aInfoStr2[1024];
extern char g_aInputStr[1024];
extern bool gs_NeedLogDraw;
extern int gs_LogsPushed;
extern IOHANDLE gs_Logfile;

struct SLOG_COLOR
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

class CCursesLogMsg
{
public:
	CCursesLogMsg()
	{
		m_aMessage[0] = '\0';
		m_HaveColor = false;
		m_Color.r = 0;
		m_Color.g = 0;
		m_Color.b = 0;
	}
	char m_aMessage[CHILLER_LOGGER_WIDTH];
	bool m_HaveColor;
	SLOG_COLOR m_Color;
};

void curses_init();
void log_draw();
void curses_refresh_windows();
void curses_log_push(const char *pStr, const SLOG_COLOR *pColor = nullptr);
// void curses_logf(const char *sys, const char *fmt, ...);

#endif

#endif
