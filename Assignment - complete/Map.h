#pragma once

#include <iostream>
using namespace std;

//structs
template <typename tKey, typename tValue>
struct sKeyValuePair
{
	tKey key;
	tValue value;

};

enum eDirection {forward, backward};

template <typename tKey, typename tValue>
struct sIterator	//holds the position in a list
{
	sKeyValuePair<tKey, tValue> keyValPair;
	int position;
	 eDirection direction;

};

template <typename tKey, typename tValue>
class mapClass
{
private:
	sKeyValuePair<tKey, tValue>* arr;	//holds the dynamically sized array - what the class will be based of
	sIterator<tKey, tValue> iterator;
	int maxSize; 
	int currentSize;

public:
	mapClass(int size); //when creating it, give it size (how big the array will be)
	~mapClass();

	void insert(tKey key, tValue value);
	tValue getValueFromKey(tKey key);
	void eraseAtKey(tKey key);
	int getSize();
	int getMaxSize();
	void clearMap();

	tKey getKeyIterator();
	tValue getValueIterator();
	void advanceIterator(int step);
	void iteratorBegin();
	void iteratorEnd();
	void reverseIterator();

};

template <typename tKey, typename tValue>
mapClass<typename tKey, typename tValue>::mapClass(int size)	//constructor - sets size and the current size as given by the user
{
	currentSize = 0;
	maxSize = size;
	arr = new sKeyValuePair <tKey, tValue>[size];
}

template <typename tKey, typename tValue>
mapClass<typename tKey, typename tValue>::~mapClass()	//deconstructor - deletes the array to keep class memory safe
{
	delete[] arr;
}

template<typename tKey, typename tValue>
void mapClass<typename tKey, typename tValue>::clearMap()	//resets all values to default, deletes the original array, creates a new array of maximum size
{
	currentSize = 0;
	delete[] arr;
	arr = new sKeyValuePair<tKey, tValue>[maxSize];
}

template <typename tKey, typename tValue>
void mapClass<typename tKey, typename tValue>::insert(tKey key, tValue value)	//adding new values to the map
{
	bool found = false;
	for (int i = 0; i < currentSize; i++)	//if key is NOT unique, do not add it to the list
	{
		if (arr[i].key == key)
		{
			found = true;
			break;
		}
	}
	if (!found)
	{
		if (currentSize < maxSize)	//adds values to array as normal
		{
			arr[currentSize].key = key;
			arr[currentSize].value = value;
			currentSize++;
		}

		else    //if the array is full, dynamically increase the size
		{
			sKeyValuePair<tKey, tValue>* temp = new sKeyValuePair<tKey, tValue>[maxSize];

			for (int i = 0; i < maxSize; i++) //copy the original array into temporary array
			{
				temp[i] = arr[i];
			}

			maxSize++;
			delete[] arr; //free memory
			arr = new sKeyValuePair<tKey, tValue>[maxSize];	//take the original array and re-adjust to the new size
			for (int i = 0; i < maxSize; i++)	//copy the array into the new size
			{
				arr[i] = temp[i];
			}

			arr[currentSize].key = key;	//adds values to array as normal
			arr[currentSize].value = value;
			currentSize++;
			delete[] temp;	//deletes temporary when it is no longer used to keep memory sage
		}
	}	
}

 template <typename tKey, typename tValue>
 tValue mapClass<typename tKey, typename tValue>::getValueFromKey(tKey key)		//retrieves value from user given key
 {
	 for (int i = 0; i < currentSize; i++)
	 {
		 if (arr[i].key == key)
		 {
			 return arr[i].value;	//returns value if the key has been found, if not nothing is returned
		 }
	 }

	 return NULL;
 }

 template <typename tKey, typename tValue>
 void mapClass<typename tKey, typename tValue>::eraseAtKey(tKey key)	//removes value at given key and condences the existing data, so as not to have gaps in the map
 {
	 for (int i = 0; i < currentSize; i++)
	 {
		 if (arr[i].key == key)
		 {
			 for (int j = 0; j < currentSize - 1; j++)
			 {
				 arr[j].key = arr[j + 1].key;
				 arr[j].value = arr[j + 1].value;	//after data has been deleted, move consecutive pairs back one space
			 }
		 }
	 }
 }


 template <typename tKey, typename tValue>
 int mapClass<typename tKey, typename tValue>::getSize()	//returns the current size of the array
 {
	 return currentSize;
 }

 template <typename tKey, typename tValue>
 int mapClass<typename tKey, typename tValue>::getMaxSize()	//returns the maximum size of the array
 {
	 return maxSize;
 }

 template <typename tKey, typename tValue>
 tKey mapClass<typename tKey, typename tValue>::getKeyIterator()	//retrives the key at the iterator position
 {
	 return arr[iterator.position].key;
 }

 template <typename tKey, typename tValue>
 tValue mapClass<typename tKey, typename tValue>::getValueIterator()	//retrives the value at the iterator position
 {
	 return arr[iterator.position].value;
 }

 template <typename tKey, typename tValue>
 void mapClass<typename tKey, typename tValue>::advanceIterator(int steps)	//steps the iterator by the defined amount in the direction of the iterator type (forward or backward)
 {
	 if (iterator.direction == eDirection::forward)
	 {
		 iterator.position += steps;
		 if (iterator.position >= currentSize)	//if it has reached the limit, do not let it continue
		 {
			 iterator.position = currentSize - 1;
		 }
	 }
	 
	 else
	 {
		 iterator.position -= steps;
		 if (iterator.position < 0) //if it has reached the limit, do not let it continue
		 {
			 iterator.position = 0;
		 }
	 }
	 
 }

 template <typename tKey, typename tValue>
 void mapClass<typename tKey, typename tValue>::iteratorBegin()	//sets iterator to start position dependent on position
 {
	 if (iterator.direction == eDirection::forward)
	 {
		 iterator.position = 0;
	 }
	 else if (iterator.direction == eDirection::backward)
	 {
		 iterator.position = currentSize - 1;
	 }
 }

 template <typename tKey, typename tValue>
 void mapClass<typename tKey, typename tValue>::iteratorEnd()	//sets iterator to end position dependent on position
 {
	 if (iterator.direction == eDirection::forward)
	 {
		 iterator.position = currentSize - 1;
	 }
	 else if (iterator.direction == eDirection::backward)
	 {
		 iterator.position = 0;
	 }
 }

 template <typename tKey, typename tValue>
 void mapClass<typename tKey, typename tValue>::reverseIterator()	//changes the direction of the iterator
 {
	 if (iterator.direction == eDirection::forward)
	 {
		 iterator.direction = eDirection::backward;
	 }
	 else if (iterator.direction == eDirection::backward)
	 {
		 iterator.direction = eDirection::forward;
	 }
 }
