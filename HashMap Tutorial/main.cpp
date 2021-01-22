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

	std::cout << map[1 ] << std::endl;
	std::cout << map[2 ] << std::endl;
	std::cout << map[3 ] << std::endl;
	std::cout << map[4 ] << std::endl;
	std::cout << map[5 ] << std::endl;
	std::cout << map[6 ] << std::endl;
	std::cout << map[7 ] << std::endl;
	std::cout << map[8 ] << std::endl;
	std::cout << map[9 ] << std::endl;
	std::cout << map[10] << std::endl;
	std::cout << map[11] << std::endl;
	std::cout << map[12] << std::endl;
	std::cout << map[13] << std::endl;
	std::cout << map[14] << std::endl;
	std::cout << map[15] << std::endl;
	std::cout << map[16] << std::endl;
	std::cout << map[17] << std::endl;
	std::cout << map[18] << std::endl;
	std::cout << map[19] << std::endl;

	map.Remove(1);
	map.Remove(2);
	map.Remove(3);
	map.Remove(4);
	map.Remove(5);
	map.Remove(6);

	std::cout << map[1 ] << std::endl;
	std::cout << map[2 ] << std::endl;
	std::cout << map[3 ] << std::endl;
	std::cout << map[4 ] << std::endl;
	std::cout << map[5 ] << std::endl;
	std::cout << map[6 ] << std::endl;
	std::cout << map[7 ] << std::endl;
	std::cout << map[8 ] << std::endl;
	std::cout << map[9 ] << std::endl;
	std::cout << map[10] << std::endl;
	std::cout << map[11] << std::endl;
	std::cout << map[12] << std::endl;
	std::cout << map[13] << std::endl;
	std::cout << map[14] << std::endl;
	std::cout << map[15] << std::endl;
	std::cout << map[16] << std::endl;
	std::cout << map[17] << std::endl;
	std::cout << map[18] << std::endl;
	std::cout << map[19] << std::endl;

	map.Clear();

	std::cout << map[1 ] << std::endl;
	std::cout << map[2 ] << std::endl;
	std::cout << map[3 ] << std::endl;
	std::cout << map[4 ] << std::endl;
	std::cout << map[5 ] << std::endl;
	std::cout << map[6 ] << std::endl;
	std::cout << map[7 ] << std::endl;
	std::cout << map[8 ] << std::endl;
	std::cout << map[9 ] << std::endl;
	std::cout << map[10] << std::endl;
	std::cout << map[11] << std::endl;
	std::cout << map[12] << std::endl;
	std::cout << map[13] << std::endl;
	std::cout << map[14] << std::endl;
	std::cout << map[15] << std::endl;
	std::cout << map[16] << std::endl;
	std::cout << map[17] << std::endl;
	std::cout << map[18] << std::endl;
	std::cout << map[19] << std::endl;

	return 0;
}