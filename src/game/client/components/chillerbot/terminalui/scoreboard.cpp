// ChillerDragon 2023 - chillerbot

#include <engine/client/serverbrowser.h>
#include <game/client/components/controls.h>
#include <game/client/gameclient.h>

#include <base/chillerbot/curses_colors.h>
#include <base/terminalui.h>

#include "terminalui.h"

#if defined(CONF_CURSES_CLIENT)

void CTerminalUI::RenderScoreboard(int Team, CTermWindow *pWin)
{
	if(!m_ScoreboardActive)
		return;

	int NumRenderScoreIDs = 0;

	int mx = getmaxx(pWin->m_pCursesWin);
	int my = getmaxy(pWin->m_pCursesWin);
	int offY = 5;
	int offX = 40;
	int width = minimum(128, mx - 3);
	if(mx < offX + 2 + width)
		offX = 2;
	if(my < 60)
		offY = 2;

	for(int i = 0; i < MAX_CLIENTS; i++)
	{
		// make sure that we render the correct team
		const CNetObj_PlayerInfo *pInfo = m_pClient->m_Snap.m_apInfoByDDTeamScore[i];
		if(!pInfo || pInfo->m_Team != Team)
			continue;

		NumRenderScoreIDs++;
		if(offY + i > my - 8)
			break;
	}
	int height = minimum(NumRenderScoreIDs, my - 5);
	if(height < 1)
		return;

	pWin->DrawBorders(offX, offY - 1, width, height + 2);
	// DrawBorders(pWin, 10, 5, 10, 5);

	int k = 0;
	for(int i = 0; i < MAX_CLIENTS; i++)
	{
		// if(rendered++ < 0) continue;

		// make sure that we render the correct team
		const CNetObj_PlayerInfo *pInfo = m_pClient->m_Snap.m_apInfoByDDTeamScore[i];
		if(!pInfo || pInfo->m_Team != Team)
			continue;

		// dbg_msg("scoreboard", "i=%d name=%s", i, m_pClient->m_aClients[pInfo->m_ClientID].m_aName);

		char aScore[64];

		// score
		if(m_pClient->m_GameInfo.m_TimeScore && g_Config.m_ClDDRaceScoreBoard)
		{
			if(pInfo->m_Score == -9999)
				aScore[0] = 0;
			else
				str_time((int64_t)abs(pInfo->m_Score) * 100, TIME_HOURS, aScore, sizeof(aScore));
		}
		else
			str_format(aScore, sizeof(aScore), "%d", clamp(pInfo->m_Score, -999, 99999));

		char aLine[1024];
		char aBuf[1024];
		size_t NameSize;
		size_t NameCount;
		size_t ClanSize;
		size_t ClanCount;
		str_utf8_stats(m_pClient->m_aClients[pInfo->m_ClientID].m_aName, 60, 60, &NameSize, &NameCount);
		str_utf8_stats(m_pClient->m_aClients[pInfo->m_ClientID].m_aClan, 60, 60, &ClanSize, &ClanCount);
		str_format(aBuf, sizeof(aBuf),
			"%8s| %-*s | %-*s |",
			aScore,
			20 + (NameSize - NameCount),
			m_pClient->m_aClients[pInfo->m_ClientID].m_aName,
			20 + (ClanSize - ClanCount),
			m_pClient->m_aClients[pInfo->m_ClientID].m_aClan);
		str_format(aLine, sizeof(aLine), "|%-*s|", (width - 2) + (NameSize - NameCount) + (ClanSize - ClanCount), aBuf);
		if(sizeof(aBuf) > (unsigned long)(mx - 2))
			aLine[mx - 2] = '\0'; // ensure no line wrapping
		mvwprintw(pWin->m_pCursesWin, offY + k, offX, "%s", aLine);

		if(k++ >= height - 1)
			break;
	}
}

#endif
