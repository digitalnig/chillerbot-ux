#include "test.h"

#include <gtest/gtest.h>

#include <base/system.h>
#include <engine/shared/chillerbot/langparser.h>

TEST(ChillerBot, LangParserAskToAsk)
{
	CLangParser LangParser;
	bool AskToAsk = LangParser.IsAskToAsk("Can I ask you a question?");
	EXPECT_EQ(AskToAsk, true);
	AskToAsk = LangParser.IsAskToAsk("Kann ich dich was fragen?");
	EXPECT_EQ(AskToAsk, true);
}

TEST(ChillerBot, LangParserAskToAskStatement)
{
	CLangParser LangParser;
	bool AskToAsk = LangParser.IsAskToAsk("I have a question");
	EXPECT_EQ(AskToAsk, true);
	AskToAsk = LangParser.IsAskToAsk("Ich hab eine frage");
	EXPECT_EQ(AskToAsk, true);
}

TEST(ChillerBot, LangParserWantedToAskFalsePositive)
{
	CLangParser LangParser;
	bool AskToAsk = LangParser.IsAskToAsk("I wanted To ask you something, but then I did not care");
	EXPECT_EQ(AskToAsk, false);

	AskToAsk = LangParser.IsAskToAsk("I just wanted to ask how are you");
	EXPECT_EQ(AskToAsk, false);

	AskToAsk = LangParser.IsAskToAsk("I just wanted to ask");
	EXPECT_EQ(AskToAsk, false);
}

TEST(ChillerBot, LangParserWantedToAskFalsePositiveGer)
{
	CLangParser LangParser;
	bool AskToAsk = LangParser.IsAskToAsk("ich wollte dich fragen, doch dann wars mir egal");
	EXPECT_EQ(AskToAsk, false);

	AskToAsk = LangParser.IsAskToAsk("Ich wollt dich nur fragen wie es dir geht");
	EXPECT_EQ(AskToAsk, false);

	AskToAsk = LangParser.IsAskToAsk("das wollte ich dich schon immer mal fragen");
	EXPECT_EQ(AskToAsk, false);
}
