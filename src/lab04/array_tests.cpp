#include <gtest/gtest.h>
#include <array_list.h>
#include <sstream>

TEST(ALTest, Bracket)
{
	ssuds::ArrayList<float> flist = { 1.1f,2.2f,3.3f };
	ASSERT_EQ(flist.size(), 3);
	EXPECT_EQ(flist[0], 1.1f);
	EXPECT_EQ(flist[1], 2.2f);
	EXPECT_EQ(flist[2], 3.3f);
	//EXPECT_THROW(flist[4], std::out_of_range);
}

TEST(ALTest, Append)
{
	ssuds::ArrayList<float> flist;
	flist.append(2.3f);                                    
	flist.append(2.6f);
	EXPECT_EQ(flist[0], 2.3f);
	EXPECT_EQ(flist[1], 2.6f);
}

TEST(ALTest, Insert)
{
	ssuds::ArrayList<float> flist = { 1.1f,2.2f,3.3f };
	flist.insert(1.8f, 0);                                    
	flist.insert(4.2f, 3);                                                                     
	EXPECT_EQ(flist[0], 1.8f);
	EXPECT_EQ(flist[1], 1.1f);
	EXPECT_EQ(flist[2], 2.2f);
	EXPECT_EQ(flist[3], 4.2f);
}

TEST(ALTest, Prepend)
{
	ssuds::ArrayList<float> flist = { 1.1f,2.2f };
	flist.prepend(0.0f);
	flist.prepend(5.5f);
	EXPECT_EQ(flist[0], 5.5f);
	EXPECT_EQ(flist[1], 0.0f);
	EXPECT_EQ(flist[2], 1.1f);
	EXPECT_EQ(flist[3], 2.2f);
}

TEST(ALTest, Grow)
{
	ssuds::ArrayList<float> flist = { 1.1f,2.2f,3.3f,4.4f };
	EXPECT_EQ(flist.capacity(), 5);
	EXPECT_EQ(flist.size(), 4);
	flist.append(5.5f);
	flist.append(6.6f);
	EXPECT_EQ(flist.capacity(), 10);
	EXPECT_EQ(flist.size(), 6);
}

TEST(ALTest, Remove)
{
	ssuds::ArrayList<float> flist = { 1.1f,2.2f,3.3f,4.4f };
	EXPECT_EQ(flist.size(), 4);
	flist.remove(1);
	EXPECT_EQ(flist.size(), 3);
	EXPECT_EQ(flist[0], 1.1f);
	EXPECT_EQ(flist[1], 3.3f);
	EXPECT_EQ(flist[2], 4.4f);
}

TEST(ALTest, Shrink)
{
	ssuds::ArrayList<float> flist = { 1.1f,2.2f,3.3f,4.4f,5.5f };
	EXPECT_EQ(flist.capacity(), 10);
	EXPECT_EQ(flist.size(), 5);
	flist.remove(3);
	flist.remove(3);
	flist.remove(2);
	EXPECT_EQ(flist.capacity(), 5);
	EXPECT_EQ(flist.size(), 2);
}

TEST(ALTest, At)
{
	ssuds::ArrayList<float> flist = { 1.1f,2.2f,3.3f };
	EXPECT_EQ(flist.at(1), 2.2f);
}

TEST(ALTest, Find)
{
	ssuds::ArrayList<float> flist = { 1.1f,2.2f,3.3f };
	EXPECT_EQ(flist.find(3.3f), 2);
}

TEST(ALTest, CopyConstructor)
{
	ssuds::ArrayList<float> flist = { 1.1f,2.2f,3.3f };
	ssuds::ArrayList<float> flist2(flist);
	ASSERT_EQ(flist2.size(), 3);
	EXPECT_EQ(flist2[0], 1.1f);
	EXPECT_EQ(flist2[1], 2.2f);
	EXPECT_EQ(flist2[2], 3.3f);
}

TEST(ALTest, AssignmentOperator)
{
	ssuds::ArrayList<float> flist = { 1.1f,2.2f,3.3f };
	ssuds::ArrayList<float> flist2 = flist;
	ASSERT_EQ(flist2.size(), 3);
	EXPECT_EQ(flist2[0], 1.1f);
	EXPECT_EQ(flist2[1], 2.2f);
	EXPECT_EQ(flist2[2], 3.3f);
}

TEST(ALTest, Iterator)
{
	ssuds::ArrayList<float> flist = { 1.1f,2.2f,3.3f };
	ssuds::ArrayList<float>::AlIterator fit = flist.begin();
	ASSERT_EQ(*fit, 1.1f);
	++fit;
	EXPECT_EQ(*fit, 2.2f);
	++fit;
	EXPECT_EQ(*fit, 3.3f);
	++fit;
	EXPECT_EQ(fit, flist.end());
}

TEST(ALTest, RevIterator)
{
	ssuds::ArrayList<float> flist = { 1.1f,2.2f,3.3f };
	ssuds::ArrayList<float>::AlIterator fit = flist.rbegin();
	ASSERT_EQ(*fit, 3.3f);
	++fit;
	EXPECT_EQ(*fit, 2.2f);
	++fit;
	EXPECT_EQ(*fit, 1.1f);
	++fit;
	EXPECT_EQ(fit, flist.rend());
}

TEST(ALTest, ForEach)
{
	float temp_arr[] = { 1.1f, 2.2f, 3.3f, 4.4f };
	ssuds::ArrayList<float> flist;
	for (int i = 0; i < 4; i++)
	{
		flist.append(temp_arr[i]);
	}
	ASSERT_EQ(flist.size(), 4);

	int index = 0;
	for (float val : flist)
	{
		ASSERT_EQ(temp_arr[index], val);
		index++;
	}
}

TEST(ALTest, StreamTest)
{
	ssuds::ArrayList<std::string> slist;

	std::stringstream ss;
	ss << slist;
	EXPECT_EQ(ss.str(), "[]");

	ss.str("");
	slist.append("first");
	ss << slist;
	EXPECT_EQ(ss.str(), "[first]");

	ss.str("");
	slist.append("second");
	slist.append("last");
	ss << slist;
	EXPECT_EQ(ss.str(), "[first, second, last]");
}
	
