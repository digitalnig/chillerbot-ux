// ChillerDragon 2021 - chillerbot ux

#include <engine/config.h>
#include <engine/shared/linereader.h>
#include <engine/textrender.h>
#include <game/client/gameclient.h>

#include <base/system.h>

#include "warlist.h"

void CWarList::AddSimpleWar(const char *pName)
{
	if(!pName || pName[0] == '\0')
	{
		m_pClient->m_Chat.AddLine(-2, 0, "Error: missing argument <name>");
		return;
	}
	if(!Storage()->CreateFolder("chillerbot/warlist/war", IStorage::TYPE_SAVE))
	{
		m_pClient->m_Chat.AddLine(-2, 0, "Error: failed to create war folder");
		return;
	}
	if(!Storage()->CreateFolder("chillerbot/warlist/war/war", IStorage::TYPE_SAVE))
	{
		m_pClient->m_Chat.AddLine(-2, 0, "Error: failed to create war/war folder");
		return;
	}

	AddWar("war", pName);
}

void CWarList::RemoveSimpleWar(const char *pName)
{
	if(!RemoveWarNameFromVector("chillerbot/warlist/war/war", pName))
	{
		char aBuf[512];
		str_format(aBuf, sizeof(aBuf), "Name '%s' not found in the war list", pName);
		m_pClient->m_Chat.AddLine(-2, 0, aBuf);
		return;
	}
	if(!WriteWarNames("chillerbot/warlist/war/war"))
	{
		m_pClient->m_Chat.AddLine(-2, 0, "Error: failed to write war names");
	}
}

void CWarList::AddSimpleTeam(const char *pName)
{
	if(!pName || pName[0] == '\0')
	{
		m_pClient->m_Chat.AddLine(-2, 0, "Error: missing argument <name>");
		return;
	}
	if(!Storage()->CreateFolder("chillerbot/warlist/war", IStorage::TYPE_SAVE))
	{
		m_pClient->m_Chat.AddLine(-2, 0, "Error: failed to create war folder");
		return;
	}
	if(!Storage()->CreateFolder("chillerbot/warlist/war/war", IStorage::TYPE_SAVE))
	{
		m_pClient->m_Chat.AddLine(-2, 0, "Error: failed to create war/war folder");
		return;
	}

	AddTeam("war", pName);
}

void CWarList::RemoveSimpleTeam(const char *pName)
{
	if(!RemoveTeamNameFromVector("chillerbot/warlist/war/war", pName))
	{
		char aBuf[512];
		str_format(aBuf, sizeof(aBuf), "Name '%s' not found in the war list", pName);
		m_pClient->m_Chat.AddLine(-2, 0, aBuf);
		return;
	}
	if(!WriteTeamNames("chillerbot/warlist/war/war"))
	{
		m_pClient->m_Chat.AddLine(-2, 0, "Error: failed to write war names");
	}
}

bool CWarList::OnChatCmdSimple(char Prefix, int ClientId, int Team, const char *pCmd, int NumArgs, const char **ppArgs, const char *pRawArgLine)
{
	if(!str_comp(pCmd, "search")) // "search <name can contain spaces>"
	{
		m_pClient->m_Chat.AddLine(-2, 0, "Error: search only works in advanced warlist mode");
		return true;
	}
	else if(!str_comp(pCmd, "help"))
	{
		m_pClient->m_Chat.AddLine(-2, 0, "=== chillerbot-ux warlist ===");
		m_pClient->m_Chat.AddLine(-2, 0, "!addwar <name>");
		m_pClient->m_Chat.AddLine(-2, 0, "!war <name>");
		m_pClient->m_Chat.AddLine(-2, 0, "!peace <name>");
		m_pClient->m_Chat.AddLine(-2, 0, "!delwar <name>");
		m_pClient->m_Chat.AddLine(-2, 0, "!addteam <name>");
		m_pClient->m_Chat.AddLine(-2, 0, "!team <name>");
		m_pClient->m_Chat.AddLine(-2, 0, "!unfriend <name>");
		// m_pClient->m_Chat.AddLine(-2, 0, "!search <name>");
	}
	else if(!str_comp(pCmd, "create"))
	{
		m_pClient->m_Chat.AddLine(-2, 0, "Error: create only works in advanced warlist mode");
		return true;
	}
	else if(!str_comp(pCmd, "addwar")) // "addwar <name>"
	{
		AddSimpleWar(pRawArgLine);
		return true;
	}
	else if(!str_comp(pCmd, "addteam")) // "addteam <name>"
	{
		AddSimpleTeam(pRawArgLine);
		return true;
	}
	else if(!str_comp(pCmd, "peace")) // "peace <name>"
	{
		RemoveSimpleWar(pRawArgLine);
		return true;
	}
	else if(!str_comp(pCmd, "delwar")) // "delwar <name>"
	{
		RemoveSimpleWar(pRawArgLine);
		return true;
	}
	else if(!str_comp(pCmd, "team")) // "team <name>"
	{
		AddSimpleTeam(pRawArgLine);
		return true;
	}
	else if(!str_comp(pCmd, "delteam")) // "delteam <name>"
	{
		RemoveSimpleTeam(pRawArgLine);
		return true;
	}
	else if(!str_comp(pCmd, "unfriend")) // "unfriend <name>"
	{
		RemoveSimpleTeam(pRawArgLine);
		return true;
	}
	else if(!str_comp(pCmd, "war")) // "war <name>"
	{
		AddSimpleWar(pRawArgLine);
		return true;
	}
	else if(!str_comp(pCmd, "addreason")) // "addreason <folder> <reason can contain spaces>"
	{
		m_pClient->m_Chat.AddLine(-2, 0, "Error: addreason only works in advanced warlist mode");
		return true;
	}
	else if(!str_comp(pCmd, "addtraitor")) // "addtraitor <folder> <name can contain spaces>"
	{
		m_pClient->m_Chat.AddLine(-2, 0, "Error: addtraitor only works in advanced warlist mode");
		return true;
	}
	else
	{
		return false;
	}
	return true;
}
