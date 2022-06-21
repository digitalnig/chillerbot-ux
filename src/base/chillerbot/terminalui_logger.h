#ifndef BASE_CHILLERBOT_TERMINALUI_LOGGER_H
#define BASE_CHILLERBOT_TERMINALUI_LOGGER_H

#include "../logger.h"

#include "../color.h"
#include "../system.h"
#include "../terminalui.h"

#include <atomic>
#include <cstdio>

#if defined(CONF_FAMILY_WINDOWS)
#define WIN32_LEAN_AND_MEAN
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0501 /* required for mingw to get getaddrinfo to work */
#include <windows.h>
#else
#include <unistd.h>
#endif

void CursesLogPush(const char *pStr)
{
#if defined(CONF_CURSES_CLIENT)
	curses_log_push(pStr);
#else
	puts(pStr);
#endif
}

class CTerminalUILogger : public ILogger
{
	ASYNCIO *m_pAio;
	// bool m_AnsiTruecolor;
	bool m_Close;

public:
	CTerminalUILogger(IOHANDLE File, bool AnsiTruecolor, bool Close) :
		m_pAio(aio_new(File)),
		m_AnsiTruecolor(AnsiTruecolor),
		m_Close(Close)
	{
	}
	void Log(const CLogMessage *pMessage) override
	{
		aio_lock(m_pAio);

		// TODO: use curses wattron for colors

		// if(m_AnsiTruecolor)
		// {
		// 	// https://en.wikipedia.org/w/index.php?title=ANSI_escape_code&oldid=1077146479#24-bit
		// 	char aAnsi[32];
		// 	if(pMessage->m_HaveColor)
		// 	{
		// 		str_format(aAnsi, sizeof(aAnsi),
		// 			"\x1b[38;2;%d;%d;%dm",
		// 			pMessage->m_Color.r,
		// 			pMessage->m_Color.g,
		// 			pMessage->m_Color.b);
		// 		CursesLogPush(aAnsi);
		// 	}
		// }
		CursesLogPush(pMessage->m_aLine);
		// if(m_AnsiTruecolor && pMessage->m_HaveColor)
		// {
		// 	const char aResetColor[] = "\x1b[0m";
		// 	CursesLogPush(aResetColor); // reset
		// }
		aio_unlock(m_pAio);
	}
	~CTerminalUILogger()
	{
		if(m_Close)
		{
			aio_close(m_pAio);
		}
		aio_wait(m_pAio);
		aio_free(m_pAio);
	}
	void GlobalFinish() override
	{
		if(m_Close)
		{
			aio_close(m_pAio);
		}
		aio_wait(m_pAio);
	}
};

#endif
