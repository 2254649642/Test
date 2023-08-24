#include <iostream>
#include <typeinfo>

using namespace std;

template<typename T, int SIZE> 
void sort(T arry[]) {
	for (int i = 0; i < SIZE - 1; i++) {
		for (int j = 0; j < SIZE - 1 - i; j++) {
			if (arry[j] < arry[j + 1]) {
				swap(arry[j + 1], arry[j]);
			}
		}
	}
}

int main()
{
	int arry[6] = { 5, 2,7,1,5,3 };
	sort<int, 6>(arry);


	return 0;
}
