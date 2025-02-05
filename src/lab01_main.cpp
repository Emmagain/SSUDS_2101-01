#include <iostream>
#include <person.h>
#include <PersonDatabase.h>

#define namef "..\\..\\media\\tryit.txt"

int main()
{
	//we will read in the contents of the text file into an array of Person objects
	//we do NOT use any container types (std::list, etc)
	//example::PersonDatabase PD("..\\..\\media\\personb.txt");

	example::Person a(1, "Bob", "Jones");
	example::Person b(2, "Sally", "Smith");

	a.sethourly_rate(35.0f);
	a.sethours_worked(38);
	b.sethourly_rate(16.75f);
	b.sethours_worked(42);

	//std::string namef = "..\\media\\Test.txt";

	example::PersonDatabase Dbase(namef); //("..\media\Test.txt");

	std::string s;
	std::string o;
	std::string f;
	std::string l;
	unsigned int i;

	while (true)
	{
		std::cout << "========== Your Database Options ==========\n1. Add a person to the database\n2. Remove a person from the database\n3. Print the database\n4. Quit\n===========================================\nWhat would you like to do?";
		std::cin >> s;
		if (s == "1")
		{
			std::cout << "Insert ID Number: ";
			std::cin >> i;
			std::cout << "Insert First Name: ";
			std::cin >> f;
			std::cout << "Instert Last Name: ";
			std::cin >> l;		

			Dbase.add_person(example::Person(i, f, l));
		}
		else if (s == "2")
		{
			std::cout << "Insert ID to Remove: ";
			std::cin >> i;
			Dbase.remove_person(i);
		}
		else if (s == "3")
		{
			std::cout << Dbase.to_string() << "\n";
		}
		else if (s == "4")
		{
			break;
		}
		else
		{
			std::cout << "Invalid Input. Try Again.\n";
		}
	}
	//input

	return 0;
}