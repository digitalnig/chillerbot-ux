// ChillerDragon 2023 - chillerbot ux

#include <game/client/components/chillerbot/chillerbotux.h>
#include <game/client/gameclient.h>

#include <cinttypes>
#include <engine/shared/protocol.h>

#include <game/client/components/chat.h>

#include "chatcommand.h"

void CChatCommand::OnServerMsg(const char *pMsg)
{
}

void CChatCommand::OnChatMsg(int ClientID, int Team, const char *pMsg)
{
	if(!pMsg[1])
		return;
	if(pMsg[0] == '.' || pMsg[0] == ':' || pMsg[0] == '!' || pMsg[0] == '#' || pMsg[0] == '$' || pMsg[0] == '/')
		if(ParseChatCmd(pMsg[0], ClientID, Team, pMsg + 1))
			return;

	OnNoChatCommandMatches(ClientID, Team, pMsg);
}

void CChatCommand::OnNoChatCommandMatches(int ClientID, int Team, const char *pMsg)
{
	// ux components

	// m_pClient->m_WarList.OnNoChatCommandMatches(ClientID, Team, pMsg);

	// zx components
}

bool CChatCommand::OnChatCmd(char Prefix, int ClientID, int Team, const char *pCmd, int NumArgs, const char **ppArgs)
{
	bool match = false;
	// ux components

	if(m_pClient->m_WarList.OnChatCmd(Prefix, ClientID, Team, pCmd, NumArgs, ppArgs))
		match = true;

	// zx components

	return match;
}

bool CChatCommand::ParseChatCmd(char Prefix, int ClientID, int Team, const char *pCmdWithArgs)
{
	const int MAX_ARG_LEN = 256;
	char aCmd[MAX_ARG_LEN];
	int i;
	for(i = 0; pCmdWithArgs[i] && i < MAX_ARG_LEN; i++)
	{
		if(pCmdWithArgs[i] == ' ')
			break;
		aCmd[i] = pCmdWithArgs[i];
	}
	aCmd[i] = '\0';
	int ROffset = m_pClient->m_ChatHelper.ChatCommandGetROffset(aCmd);

	// max 8 args of 128 len each
	const int MAX_ARGS = 16;
	char **ppArgs = new char *[MAX_ARGS];
	for(int x = 0; x < MAX_ARGS; ++x)
	{
		ppArgs[x] = new char[MAX_ARG_LEN];
		ppArgs[x][0] = '\0';
	}
	int NumArgs = 0;
	int k = 0;
	while(pCmdWithArgs[i])
	{
		if(k + 1 >= MAX_ARG_LEN)
		{
			dbg_msg("chillerbot", "ERROR: chat command has too long arg");
			break;
		}
		if(NumArgs + 1 >= MAX_ARGS)
		{
			dbg_msg("chillerbot", "ERROR: chat command has too many args");
			break;
		}
		if(pCmdWithArgs[i] == ' ')
		{
			// do not delimit on space
			// if we reached the r parameter
			if(NumArgs == ROffset)
			{
				// strip spaces from the beggining
				// add spaces in the middle and end
				if(ppArgs[NumArgs][0])
				{
					ppArgs[NumArgs][k] = pCmdWithArgs[i];
					k++;
					i++;
					continue;
				}
			}
			else if(ppArgs[NumArgs][0])
			{
				ppArgs[NumArgs][k] = '\0';
				k = 0;
				NumArgs++;
			}
			i++;
			continue;
		}
		ppArgs[NumArgs][k] = pCmdWithArgs[i];
		k++;
		i++;
	}
	if(ppArgs[NumArgs][0])
	{
		ppArgs[NumArgs][k] = '\0';
		NumArgs++;
	}

	// char aArgsStr[128];
	// aArgsStr[0] = '\0';
	// for(i = 0; i < NumArgs; i++)
	// {
	// 	if(aArgsStr[0] != '\0')
	// 		str_append(aArgsStr, ", ", sizeof(aArgsStr));
	// 	str_append(aArgsStr, ppArgs[i], sizeof(aArgsStr));
	// }

	// char aBuf[512];
	// str_format(aBuf, sizeof(aBuf), "got cmd '%s' with %d args: %s", aCmd, NumArgs, aArgsStr);
	// Say(aBuf);
	bool match = OnChatCmd(Prefix, ClientID, Team, aCmd, NumArgs, (const char **)ppArgs);
	for(int x = 0; x < 8; ++x)
		delete[] ppArgs[x];
	delete[] ppArgs;
	return match;
}

void CChatCommand::OnMessage(int MsgType, void *pRawMsg)
{
	if(MsgType == NETMSGTYPE_SV_CHAT)
	{
		CNetMsg_Sv_Chat *pMsg = (CNetMsg_Sv_Chat *)pRawMsg;
		if(pMsg->m_ClientID == -1 && pMsg->m_Team < 2)
			OnServerMsg(pMsg->m_pMessage);
		else
			OnChatMsg(pMsg->m_ClientID, pMsg->m_Team, pMsg->m_pMessage);
	}
}
