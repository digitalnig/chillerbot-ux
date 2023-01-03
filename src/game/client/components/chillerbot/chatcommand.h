#ifndef GAME_CLIENT_COMPONENTS_CHILLERBOT_CHATCOMMAND_H
#define GAME_CLIENT_COMPONENTS_CHILLERBOT_CHATCOMMAND_H

#include <game/client/component.h>

class CChatCommand : public CComponent
{
	virtual void OnMessage(int MsgType, void *pRawMsg) override;

	void OnServerMsg(const char *pMsg);
	void OnChatMsg(int ClientID, int Team, const char *pMsg);
	void ParseChatCmd(char Prefix, int ClientID, const char *pCmdWithArgs);
	void OnChatCmd(char Prefix, int ClientID, const char *pCmd, int NumArgs, const char **ppArgs);

public:
	virtual int Sizeof() const override { return sizeof(*this); }
};

#endif
