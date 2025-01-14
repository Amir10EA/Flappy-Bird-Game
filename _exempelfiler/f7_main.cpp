/*
1) 'Text.cpp' placeras i 'src/', 'Text.h' placeras i 'include/'
2) Detta exempel använder std::strncpy() istället för strcpy_s()
*/

#include "Text.h"
#include <iostream>

using namespace std;

void funk(Text t2) {

}

int main() {
	Text t1("Jozef");
	Text t3("Stefan");
	Text t4;

	t3 = t1;
	t3[2] = 's';
	for (int i = 0; i < t3.length(); i++){
		cout << t3[i];
	}
	cout << endl;
	cin.get();
	
}