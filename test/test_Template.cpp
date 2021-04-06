#include "Template.h"
#include <sstream>
#include <gtest.h>

TEST(TEXT, can_create_Text)
{
	ASSERT_NO_THROW(Text());
}



TEST(TEXT, Can_copy_Text)
{
	char ss[] = "LA LA LA";
	Text s1(ss);
	ASSERT_NO_THROW(Text s2(s1));
}
TEST(TEXT, Correct_sentenses)
{
	char s1[] = "Why so serious?";
	Text s(s1);
	stringstream s3;
	s3 << s;
	ASSERT_EQ(s3.str(),static_cast<string>(s1));
}

TEST(TEXT, Correct_text)
{
	char s1[] = "My poshli na plaz. Love u.";
	Text s(s1);
	stringstream s3;
	s3 << s;
	ASSERT_EQ(s3.str(), static_cast<string>(s1));
}

TEST(TEXT, Correct_text1)
{
	char s1[] = "Let's see what we have there? Are u alone, sweety?";
	Text s(s1);
	stringstream s3;
	s3 << s;
	ASSERT_EQ(s3.str(), static_cast<string>(s1));
}

TEST(TEXT, Correct_text2)
{
	char s1[] = "My shizi. YAto nasha zemla. I zdes budet nash poryadok.";
	Text s(s1);
	stringstream s3;
	s3 << s;
	ASSERT_EQ(s3.str(), static_cast<string>(s1));
}









