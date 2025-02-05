#include <iostream>
#include <string.h>
#include <string> //new for c++
#include <person.h>

using namespace std;
using namespace example;

int main()
{
	example::Person p(42, "Bob", "Jones"); // <- doesn't need the "using namespace" line
	Person q(43, "Sally", "Smith"); // <- needs the "using namespace" line
	Person r; // <- Uses the "default" constructor

	p.sethourly_rate(35.0f);
	p.sethours_worked(38);
	q.sethourly_rate(16.75f);
	q.sethours_worked(42);
	try 
	{
		r.sethourly_rate(-1.5f);
	}
	//catch (std::out_of_range e)
	//{
		//this code runs if an out_of_range error is triggered in the "try"
	//}
	catch (std::runtime_error)
	{
		//this code runs if a runtime error is triggered in the "try"
		std::cout << "Invalid entry\n\t";
		//std::cout << e.what() << "\n";
	}

	std::cout << p.getid() << " " << p.getfirst_name() << "\n";
}