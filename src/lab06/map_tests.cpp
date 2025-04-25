#include <gtest/gtest.h>
#include <hash_map.h>
#include <sstream>


TEST(HMTest, Bracket)
{
	ssuds::Map<std::string, float> smap;

	smap["Emma"] = 5.30f;
	smap["Syd"] = 6.17f;
	smap["Beth"] = 8.15f;
	ASSERT_EQ(smap.size(),3);
	EXPECT_EQ(smap["Emma"], 5.3f);
	EXPECT_EQ(smap["Syd"], 6.17f);
	EXPECT_EQ(smap["Beth"], 8.15f);
	smap["Beth"] = 8.12f;
	EXPECT_EQ(smap.size(), 3);
	EXPECT_EQ(smap["Beth"], 8.12f);
	smap["Jeff"];
	EXPECT_EQ(smap.size(), 4);
}

TEST(HMTest, Grow)
{
	ssuds::Map<std::string, float> mmap;
	EXPECT_EQ(mmap.capacity(), 10);
	mmap["bob"] = 11.3f;		
	mmap["sue"] = 13.9f;		
	mmap["carl"] = 15.6f;
	mmap["abe"] = 0.1f;
	mmap["doug"] = 16.3f;
	mmap["bella"] = 12.1f;
	EXPECT_EQ(mmap.size(), 6);
	EXPECT_EQ(mmap.capacity(), 10);
	mmap["will"] = 7.8f;
	mmap["allie"] = 10.1f;
	// May need to add an 8th entry for it to grow, unsure
	EXPECT_EQ(mmap.size(), 8);
	EXPECT_EQ(mmap.capacity(), 20);
}


TEST(HMTest, StreamTest)
{
	ssuds::Map<std::string, int> mmap;

	std::stringstream ss;
	ss << mmap;
	EXPECT_EQ(ss.str(), "{}");

	ss.str("");
	mmap["first"] = 1;
	ss << mmap;
	EXPECT_EQ(ss.str(), "{first:1}");

	ss.str("");
	mmap["second"] = 2;
	ss << mmap;
	EXPECT_EQ(ss.str(), "{second:2, first:1}");
}

TEST(HMTest, Contains)
{
	ssuds::Map<std::string, float> mmap;
	mmap["bob"] = 11.3f;		
	mmap["sue"] = 13.9f;		
	mmap["carl"] = 15.6f;
	std::string b = "bob";
	std::string s = "sue";
	std::string c = "carl";
	std::string d = "bella";
	EXPECT_EQ(mmap.contains(b), true);
	EXPECT_EQ(mmap.contains(s), true);
	EXPECT_EQ(mmap.contains(c), true);
	EXPECT_EQ(mmap.contains(d), false);
}


TEST(HMTest, Find)
{
	ssuds::Map<std::string, float> mmap;
	mmap["bob"] = 11.3f;
	mmap["sue"] = 13.9f;
	mmap["carl"] = 15.6f;
	std::string b = "bob";
	std::string s = "sue";
	std::string c = "carl";
	std::string a = "allie";
	ssuds::Map<std::string, float>::MAPIterator mit;
	mit = mmap.find(b);
	EXPECT_EQ(*mit, std::pair(b, 11.3f));
	mit = mmap.find(s);
	EXPECT_EQ(*mit, std::pair(s, 13.9f));
	mit = mmap.find(c);
	EXPECT_EQ(*mit, std::pair(c, 15.6f));
	mit = mmap.find(a);
	EXPECT_EQ(mit, mmap.end());
}

TEST(HMTest, Remove)
{
	ssuds::Map<std::string, float> mmap;
	mmap["bob"] = 11.3f;
	mmap["sue"] = 13.9f;
	mmap["carl"] = 15.6f;
	mmap["allie"] = 12.4f;
	EXPECT_EQ(mmap.size(), 4);
	std::string b = "bob";
	std::string s = "sue";
	std::string c = "carl";
	std::string a = "allie";
	EXPECT_EQ(mmap.contains(b), true);
	EXPECT_EQ(mmap.contains(s), true);
	EXPECT_EQ(mmap.contains(c), true);
	EXPECT_EQ(mmap.contains(a), true);
	mmap.remove(s);
	EXPECT_EQ(mmap.size(), 3);
	EXPECT_EQ(mmap.contains(b), true);
	EXPECT_EQ(mmap.contains(s), false);
	EXPECT_EQ(mmap.contains(c), true);
	EXPECT_EQ(mmap.contains(a), true);
	mmap.remove(b);
	EXPECT_EQ(mmap.size(), 2);
	EXPECT_EQ(mmap.contains(b), false);
	EXPECT_EQ(mmap.contains(s), false);
	EXPECT_EQ(mmap.contains(c), true);
	EXPECT_EQ(mmap.contains(a), true);
}

TEST(HMTest, Iterator)
{
	ssuds::Map<std::string, float> mmap;
	mmap["bob"] = 11.3f;
	mmap["sue"] = 13.9f;
	mmap["carl"] = 15.6f;
	mmap["allie"] = 12.4f;
	std::string b = "bob";
	std::string s = "sue";
	std::string c = "carl";
	std::string a = "allie";
	ssuds::Map<std::string, float>::MAPIterator mit = mmap.begin();
	ASSERT_EQ(*mit, std::pair(s, 13.9f));	//0
	++mit;
	//*mit is nullptr						//1
	++mit;
	EXPECT_EQ(*mit, std::pair(b,11.3f));	//2
	++mit;
	//*mit is nullptr						//3
	++mit;
	EXPECT_EQ(*mit, std::pair(a,12.4f));	//4
	++mit;
	//*mit is nullptr						//5
	++mit;
	//*mit is nullptr						//6
	++mit;
	EXPECT_EQ(*mit, std::pair(c,15.6f));	//7
	++mit;
	//*mit is nullptr						//8
	++mit;
	//*mit is nullptr						//9
	++mit;
	EXPECT_EQ(mit, mmap.end());
}

TEST(HMTest, RevIterator)
{
	ssuds::Map<std::string, float> mmap;
	mmap["bob"] = 11.3f;
	mmap["sue"] = 13.9f;
	mmap["carl"] = 15.6f;
	mmap["allie"] = 12.4f;
	std::string b = "bob";
	std::string s = "sue";
	std::string c = "carl";
	std::string a = "allie";
	ssuds::Map<std::string, float>::MAPIterator mit = mmap.rbegin();
	//*mit is nullptr						//9
	++mit;
	//*mit is nullptr						//8
	++mit;
	EXPECT_EQ(*mit, std::pair(c, 15.6f));	//7
	++mit;
	//*mit is nullptr						//6
	++mit;
	//*mit is nullptr						//5
	++mit;
	EXPECT_EQ(*mit, std::pair(a, 12.4f));	//4
	++mit;
	//*mit is nullptr						//3
	++mit;
	EXPECT_EQ(*mit, std::pair(b, 11.3f));	//2
	++mit;
	//*mit is nullptr						//1
	++mit;
	ASSERT_EQ(*mit, std::pair(s, 13.9f));	//0
	++mit;
	EXPECT_EQ(mit, mmap.rend());
}