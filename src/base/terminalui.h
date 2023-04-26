#ifndef BASE_TERMINALUI_H
#define BASE_TERMINALUI_H

#include "system.h"

#if defined(CONF_CURSES_CLIENT)

#include <base/curses.h>
#include <base/math.h>

#define CHILLER_LOGGER_WIDTH 1024 * 4
#define CHILLER_LOGGER_HEIGHT 2048

#define INFO_WIN_HEIGHT 3

class CTermWindow
{
	char m_aTextTopYellow[128];
	char m_aTextTop[128];

public:
	CTermWindow();
	void SetTextTopLeftYellow(const char *pText);
	void SetTextTopLeft(const char *pText);
	void DrawBorders();
	void DrawBorders(int x, int y, int w, int h);

	WINDOW *m_pCursesWin;
};

class CInputWindow : public CTermWindow
{
public:
	CInputWindow()
	{
		CTermWindow();
		m_Search = false;
		m_CurserOffset = 0;
		Open();
		m_Menu = false; // TODO: set to true when it closes fine
		m_SelectedMenuItem = MENU_ITEM_BROWSER;
	}
	bool m_Search;
	int m_CurserOffset;
	int m_Height;
	bool m_Active;
	bool m_Menu;
	int m_SelectedMenuItem;
	enum
	{
		MENU_ITEM_BROWSER,
		MENU_ITEM_QUIT,
		NUM_MENU_ITEMS,
	};
	void CloseMenu()
	{
		if(!IsMenu())
			return;
		dbg_msg("chiller", "closing menu");
		m_Menu = false;
		refresh();
		wclear(m_pCursesWin);
		refresh();
		Close();
	}
	void Open()
	{
		m_Height = 3;
		m_Active = true;
		CloseMenu();
	}
	void Close()
	{
		m_Height = 0;
		m_Active = false;
		CloseMenu();
	}
	void NextMenuItem()
	{
		if(!IsMenu())
			return;
		m_SelectedMenuItem = clamp(m_SelectedMenuItem + 1, 0, (int)NUM_MENU_ITEMS);
		DrawBorders();
		refresh();
	}
	void PrevMenuItem()
	{
		if(!IsMenu())
			return;
		m_SelectedMenuItem = clamp(m_SelectedMenuItem - 1, 0, (int)NUM_MENU_ITEMS);
		DrawBorders();
		refresh();
	}
	int Item() { return m_SelectedMenuItem; }
	bool IsActive() { return m_Active; }
	bool IsMenu() { return m_Menu; }
	bool IsSearch() { return m_Search; }
	void SetSearch(bool Search)
	{
		m_Search = Search;
		m_CurserOffset = Search ? 3 : 0;
	}
	void DrawBorders();
};

extern CTermWindow g_LogWindow;
extern CTermWindow g_GameWindow;
extern CTermWindow g_InfoWin;
extern CInputWindow g_InputWin;

extern int g_ParentX;
extern int g_ParentY;
extern int g_NewX;
extern int g_NewY;
extern bool g_TriggerResize;
extern char g_aInfoStr[1024];
extern char g_aInfoStr2[1024];
extern char g_aInputStr[1024];
extern bool gs_NeedLogDraw;
extern int gs_LogsPushed;
/*
	gs_LogScroll

	print offset of the log.
	to keep track of scrolling to older pages.
*/
extern int gs_LogScroll;
extern int gs_LogNumFilled;
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

/*
	set_curses_log_scroll

	set the bottom offset of the log scroll
	0 is latest message
	and CHILLER_LOGGER_WIDTH - (terminal height)
	is oldest message
*/
int set_curses_log_scroll(int offset);
int get_curses_log_scroll();
int scroll_curses_log(int offset);
void curses_refresh_windows();
void curses_log_push(const char *pStr, const SLOG_COLOR *pColor = nullptr);
// void curses_logf(const char *sys, const char *fmt, ...);

#endif

#endif
