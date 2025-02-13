#include <array_list.h>
#include <iostream>

int main()
{
	/*
	//TEST EVERY FUNCTION FOR FLOAT

	// The basic test program (for floats)
	ssuds::ArrayList<float> float_list;

	std::cout << "test1:\n=====\n";										// test1 (constructor, append, size, capacity, at):
	float_list.append(2.1f);											// ======
	float_list.append(3.6f);
	std::cout << "\tsize=" << float_list.size() << std::endl;			// size=2
	std::cout << "\tcapacity=" << float_list.capacity() << std::endl;	// capacity=5
	std::cout << "\titem0=" << float_list.at(0) << std::endl;			// item0=2.1
	std::cout << "\titem1=" << float_list.at(1) << std::endl;			// item1=3.6

	std::cout << "test2:\n=====\n";										// test2 (insert, grow capacity):
	float_list.insert(1.8f, 0);											// ======
	float_list.insert(4.2f, 3);											// item0=1.8
	float_list.insert(2.0f, 1);											// item1=2
	for (int i = 0; i < float_list.size(); i++)							// item2=2.1
		std::cout << "\titem" << i << "=" << float_list.at(i) << "\n";	// item3=3.6
	std::cout << "\tcapacity=" << float_list.capacity() << std::endl;	// item4=4.2
																		// capacity=10

	std::cout << "test3:\n=====\n";										// test3 (prepend):
	//std::cout << "\tcapacity=" << float_list.capacity() << std::endl;	// ======
	float_list.prepend(4.2f);											// item0=1.6
	float_list.prepend(1.6f);											// item1=4.2
																		// item2=1.8
																		// item3=2
	for (int i = 0; i < float_list.size(); i++)							// item4=2.1
		std::cout << "\titem" << i << "=" << float_list.at(i) << "\n";	// item5=3.6
																		// item6=4.2

	std::cout << "test4:\n=====\n";										// test4 (remove, shrink capacity):
	float_list.remove(3);												// ======
	float_list.remove(5);												// item0=2.1
	float_list.remove(1);												// item1=3.6
	float_list.remove(0);												// capacity=5
	float_list.remove(0);												// size=2
	for (int i = 0; i < float_list.size(); i++)	
		std::cout << "\titem" << i << "=" << float_list.at(i) << "\n";
	std::cout << "\tcapacity=" << float_list.capacity() << std::endl;
	std::cout << "\tsize=" << float_list.size() << std::endl;


	std::cout << "test5:\n=====\n";										// test5 (output):
	float_list.append(1.8f);											// ======
	float_list.append(4.2f);											// items:
	std::cout << "\titems:\n\t";											// [2.1, 3.6, 1.8, 4.2]
	float_list.output(std::cout);									
	std::cout << "\n";
	
	std::cout << "test6:\n=====\n";										// test6 (find):
	int val_index = float_list.find(1.8);								// ======
	std::cout << "\tValue '1.8' is at index " << val_index << "\n";		// Value '1.8' is at index 2
	val_index = float_list.find(0.0);									// Value '0.0' is at index -1
	std::cout << "\tValue '0.0' is at index " << val_index << "\n";		// Value '3.6' is at index 1
	float_list.append(3.6f);											// Value '3.6' is also at index 4
	val_index = float_list.find(3.6);
	std::cout << "\tValue '3.6' is at index " << val_index << "\n";		
	val_index = float_list.find(3.6,2);
	std::cout << "\tValue '3.6' is also at index " << val_index << "\n";	


	//TEST EVERY FUNCTION FOR INT

	// The basic test program (for ints)
	ssuds::ArrayList<int> int_list;

	std::cout << "test1:\n=====\n";										// test1 (constructor, append, size, capacity, at):
	int_list.append(2);													// ======
	int_list.append(3);
	std::cout << "\tsize=" << int_list.size() << std::endl;				// size=2
	std::cout << "\tcapacity=" << int_list.capacity() << std::endl;		// capacity=5
	std::cout << "\titem0=" << int_list.at(0) << std::endl;				// item0=2
	std::cout << "\titem1=" << int_list.at(1) << std::endl;				// item1=3

	std::cout << "test2:\n=====\n";										// test2 (insert, grow capacity):
	int_list.insert(1, 0);												// ======
	int_list.insert(4, 3);												// item0=1
	int_list.insert(6, 1);												// item1=6
	for (int i = 0; i < int_list.size(); i++)							// item2=2
		std::cout << "\titem" << i << "=" << int_list.at(i) << "\n";	// item3=3
	std::cout << "\tcapacity=" << int_list.capacity() << std::endl;		// item4=4
																		// capacity=10

	std::cout << "test3:\n=====\n";										// test3 (prepend):
	//std::cout << "\tcapacity=" << int_list.capacity() << std::endl;	// ======
	int_list.prepend(4);												// item0=1
	int_list.prepend(1);												// item1=4
																		// item2=1
																		// item3=6
	for (int i = 0; i < int_list.size(); i++)							// item4=2
		std::cout << "\titem" << i << "=" << int_list.at(i) << "\n";	// item5=3
																		// item6=4

	std::cout << "test4:\n=====\n";										// test4 (remove, shrink capacity):
	int_list.remove(3);													// ======
	int_list.remove(5);													// item0=2
	int_list.remove(1);													// item1=3
	int_list.remove(0);													// capacity=5
	int_list.remove(0);													// size=2
	for (int i = 0; i < int_list.size(); i++)
		std::cout << "\titem" << i << "=" << int_list.at(i) << "\n";
	std::cout << "\tcapacity=" << int_list.capacity() << std::endl;
	std::cout << "\tsize=" << int_list.size() << std::endl;


	std::cout << "test5:\n=====\n";										// test5 (output):
	int_list.append(1.8f);												// ======
	int_list.append(4.2f);												// items:
	std::cout << "\titems:\n\t";										// [2, 3, 1, 4]
	int_list.output(std::cout);
	std::cout << "\n";

	std::cout << "test6:\n=====\n";										// test6 (find):
	int int_index = int_list.find(1);									// ======
	std::cout << "\tValue '1' is at index " << int_index << "\n";		// Value '1' is at index 2
	int_index = int_list.find(0);										// Value '0' is at index -1
	std::cout << "\tValue '0' is at index " << int_index << "\n";		// Value '3' is at index 1
	int_list.append(3);													// Value '3' is also at index 4
	int_index = int_list.find(3);
	std::cout << "\tValue '3' is at index " << int_index << "\n";
	int_index = int_list.find(3, 2);
	std::cout << "\tValue '3' is also at index " << int_index << "\n";

	*/

	//TEST EVERY FUNCTION FOR PERSON OBJECT
	// The basic test program (for person objects)
	ssuds::ArrayList<float> person_list;

	std::cout << "test1:\n=====\n";
}

/*
ssuds::ArrayList<int>::AlIterator it;
it = ilist.begin()
while (it != ilist.end())
{
	int cur = *it;
	std::cout << cur << "\n";
	++it;
}
*/