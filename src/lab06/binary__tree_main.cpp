#include <binary_tree.h>
#include <array_list.h>
#include <iostream>

int main(int argc, char** argv)
{
	ssuds::OrderedSet<float> fset;
	fset.insert(3.7f);
	fset.insert(1.9f);
	fset.insert(2.3f);
	fset.insert(1.9f);		// duplicate!
	fset.insert(0.1f);

	std::cout << fset.contains(1.9f) << "\n";		// true (1)
	std::cout << fset.contains(8.8f) << "\n";		// falst (0)
	/*
	ssuds::ArrayList<float> pre_order = fset.traversal(ssuds::TraversalType::PRE_ORDER);
	//             3.7
	//            / 
	//           1.9
	//           / \
	//         0.1  2.3
	// [3.7, 1.9, 0.1, 2.3]
	
	ssuds::ArrayList<float> in_order = fset.traversal(ssuds::TraversalType::IN_ORDER);
	// [0.1, 1.9, 2.3, 3.7]
	*/
	ssuds::OrderedSet<float> fset2;
	fset2.insert(3.7f);
	fset2.insert(0.5f);
	fset2.insert(8.4f);
	fset2.insert(0.0f);
	fset2.insert(1.9f);
	fset2.insert(4.2f);
	fset2.insert(11.3f);

	ssuds::ArrayList<float> prelist = fset2.traversal(ssuds::traversal_order::PREORDER);
	ssuds::ArrayList<float> postlist = fset2.traversal(ssuds::traversal_order::POSTORDER);
	std::cout << prelist << "\n";			// Pre Order:  [3.7, 0.5, 0, 1.9, 8.4, 4.2, 11.3]
	std::cout << postlist << "\n";          // Post Order: [0, 1.9, 0.5, 4.2, 11.3, 8.4, 3.7]
	std::cout << fset2 << "\n";				// In Order:   [0, 0.5, 1.9, 3.7, 4.2, 8.4, 11.3]

	ssuds::OrderedSet<float> tset;
	tset.insert(1.1f);
	tset.insert(2.2f);
	tset.insert(3.3f);
	ssuds::OrderedSet<float>::OSIterator flit = tset.begin();
	while (flit != tset.end())
	{
		std::cout << *flit << "\n";
		++flit;
	}
}