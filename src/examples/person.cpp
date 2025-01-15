#include <person.h>

//When defining a method declared as part of a class, you must use Classname::
float Person::calculate_wage()
{
	//we have access to all the attributed declared as part of the class
	return hourly_rate * hours_worked;
}