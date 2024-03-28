// ThreadingTutorial.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <chrono>  //time

using namespace std;

int main()
{
	cout << this_thread::get_id() << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << this_thread::get_id() << endl;
	





	return 0;
}
