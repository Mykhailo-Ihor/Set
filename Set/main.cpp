#include "Set.h"

int main()
{
	int arr[11] = { 1,3,3,2,5,6,10,9,8,7,4 };
	Set<int> set(arr,11);
	set.print_all();
	int arr2[5] = { 1,11,5,7,8 };
	Set<int>set2(arr2, 5);
	set2.print_all();
	set = set.set_union(set2);
	set.print_all();
	return 0;
}