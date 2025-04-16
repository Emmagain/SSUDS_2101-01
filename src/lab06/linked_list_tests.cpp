#include <gtest/gtest.h>
#include <linked_list.h>
#include <iostream>
#include <sstream>

TEST(LLTest, Bracket_and_Append)
{
	ssuds::LinkedList<float> flist; //= { 1.1f,2.2f,3.3f };
	flist.append(1.1f);
	flist.append(2.2f);
	flist.append(3.3f);
	ASSERT_EQ(flist.size(), 3);
	EXPECT_EQ(flist[0], 1.1f);
	EXPECT_EQ(flist[1], 2.2f);
	EXPECT_EQ(flist[2], 3.3f);
	EXPECT_THROW(flist[4], std::out_of_range);
}


TEST(LLTest, Insert)
{
	ssuds::LinkedList<float> flist; //= { 1.1f,2.2f,3.3f };
	flist.append(1.1f);
	flist.append(2.2f);
	flist.append(3.3f);
	flist.insert(1.8f, 0);
	flist.insert(4.2f, 3);
	EXPECT_EQ(flist[0], 1.8f);
	EXPECT_EQ(flist[1], 1.1f);
	EXPECT_EQ(flist[2], 2.2f);
	EXPECT_EQ(flist[3], 4.2f);
}

TEST(LLTest, StreamTest)
{
	ssuds::LinkedList<std::string> slist;

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

TEST(LLTest, At)
{
	ssuds::LinkedList<float> flist;
	flist.append(1.1f);
	flist.append(2.2f);
	flist.append(3.3f);
	EXPECT_EQ(flist.at(1), 2.2f);
	EXPECT_THROW(flist.at(4), std::out_of_range);
}

TEST(LLTest, CopyConstructor)
{
	ssuds::LinkedList<float> flist;
	flist.append(1.1f);
	flist.append(2.2f);
	flist.append(3.3f);
	ssuds::LinkedList<float> flist2(flist);
	ASSERT_EQ(flist2.size(), 3);
	EXPECT_EQ(flist2[0], 1.1f);
	EXPECT_EQ(flist2[1], 2.2f);
	EXPECT_EQ(flist2[2], 3.3f);
	ASSERT_EQ(flist.size(), 3);
	EXPECT_EQ(flist[0], 1.1f);
	EXPECT_EQ(flist[1], 2.2f);
	EXPECT_EQ(flist[2], 3.3f);
}

TEST(LLTest, AssignmentOperator)
{
	ssuds::LinkedList<float> flist;
	flist.append(1.1f);
	flist.append(2.2f);
	flist.append(3.3f);
	ssuds::LinkedList<float> flist2 = flist;
	ASSERT_EQ(flist2.size(), 3);
	EXPECT_EQ(flist2[0], 1.1f);
	EXPECT_EQ(flist2[1], 2.2f);
	EXPECT_EQ(flist2[2], 3.3f);
}

TEST(OSTest, Clear)
{
	ssuds::LinkedList<float> flist;
	flist.append(1.1f);
	flist.append(2.2f);
	flist.append(3.3f);
	flist.clear();
	EXPECT_EQ(flist.size(), 0);
	EXPECT_THROW(flist.at(0), std::out_of_range);
	EXPECT_THROW(flist.at(1), std::out_of_range);
}

TEST(LLTest, Iterator_and_InitListConstructor)
{
	ssuds::LinkedList<float> flist = { 1.1f,2.2f,3.3f };
	ssuds::LinkedList<float>::LLIterator fit = flist.begin();
	ASSERT_EQ(*fit, 1.1f);
	++fit;
	EXPECT_EQ(*fit, 2.2f);
	++fit;
	EXPECT_EQ(*fit, 3.3f);
	++fit;
	EXPECT_EQ(fit, flist.end());
}

TEST(LLTest, RevIterator)
{
	ssuds::LinkedList<float> flist = { 1.1f,2.2f,3.3f };
	ssuds::LinkedList<float>::LLIterator fit = flist.rbegin();
	ASSERT_EQ(*fit, 3.3f);
	++fit;
	EXPECT_EQ(*fit, 2.2f);
	++fit;
	EXPECT_EQ(*fit, 1.1f);
	++fit;
	EXPECT_EQ(fit, flist.rend());
}

TEST(LLTest, ForEach)
{
	float temp_arr[] = { 1.1f, 2.2f, 3.3f, 4.4f };
	ssuds::LinkedList<float> flist;
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

TEST(LLTest, Find)
{
	ssuds::LinkedList<float> flist = { 1.1f,2.2f,3.3f,4.4f };
	EXPECT_EQ(flist.find(3.3f), 2);
	EXPECT_EQ(flist.find(4.4f), 3);
	EXPECT_EQ(flist.find(5.5f), -1);
}

TEST(LLTest, Find_It)
{
	ssuds::LinkedList<float> flist = { 1.1f,2.2f,3.3f,4.4f,2.2f };
	ssuds::LinkedList<float>::LLIterator it = flist.find_it(1.1f);
	EXPECT_EQ(*it, 1.1f);
	it = flist.find_it(2.2f);
	EXPECT_EQ(*it, 2.2f);
	it = flist.find_it(2.2f, 2);
	EXPECT_EQ(*it, 2.2f);
	//it = flist.find_it(1.1f, 2);
	EXPECT_THROW(flist.find_it(1.1f, 2), std::runtime_error);
	EXPECT_THROW(flist.find_it(5.5f), std::runtime_error);
}

TEST(LLTest, Remove)
{
	ssuds::LinkedList<float> flist = { 1.1f,2.2f,3.3f,4.4f };
	EXPECT_EQ(flist.size(), 4);
	flist.remove(1);
	EXPECT_EQ(flist.size(), 3);
	EXPECT_EQ(flist[0], 1.1f);
	EXPECT_EQ(flist[1], 3.3f);
	EXPECT_EQ(flist[2], 4.4f);
}

TEST(LLTest, Remove_It)
{
	ssuds::LinkedList<float> flist = { 1.1f,2.2f,3.3f,4.4f };
	ssuds::LinkedList<float>::LLIterator it = flist.find_it(2.2f);
	EXPECT_EQ(flist.size(), 4);
	flist.remove_it(it);
	EXPECT_EQ(flist.size(), 3);
	EXPECT_EQ(flist[0], 1.1f);
	EXPECT_EQ(flist[1], 3.3f);
	EXPECT_EQ(flist[2], 4.4f);
	it = flist.find_it(1.1f);
	flist.remove_it(it);
	EXPECT_EQ(flist.size(), 2);
	it = flist.find_it(4.4f);
	flist.remove_it(it);
	EXPECT_EQ(flist.size(), 1);
}

TEST(LLTest, RemoveAll)
{
	ssuds::LinkedList<float> flist = { 2.2f,1.1f,2.2f,3.3f,4.4f,2.2f,5.5f };
	EXPECT_EQ(flist.size(), 7);
	flist.remove_all(2.2f);
	EXPECT_EQ(flist.size(), 4);
	EXPECT_EQ(flist[0], 1.1f);
	EXPECT_EQ(flist[1], 3.3f);
	EXPECT_EQ(flist[2], 4.4f);
	EXPECT_EQ(flist[3], 5.5f);
	EXPECT_THROW(flist.find_it(2.2f), std::runtime_error);
}
