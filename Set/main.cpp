#include "Set.h"

int main()
{
	int arr[11] = { 1,3,3,2,5,6,10,9,8,7,4 };
	Set<int> mySet(arr,11);
	/*mySet.add(3).add(1).add(2);*/
	mySet.print_all();
}