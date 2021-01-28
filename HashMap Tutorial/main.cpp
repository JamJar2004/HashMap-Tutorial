#include <iostream>
#include <string>
#include "hashMap.hpp"

int main()
{
	HashMap<int, std::string> map;
	map.Place(1, "A");
	map.Place(2, "B");
	map.Place(3, "C");
	map.Place(4, "D");
	map.Place(5, "E");
	map.Place(6, "F");

	map[7 ] = "G";
	map[8 ] = "H";
	map[9 ] = "I";
	map[10] = "J";
	map[11] = "K";
	map[12] = "L";
	map[13] = "M";
	map[14] = "N";
	map[15] = "O";
	map[16] = "P";
	map[17] = "Q";
	map[18] = "R";
	map[19] = "S";

	for(int key : map.GetKeys())
		std::cout << map[key] << std::endl;

	map.Remove(1);
	map.Remove(2);
	map.Remove(3);
	map.Remove(4);
	map.Remove(5);
	map.Remove(6);

	for(int key : map.GetKeys())
		std::cout << map[key] << std::endl;

	map.Clear();

	for(int key : map.GetKeys())
		std::cout << map[key] << std::endl;

	return 0;
}