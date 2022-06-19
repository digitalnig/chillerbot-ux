#ifndef GAME_CLIENT_RACE_H
#define GAME_CLIENT_RACE_H

#include <base/vmath.h>

class CRaceHelper
{
public:
	static int ms_aFlagIndex[2];

	// these functions return the time in milliseconds, time -1 is invalid
	static int TimeFromSecondsStr(const char *pStr); // x.xxx
	static int TimeFromStr(const char *pStr); // x minute(s) x.xxx second(s)
	static int TimeFromFinishMessage(const char *pStr, char *pNameBuf, int NameBufSize); // xxx finished in: x minute(s) x.xxx second(s)

	static bool IsStart(class CGameClient *pClient, vec2 Prev, vec2 Pos);
	static bool IsFinish(class CGameClient *pClient, vec2 Pos1, vec2 Pos2);
	/*
		IsNearFinish

		Checks every tiles on the border of the square
		The square is located at Pos and has the size RadiusInTiles

		It does not cover tiles inside of the square. So making the radius too big
		might miss the target.

		<----- radius ---->

		+-----------------+
		|                 |
		|                 |
		|                 |
		|                 |
		|       pos       |
		|                 |
		|                 |
		|                 |
		+-----------------+
	*/
	static bool IsNearFinish(class CGameClient *pClient, vec2 Pos, int RadiusInTiles = 4);
	/*
		IsNearStart

		Checks every tiles on the border of the square
		The square is located at Pos and has the size RadiusInTiles

		It does not cover tiles inside of the square. So making the radius too big
		might miss the target.

		<----- radius ---->

		+-----------------+
		|                 |
		|                 |
		|                 |
		|                 |
		|       pos       |
		|                 |
		|                 |
		|                 |
		+-----------------+
	*/
	static bool IsNearStart(class CGameClient *pClient, vec2 Pos, int RadiusInTiles = 4);
	/*
		IsClusterRangeFinish

		Recommended for bigger areas.
		For areas smaller than 10 tiles use IsNearFinish instead.

		Calls IsNearFinish internally.
		It creates multiple 4x4 check boxes to cover the full given are.
		Around position Pos with the size of RadiusInTiles.
		Only indecies on the border are looked at.

		<----- radius ---->

		+--+ +--+ +--+ +--+
		|  | |  | |  | |  |
		+--+ +--+ +--+ +--+
		+--+ +--+ +--+ +--+
		|  | |  | |  | |  |
		+--+ +--+ +--+ +--+
		+--+ +--+ +--+ +--+
		|  | |  | |  | |  |
		+--+ +--+ +--+ +--+
	*/
	static bool IsClusterRangeFinish(class CGameClient *pClient, vec2 Pos, int RadiusInTiles = 10);
	/*
		IsClusterRangeStart

		Recommended for bigger areas.
		For areas smaller than 10 tiles use IsNearStart instead.

		Calls IsNearStart internally.
		It creates multiple 4x4 check boxes to cover the full given are.
		Around position Pos with the size of RadiusInTiles.
		Only indecies on the border are looked at.

		<----- radius ---->

		+--+ +--+ +--+ +--+
		|  | |  | |  | |  |
		+--+ +--+ +--+ +--+
		+--+ +--+ +--+ +--+
		|  | |  | |  | |  |
		+--+ +--+ +--+ +--+
		+--+ +--+ +--+ +--+
		|  | |  | |  | |  |
		+--+ +--+ +--+ +--+
	*/
	static bool IsClusterRangeStart(class CGameClient *pClient, vec2 Pos, int RadiusInTiles = 10);
};

#endif // GAME_CLIENT_RACE_H
