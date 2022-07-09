// chillerbot-ux reply to ping

#include "engine/shared/protocol.h"
#include <engine/client/notifications.h>
#include <engine/config.h>
#include <engine/console.h>
#include <engine/graphics.h>
#include <engine/keys.h>
#include <engine/textrender.h>
#include <game/client/animstate.h>
#include <game/client/components/camera.h>
#include <game/client/components/chat.h>
#include <game/client/components/chillerbot/chathelper.h>
#include <game/client/components/chillerbot/version.h>
#include <game/client/components/controls.h>
#include <game/client/components/menus.h>
#include <game/client/components/voting.h>
#include <game/client/gameclient.h>
#include <game/client/prediction/entities/character.h>
#include <game/client/race.h>
#include <game/client/render.h>
#include <game/generated/client_data.h>
#include <game/generated/protocol.h>
#include <game/version.h>

#include "replytoping.h"

// where are you

bool CReplyToPing::Where()
{
	if(str_find_nocase(m_pMessage, "where are you") || str_find_nocase(m_pMessage, "where r u") || str_find_nocase(m_pMessage, "where r yo") ||
		str_find_nocase(m_pMessage, "where u") ||
		str_find_nocase(m_pMessage, "wo bist"))
	{
		for(auto &Client : ChatHelper()->GameClient()->m_aClients)
		{
			if(!Client.m_Active)
				continue;
			if(str_comp(Client.m_aName, m_pMessageAuthor))
				continue;

			// TODO: dont get current dummy but the pinged dummy
			CCharacter *pChar = ChatHelper()->GameClient()->m_GameWorld.GetCharacterByID(ChatHelper()->GameClient()->m_aLocalIDs[g_Config.m_ClDummy]);
			if(!pChar)
				continue;
			vec2 Self = pChar->m_Pos;
			vec2 Other = Client.m_RenderPos;
			float distY = abs(Self.y - Other.y);
			float distX = abs(Self.x - Other.x);
			// instead of some unimaginable long distance number in tiles
			// prefer saying "finish" or "end" without any relation to the other player
			// since it does not matter in this case
			if(distX > 50 * 32 && distY > 50 * 32)
			{
				if(ChatHelper()->GameClient()->m_Snap.m_pLocalCharacter && CRaceHelper::IsClusterRangeFinish(ChatHelper()->GameClient(), ChatHelper()->GameClient()->m_PredictedChar.m_Pos, 32))
				{
					str_format(m_pResponse, m_SizeOfResponse, "%s I am at the finish line", m_pMessageAuthor);
					return true;
				}
				else if(ChatHelper()->GameClient()->m_Snap.m_pLocalCharacter && CRaceHelper::IsClusterRangeStart(ChatHelper()->GameClient(), ChatHelper()->GameClient()->m_PredictedChar.m_Pos, 32))
				{
					str_format(m_pResponse, m_SizeOfResponse, "%s I am at start", m_pMessageAuthor);
					return true;
				}
			}
			if(distX < 5 * 32 && distY < 5 * 32)
			{
				if(distX > distY)
				{
					if(Self.x > Other.x)
					{
						str_format(m_pResponse, m_SizeOfResponse, "%s i am literally next to you (on your right)", m_pMessageAuthor);
						return true;
					}
					else
					{
						str_format(m_pResponse, m_SizeOfResponse, "%s i am literally next to you (on your left)", m_pMessageAuthor);
						return true;
					}
				}
				else
				{
					if(Self.y > Other.y)
					{
						str_format(m_pResponse, m_SizeOfResponse, "%s i am literally next to you (below you)", m_pMessageAuthor);
						return true;
					}
					else
					{
						str_format(m_pResponse, m_SizeOfResponse, "%s i am literally next to you (above you)", m_pMessageAuthor);
						return true;
					}
				}
			}
			else if(distY > distX * 8)
			{
				if(Self.y > Other.y)
				{
					str_format(m_pResponse, m_SizeOfResponse, "%s below you (%d tiles)", m_pMessageAuthor, (int)(distY / 32));
					return true;
				}
				else
				{
					str_format(m_pResponse, m_SizeOfResponse, "%s above you (%d tiles)", m_pMessageAuthor, (int)(distY / 32));
					return true;
				}
			}
			else if(Self.x > Other.x)
			{
				if(distY < 15 * 32)
				{
					str_format(m_pResponse, m_SizeOfResponse, "%s i am on your right (%d tiles away)", m_pMessageAuthor, (int)(distX / 32));
					return true;
				}
				else if(Self.y > Other.y)
				{
					str_format(m_pResponse, m_SizeOfResponse, "%s i am on your right (%d tiles away) and %d tiles below you", m_pMessageAuthor, (int)(distX / 32), (int)(distY / 32));
					return true;
				}
				else
				{
					str_format(m_pResponse, m_SizeOfResponse, "%s i am on your right (%d tiles away) and %d tiles above you", m_pMessageAuthor, (int)(distX / 32), (int)(distY / 32));
					return true;
				}
			}
			else
			{
				if(distY < 15 * 32)
				{
					str_format(m_pResponse, m_SizeOfResponse, "%s i am on your left (%d tiles away)", m_pMessageAuthor, (int)(distX / 32));
					return true;
				}
				else if(Self.y > Other.y)
				{
					str_format(m_pResponse, m_SizeOfResponse, "%s i am on your left (%d tiles away) and %d tiles below you", m_pMessageAuthor, (int)(distX / 32), (int)(distY / 32));
					return true;
				}
				else
				{
					str_format(m_pResponse, m_SizeOfResponse, "%s i am on your left (%d tiles away) and %d tiles above you", m_pMessageAuthor, (int)(distX / 32), (int)(distY / 32));
					return true;
				}
			}
		}
		if(ChatHelper()->GameClient()->m_Snap.m_pLocalCharacter && CRaceHelper::IsNearFinish(ChatHelper()->GameClient(), ChatHelper()->GameClient()->m_PredictedChar.m_Pos, 32))
			str_format(m_pResponse, m_SizeOfResponse, "%s I am at the finish line", m_pMessageAuthor);
		else if(ChatHelper()->GameClient()->m_Snap.m_pLocalCharacter && CRaceHelper::IsNearStart(ChatHelper()->GameClient(), ChatHelper()->GameClient()->m_PredictedChar.m_Pos, 32))
			str_format(m_pResponse, m_SizeOfResponse, "%s I am at start", m_pMessageAuthor);
		else
			str_format(m_pResponse, m_SizeOfResponse, "%s no idea. Where are you?", m_pMessageAuthor);
		return true;
	}
	return false;
}
