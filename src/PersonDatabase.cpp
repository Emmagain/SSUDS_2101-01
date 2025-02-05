#include <PersonDatabase.h>
#include <person.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


example::PersonDatabase::PersonDatabase(std::string fname) 
{
	//initialize attributes
	my_array_ptr = nullptr; //because we dont have any data yet
	my_array_size = 0;
	my_file_name = fname;

	//open file
	std::ifstream fin;
	fin.open(my_file_name);
	if (!fin.is_open())
	{
		std::cout << "bad\n";
		//raise error
	}

	else
	{

	//if (fin.is_open()) //checks that the file does already exists
	//{
		//std::cout << "good\n";
		int temp_id = 0;
		std::string temp_fname, temp_lname = "";
		float temp_hourly_rate = 0.0f;
		unsigned int temp_hours_worked = 0;

		//read through file
		while (!fin.eof()) //checks if it is past the end of the file
		{

			//if (fin.eof())
			//std::cout << temp_fname << "\n";

			//get a line's worth of data

			fin >> temp_fname;
			if (temp_fname == "#")
			{
				break;
			}

			fin >> temp_lname;
			fin >> temp_id;
			fin >> temp_hourly_rate;
			fin >> temp_hours_worked;

			Person temp_person(temp_id, temp_fname, temp_lname);
			temp_person.sethourly_rate(temp_hourly_rate);
			temp_person.sethours_worked(temp_hours_worked);


			add_person(temp_person);


		}
	}

	//close file
	fin.close();

}

//example::PersonDatabase::PersonDatabase()
//{
//	my_array_ptr = nullptr; //because we dont have any data yet
//	my_array_size = 0;
//}

void example::PersonDatabase::add_person(example::Person p)
{
	// if nothing in array:
	// make an array of size 1 and put p in it
	if (my_array_size == 0)
	{
		my_array_ptr = new Person[1];
		my_array_ptr[0] = p;
		my_array_size = 1;
	}

	// if something in array:
	// make an array of my_array_size+1 and copy all data into it
	//will need to change to support capacity being different than size
	else
	{
		Person* temp_array = new Person[my_array_size + 1];
		for (unsigned int i = 0; i < my_array_size; i++)
		{
			temp_array[i] = my_array_ptr[i];
		}
		my_array_size++;

		delete[] my_array_ptr; //this is a pointer???
		my_array_ptr = temp_array;
		my_array_ptr[my_array_size - 1] = p;
	}

}

void example::PersonDatabase::remove_person(int remove_id)
{
	Person* temp_array = new Person[my_array_size - 1];
	unsigned int index = 0;
	unsigned int array_size = my_array_size;

	for (unsigned int i = 0; i < array_size; i++)
	{
		if (my_array_ptr[i].getid() == remove_id)
		{
			my_array_size--;
			continue;
		}
		
		temp_array[index] = my_array_ptr[i];
		index++;
	}
	delete[] my_array_ptr; //This is a pointer?
	my_array_ptr = temp_array;

	
}

unsigned int example::PersonDatabase::get_num_people()
{
	return my_array_size;
}

std::string example::PersonDatabase::to_string()
{
	std::ostringstream my_ostring;
	my_ostring << "Person\t\tID\tHours\tRate\tMonthly Salary\n======\t\t==\t=====\t====\t==============\n";
	float total = 0;
	for (unsigned int i = 0; i < my_array_size; i++)
	{
		total += my_array_ptr[i].calculate_wage();
		my_ostring << my_array_ptr[i].getfirst_name() << " " << my_array_ptr[i].getlast_name() << "\t" << my_array_ptr[i].getid() << "\t" << my_array_ptr[i].gethours_worked() << "\t$" << my_array_ptr[i].gethourly_rate() << "\t$" << my_array_ptr[i].calculate_wage() << "\n";
	}
	my_ostring << "======================================================\n\t\t\tTotal: $" << total << "\n";
	std::string my_string = my_ostring.str();
	return my_string;
}

example::PersonDatabase::~PersonDatabase()
{
	//write data out to the file (my_file_name)
	std::cout << "destructor\n";
	std::ofstream fout;
	fout.open(my_file_name);
	std::ostringstream my_ostring;
	for (unsigned int i = 0; i < my_array_size; i++)
	{
		my_ostring << my_array_ptr[i].getfirst_name() << " " << my_array_ptr[i].getlast_name() << " " << my_array_ptr[i].getid() << " " << my_array_ptr[i].gethours_worked() << " " << my_array_ptr[i].gethourly_rate() << "\n";
	}
	std::string my_string = my_ostring.str();
	fout << my_string << "\n#\n";
	//fout << to_string() << "\n";
	fout.close();
	//Free up any resources -- deallocate my_array_ptr
	delete[] my_array_ptr;
}