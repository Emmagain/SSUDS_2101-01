#include <array_list.h>
#include <iostream>
#include <vector>

int main()
{
	std::cout << "Test 1: Iterator Basics \n";
	ssuds::ArrayList<short> slist;
	slist.append(25);
	slist.append(99);
	slist.append(1000);
	slist.append(1001);
	ssuds::ArrayList<short>::AlIterator sit = slist.begin();//Test the normal iterator
	while (sit != slist.end())								// Should Output:
	{														// 25
		std::cout << *sit << "\n";							// 99
		++sit;												// 1000
	}														// 1001

	std::cout << "\nTest 2: For Each \n";					//Test the for each loop
	for (short s : slist)									// Should Output:
	{														// 25
		std::cout << s << "\n";								// 99
	}														// 1000
	std::cout << "\n";										// 1001

	std::cout << "Test 3: Copy Constructor \n";
	ssuds::ArrayList<short> slist2(slist);					//Test copy constructor
	for (short s : slist2)									// Should Output:
	{														// 25
		std::cout << s << "\n";								// 99
	}														// 1000
	std::cout << "\n";										// 1001

	std::cout << "Test 4: Assignment Operator \n";
	ssuds::ArrayList<short> slist3 = slist;					//Test assignment operator
	for (short s : slist3)									// Should Output:
	{														// 25
		std::cout << s << "\n";								// 99
	}														// 1000
															// 1001
	
	std::cout << "\n";										//Test reverse iterator
	std::cout << "Test 5: Reverse Iterator \n";				// Should Output:
	ssuds::ArrayList<float> flist;							// 1.1
	flist.append(1.1f);										// 2.2
	flist.append(2.2f);										// 3.3
	flist.append(3.3f);										// 4.4
	flist.append(4.4f);										// Reverse:
	ssuds::ArrayList<float>::AlIterator fit = flist.begin();// 4.4
	while (fit != flist.end())								// 3.3
	{														// 2.2
		float cur = *fit;									// 1.1
		std::cout << cur << "\n";
		++fit;
	}
	std::cout << "Reverse: \n";
	ssuds::ArrayList<float>::AlIterator rit = flist.rbegin();
	//rit.set_reverse(true);
	while (rit != flist.rend())
	{
		float cur = *rit;
		std::cout << cur << "\n";
		++rit;           // now backwards
	}

	std::cout << "\nTest 6: Initializer-list Constructor and String Type \n";	//Test initializer-list constructor and basic functionality with string type
																				// Should Output:
	ssuds::ArrayList<std::string> stlist = {"abe", "bob", "carl", "diane"};		// abe
																				// bob
	for (int i = 0; i < stlist.size(); i++)										// carl
		std::cout << stlist[i] << "\n";											//diane

	std::cout << "\nTest 7: << Overload Method \n";								//Test << overload method
	std::cout << stlist << "\n";												// Should Output:
																				// [abe, bob, carl, dane]

}

