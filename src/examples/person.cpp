#include <person.h>
#include <iostream>

using namespace example;

//When defining a method declared as part of a class, you must use Classname::

example::Person::Person()
{ // ^^ doesn't need the "using namespace" line
	id = -1;
	first_name = "?";
	last_name = "?";
	hourly_rate = 0;
	hours_worked = 0;
}

Person::Person(int starting_id, std::string starting_first_name, std::string starting_last_name)
{ 
	id = starting_id;
	first_name = starting_first_name;
	last_name = starting_last_name;
	hourly_rate = 0;
	hours_worked = 0;
}

Person::~Person()
{
	//Nothing needs to be unallocated or destroyed when an instance is deleted
	//std::cout << "Person '" << first_name << "' will be deleted from the system \n";
}

float Person::calculate_wage()
{
	//we have access to all the attributed declared as part of the class
	return hourly_rate * hours_worked;
}

int Person::getid()
{
	return id;
}

std::string Person::getfirst_name()
{
	return first_name;
}

std::string Person::getlast_name()
{
	return last_name;
}

float Person::gethourly_rate()
{
	return hourly_rate;
}

unsigned int Person::gethours_worked()
{
	return hours_worked;
}

void Person::setid(int x)
{
	id = x;
}

void Person::setfirst_name(std::string x)
{
	first_name = x;
}

void Person::setlast_name(std::string x)
{
	last_name = x;
}

void Person::sethourly_rate(float new_rate)
{
	if (new_rate < 0 || new_rate > 1000)
	{
		throw std::runtime_error("Invalid hourly rate: $" + std::to_string(new_rate));
	}
	hourly_rate = new_rate;
}

void Person::sethours_worked(unsigned int x)
{
	hours_worked = x;
}
