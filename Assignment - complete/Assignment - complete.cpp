// Assignment - complete.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include "Map.h"
#include <string>
using namespace std;

class cVector3	//make a vector class
{
public:
	int x;
	int y;
	int z;
	bool operator== (const cVector3 &rhs) const	//allows for the passing of a class as a key
	{
		if (x == rhs.x && y == rhs.y && z == rhs.z)
		{
			return true;
		}
		return false;
	}
};

int main()
{
	mapClass<int, int> map(5);

	cout << "Created map of Size 5, with int as key, int as value." << endl;
	
	map.insert(5, 5);
	map.insert(6, 6);
	map.insert(7, 7);
	map.insert(8, 8);

	cout << "Added 4 values to the map." << endl;
	cout << "Find the value at key 2: " <<  map.getValueFromKey(2) << endl;

	cout << "The map's maximum size is: " << map.getMaxSize() << endl;

	map.insert(1, 1);
	map.insert(2, 2);
	map.insert(3, 3);
	map.insert(4, 4);

	cout << "Added 4 additional values to the map." << endl; //adding more increases the size of the map
	cout << "Find the value at key 7: " << map.getValueFromKey(7) << endl;
	cout << "The map's maximum size is: " << map.getMaxSize() << endl;

	cout << "Clearing map..." << endl;
	map.clearMap();

	mapClass<cVector3, string> map2(5);

	cout << "Created map of Size 5, with class as key, string as value." << endl;

	cVector3 vectorOne;
	vectorOne.x = 1;
	vectorOne.y = 2;
	vectorOne.z = 3;
	cVector3 vectorTwo;
	vectorTwo.x = 4;
	vectorTwo.y = 5;
	vectorTwo.z = 6;

	cout << "Adding two Key Value Pairs to current map." << endl;
	map2.insert(vectorOne, "vectorOne");
	map2.insert(vectorTwo, "vectorTwo");

	cout << "Get value using the vector vector class as key." << endl;
	cout << "Value is: " << map2.getValueFromKey(vectorTwo) << endl;

	cout << "Erasing value at the same key... " << endl;
	map2.eraseAtKey(vectorTwo);

	cout << "Created map of Size 10, with float as key, double as value." << endl;

	mapClass<float, double> map3(10);
	map3.insert(1.5f, 2.0);
	map3.insert(2.5f, 4.0);
	map3.insert(3.5f, 6.0);
	map3.insert(4.5f, 8.0);
	map3.insert(5.5f, 10.0);
	map3.insert(6.5f, 12.0);

	cout << "Set iterator to the beginning." << endl;
	map3.iteratorBegin();

	cout << "Output every second value using the iterator." << endl;
	for (int i = 0; i < 2; i += 2)
	{
		cout << "Value: " << map3.getValueIterator() << endl;
		map3.advanceIterator(2);
	}

	cout << "Make iterator reverse, (reversing the order of the values)." << endl;
	map3.reverseIterator();
	map3.iteratorBegin();
	for (int i = 0; i < map3.getSize(); i++)
	{
		cout << "Value: " << map3.getValueIterator() << endl;
		map3.advanceIterator(1);
	}

	system("pause");
	return 0;
}
