#pragma once
#include <optional>
#include <array_list.h>
#include <iostream>

namespace ssuds
{
	enum class traversal_order { PREORDER, POSTORDER, INORDER };

	template <class T>
	class OrderedSet
	{
	private:
		// Just like LinkedList, I don't want outside users to see this AT ALL!!!
		class Node
		{
		public:
			T mData;
			Node* mLeft;
			Node* mRight;
		public:
			Node(const T& data) : mData(data), mLeft(nullptr), mRight(nullptr)
			{
				// intentionally empty
			}

			~Node()
			{
				if (mLeft != nullptr)
				{
					delete mLeft;
				}
				if (mRight != nullptr)
				{
					delete mRight;
				}
			}

			// Other getters/setters

			bool insert_recursive(const T& new_val)
			{
				if (new_val == mData)
					return false;			// It's a duplicate -- stop!
				else if (new_val < mData)
				{
					// This should go to my left
					if (mLeft == nullptr)
					{
						// I don't have a left-child -- make a new node that BECOMES the left child.
						mLeft = new Node(new_val);
						return true;
					}
					else
					{
						// I DO have a left child
						mLeft->insert_recursive(new_val);
					}
				}
				else
				{
					// This should go to my right -- similar to left case
					if (mRight == nullptr)
					{
						// I don't have a right-child -- make a new node that BECOMES the right child.
						mRight = new Node(new_val);
						return true;
					}
					else
					{
						// I DO have a left child
						mRight->insert_recursive(new_val);
					}
				}
			}


			bool contains_recursive(const T& val) const
			{
				// If I hold the value, return true.
				if (val == mData)
					return true;
				else if (val < mData)
				{
					if (mLeft == nullptr)
					{
						// I don't have a left-child - val is not in the set
						return false;
					}
					else
					{
						// I DO have a left child
						mLeft->contains_recursive(val);
					}
				}
				else
				{
					if (mRight == nullptr)
					{
						// I don't have a right-child - val is not in the set
						return false;
					}
					else
					{
						// I DO have a right child
						mRight->contains_recursive(val);
					}
				}
			}

			unsigned int get_height_recursive(const T& val)
			{
				if (mLeft == nullptr && mRight == nullptr)
				{
					return 1;
				}
				else
				{
					unsigned int lHeight = 0;
					unsigned int rHeight = 0;

					if (mLeft != nullptr)
					{
						lHeight = mLeft->get_height_recursive(val);
					}
					if (mRight != nullptr)
					{
						rHeight = mRight->get_height_recursive(val);
					}
					if (lHeight >= rHeight)
					{
						return lHeight + 1;
					}
					else
					{
						return rHeight + 1;
					}
				}
			}

			std::optional<T> get_parent_recursive(const T& val)
			{
				if (mLeft == nullptr && mRight == nullptr)
				{
					return std::nullopt;
				}
				else if (val < mData)
				{
					if (mLeft == nullptr)
					{
						return std::nullopt;
					}
					else if (mLeft->mData == val)
					{
						
						return mData;
					}
					else
					{
						return mLeft->get_parent_recursive(val);
					}
				}
				else if (val > mData)
				{
					if (mRight == nullptr)
					{
						return std::nullopt;
					}
					else if (mRight->mData == val)
					{
						return mData;
					}
					else
					{
						return mRight->get_parent_recursive(val);
					}
				}
				else if (val == mData)
				{
					return std::nullopt;
				}
			}

			Node* get_successor()
			{
				if (mRight != nullptr)
				{
					return mRight->mLeft->get_successor_recursive();
				}
				else
				{
					throw std::runtime_error("Node has no successor");
				}
			}

			Node* get_successor_recursive()
			{
				if (mLeft != nullptr)
				{
					return mLeft->get_successor_recursive();
				}
				else
				{
					return this;
				}
			}

			Node* erase_recursive(const T& val, bool& result)
			{
				if (val == mData)
				{
					result = true;
					if (!mLeft && !mRight)				//Case 1: no children
					{
						delete this;
						return nullptr;
					}
					else if (mLeft && mRight)			//Case 3: two children
					{
						Node* succ = mRight->get_successor_recursive(); //this->get_successor();
						mData = succ->mData;
						mRight->erase_recursive(mData, result);
					}
					else if (mLeft && !mRight)			//Case 2(A): one child: left
					{
						Node* temp = mLeft;
						mLeft = nullptr;
						delete this;
						return temp;
					}
					else								//Case 2(B): one child: right
					{
						Node* temp = mRight;
						mRight = nullptr;
						delete this;
						return temp;
					}
				}
				else if (val < mData && mLeft != nullptr)
				{
					mLeft = mLeft->erase_recursive(val, result);
					return this;
				}
				else if (val > mData && mRight != nullptr)
				{
					mRight = mRight->erase_recursive(val, result);
					return this;
				}
			}

			void traversal_recursive(ssuds::ArrayList<T>& list, traversal_order order)
			{
				if (order == traversal_order::PREORDER)
				{
					list.append(mData);
				}
				if (mLeft)
				{
					mLeft->traversal_recursive(list, order);
				}
				if (order == traversal_order::INORDER)
				{
					list.append(mData);
				}
				if (mRight)
				{
					mRight->traversal_recursive(list, order);
				}
				if (order == traversal_order::POSTORDER)
				{
					list.append(mData);
				}
			}
		}; // end of Node class

		
		// Attributes for OrderedSet itself.
	private:
		unsigned int mSize;
		Node* mRoot;  
	public:
		OrderedSet() : mSize(0), mRoot(nullptr)
		{
			// intentionally empty.
		}

		~OrderedSet()
		{
			if (mRoot != nullptr)
				delete mRoot;
		}

		bool insert(const T& val)
		{
			if (mSize == 0)
			{
				// Nothing here -- make the new node the root
				mRoot = new Node(val);
				mSize = 1;
				return true;
			}
			else
			{
				// We already have a root -- let it handle the rest
				bool result = mRoot->insert_recursive(val);
				if (result)
					mSize++;
				return result;
			}
		}

		bool contains(const T& val) const
		{
			if (!mRoot)
				return false;
			else
				return mRoot->contains_recursive(val);
		}

		unsigned int get_height(const T& val)
		{
			if (!mRoot)
				return 0;
			else
			{
				return mRoot->get_height_recursive(val);
			}
		}

		std::optional<T> get_parent(const T& val)
		{
			if (!mRoot)
			{
				return std::nullopt;
			}
			else
			{
				return mRoot->get_parent_recursive(val);
			}
		}

		unsigned int size() const
		{
			return mSize;
		}

		void clear()
		{
			// empty set (delete all nodes) without deleting the set itself
			if (mRoot != nullptr)
				delete mRoot;
			mRoot = nullptr;
			mSize = 0;
		}

		bool erase(const T& val)
		{
			if (mSize == 0)
			{
				return false;
			}
			else
			{
				bool removed = false;
				mRoot = mRoot->erase_recursive(val,removed);
				if (removed == true)
				{
					mSize--;
				}
				return removed;
			}
		}

		ssuds::ArrayList<T> traversal(traversal_order order)
		{
			ssuds::ArrayList<T> tlist;
			mRoot->traversal_recursive(tlist, order);
			return tlist;
		}

		friend std::ostream& operator<<(std::ostream& os, const OrderedSet& S)
		{
			ssuds::ArrayList<T> templist;
			S.mRoot->traversal_recursive(templist, ssuds::traversal_order::INORDER);
			os << templist;
			return os;
		}

		// ----------------------------------------------------------------------- ITERATOR SUBCLASS -------------------------------------------------------------------------------------------------------
		
		friend Node* pop(ArrayList<Node*>& list)
		{
			Node* temp = list[list.size() - 1];
			list.remove(list.size() - 1);
			return temp;
		}

		class OSIterator
		{
		protected:

			ArrayList<Node*> NStack;
			Node* Cur;

		public:

			OSIterator(Node* rootNode)
			{
				Cur = rootNode;
				while (Cur != NULL)
				{
					NStack.append(Cur);
					Cur = Cur->mLeft;
				}
				if (NStack.size() != 0)
				{
					Cur = pop(NStack);
				}
			}

			OSIterator operator++()
			{
				Cur = Cur->mRight;
				while (Cur != NULL)
				{
					NStack.append(Cur);
					Cur = Cur->mLeft;
				}
				if (NStack.size() != 0)
				{
					Cur = pop(NStack);
				}
				return *this;
			}

			const T& operator*()
			{
				return Cur->mData;
			}

			bool operator!=(const OSIterator& other) const
			{
				if ( Cur != other.Cur)
				{
					return true;
				}
				else
				{
					return false;
				}
			}

			bool operator ==(const OSIterator& other) const
			{
				if ( Cur == other.Cur)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		};

		OSIterator begin()		
		{
			OSIterator temp(mRoot);
			return temp;
		}

		OSIterator end()	
		{
			OSIterator temp(nullptr);
			return temp;
		}
		
	};
}
