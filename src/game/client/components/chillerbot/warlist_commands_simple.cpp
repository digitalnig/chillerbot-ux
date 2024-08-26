// ChillerDragon 2021 - chillerbot ux

#include <engine/config.h>
#include <engine/shared/linereader.h>
#include <engine/textrender.h>
#include <game/client/gameclient.h>

#include <base/system.h>

#include "warlist.h"

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
		m_pClient->m_Chat.AddLine(-2, 0, "!addwar <folder> <name>");
		m_pClient->m_Chat.AddLine(-2, 0, "!addteam <folder> <name>");
		m_pClient->m_Chat.AddLine(-2, 0, "!peace <folder>");
		m_pClient->m_Chat.AddLine(-2, 0, "!war <folder>");
		m_pClient->m_Chat.AddLine(-2, 0, "!team <folder>");
		m_pClient->m_Chat.AddLine(-2, 0, "!unfriend <folder>");
		m_pClient->m_Chat.AddLine(-2, 0, "!addreason <folder> [--force] <reason>");
		m_pClient->m_Chat.AddLine(-2, 0, "!search <name>");
		m_pClient->m_Chat.AddLine(-2, 0, "!create <war|team|neutral|traitor> <folder> [name]");
	}
	else if(!str_comp(pCmd, "create")) // "create <war|team|neutral|traitor> <folder> [name]"
	{
		m_pClient->m_Chat.AddLine(-2, 0, "Error: create only works in advanced warlist mode");
		return true;
	}
	else if(!str_comp(pCmd, "addwar")) // "addwar <folder> <name can contain spaces>"
	{
		if(NumArgs < 1)
		{
			m_pClient->m_Chat.AddLine(-2, 0, "Error: missing argument <name>");
			return true;
		}

		if(!Storage()->CreateFolder("chillerbot/warlist/war", IStorage::TYPE_SAVE))
		{
			m_pClient->m_Chat.AddLine(-2, 0, "Error: failed to create war folder");
			return true;
		}
		if(!Storage()->CreateFolder("chillerbot/warlist/war/war", IStorage::TYPE_SAVE))
		{
			m_pClient->m_Chat.AddLine(-2, 0, "Error: failed to create war/war folder");
			return true;
		}

		AddWar("war", pRawArgLine);
	}
	else if(!str_comp(pCmd, "addteam")) // "addteam <folder> <name can contain spaces>"
	{
		m_pClient->m_Chat.AddLine(-2, 0, "Error: addteam only works in advanced warlist mode");
		return true;
	}
	else if(!str_comp(pCmd, "addtraitor")) // "addtraitor <folder> <name can contain spaces>"
	{
		m_pClient->m_Chat.AddLine(-2, 0, "Error: addtraitor only works in advanced warlist mode");
		return true;
	}
	else if(!str_comp(pCmd, "peace")) // "peace <folder>"
	{
		m_pClient->m_Chat.AddLine(-2, 0, "Error: peace only works in advanced warlist mode");
		return true;
	}
	else if(!str_comp(pCmd, "unfriend")) // "unfriend <folder>"
	{
		m_pClient->m_Chat.AddLine(-2, 0, "Error: unfriend only works in advanced warlist mode");
		return true;
	}
	else if(!str_comp(pCmd, "team")) // "team <folder>"
	{
		m_pClient->m_Chat.AddLine(-2, 0, "Error: team only works in advanced warlist mode");
		return true;
	}
	else if(!str_comp(pCmd, "war")) // "war <folder>"
	{
		m_pClient->m_Chat.AddLine(-2, 0, "Error: war only works in advanced warlist mode");
		return true;
	}
	else if(!str_comp(pCmd, "addreason")) // "addreason <folder> <reason can contain spaces>"
	{
		m_pClient->m_Chat.AddLine(-2, 0, "Error: addreason only works in advanced warlist mode");
		return true;
	}
	else
	{
		return false;
	}
	return true;
}
