#include <gtest/gtest.h>
#include <binary_tree.h>
#include <iostream>
#include <optional>

TEST(OSTest, InsertAndContains)
{
	ssuds::OrderedSet<float> fset;
	fset.insert(3.7f);
	fset.insert(1.9f);
	fset.insert(2.3f);
	EXPECT_EQ(fset.contains(3.7f), true);
	EXPECT_EQ(fset.contains(1.9f), true);
	EXPECT_EQ(fset.contains(2.3f), true);
	EXPECT_EQ(fset.contains(0.0f), false);
}

TEST(OSTest, Size)
{
	ssuds::OrderedSet<float> fset;
	fset.insert(3.7f);
	fset.insert(1.9f);
	fset.insert(2.3f);
	EXPECT_EQ(fset.size(), 3);
	fset.insert(1.9f);
	EXPECT_EQ(fset.size(), 3);
}

TEST(OSTest, GetHeight)
{
	ssuds::OrderedSet<float> fset;
	fset.insert(3.7f);
	fset.insert(1.9f);
	fset.insert(2.3f);
	fset.insert(4.8f);
	fset.insert(2.2f);
	EXPECT_EQ(fset.get_height(3.7), 4);
}

TEST(OSTest, GetParent)
{
	ssuds::OrderedSet<float> fset;
	fset.insert(3.7f);
	fset.insert(1.9f);
	fset.insert(2.3f);
	fset.insert(4.8f);
	fset.insert(2.2f);
	EXPECT_EQ(fset.get_parent(2.3), 1.9f);
	EXPECT_EQ(fset.get_parent(2.2), 2.3f);
	EXPECT_EQ(fset.get_parent(3.7), std::nullopt);
	EXPECT_EQ(fset.get_parent(0.0), std::nullopt);
}

TEST(OSTest, Erase)
{
	ssuds::OrderedSet<float> fset;
	fset.insert(3.7f);
	fset.insert(0.5f);
	fset.insert(8.4f);
	fset.insert(0.0f);
	fset.insert(1.9f);
	fset.insert(4.2f);
	fset.insert(11.3f);
	EXPECT_EQ(fset.erase(1.9f), true); // No Children
	EXPECT_EQ(fset.contains(1.9f), false);
	EXPECT_EQ(fset.erase(0.5f), true); // One Child
	EXPECT_EQ(fset.contains(0.5f), false);
	EXPECT_EQ(fset.erase(8.4f), true); // Two Children
	EXPECT_EQ(fset.contains(8.4f), false);
	EXPECT_EQ(fset.erase(7.2f), false); // Try to remove a value not in the list

}

TEST(OSTest, Clear) //NOT YET TESTED
{
	ssuds::OrderedSet<float> fset;
	fset.insert(3.7f);
	fset.insert(1.9f);
	fset.insert(2.3f);
	fset.insert(4.8f);
	fset.insert(2.2f);
	fset.clear();
	EXPECT_EQ(fset.size(), 0);
	EXPECT_EQ(fset.contains(1.9f), false);
}
/*
TEST(OSTest, Iterator)
{
	ssuds::OrderedSet<float> fset; 
	fset.insert(1.1f);
	fset.insert(2.2f); 
	fset.insert(3.3f);
	ssuds::OrderedSet<float>::OSIterator flit = fset.begin();
	ASSERT_EQ(*flit, 1.1f);
	++flit;
	EXPECT_EQ(*flit, 2.2f);
	++flit;
	EXPECT_EQ(*flit, 3.3f);
	++flit;
	EXPECT_EQ(flit, fset.end());
}
*/