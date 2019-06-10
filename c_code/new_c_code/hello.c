/*
 * hello.c
 *
 *  Created on: Mar 29, 2017
 *      Author: wmamun
 */
#include <stdio.h>
#include <stdint.h>
#include "data_struct.h"
#include <string.h>
#include <stdlib.h>
#define MAX_ENTRY 10

int unsort_arr[MAX_ENTRY]  = {10,5,9,2,4,6,7,1,3,8};
int un_heap_arr[MAX_ENTRY+1] = {-1,16,4,10,14,7,9,3,2,8,1};
List *head_ptr;
Tree *root_ptr;
int freq_count[11]; // for 0...11
int lin_unsort_arr[MAX_ENTRY+1]  = {-1,9,5,9,7,4,6,3,1,3,3};
int lin_sort_arr[MAX_ENTRY+1] = {-1};

#define swap(a,b)  \
	(a) = (a)^(b)  \
    (b) = (a)^(b)  \
    (a) = (a)^(b)

void count_sort (int arr[],int size){

	int i    = 0;

	for (i = 0;i < 11; i++) {
		freq_count[i] = 0;
	}
	// count frequency
	for (i = 1;i < size; i++) {
		freq_count[arr[i]]++;
	}
	// cumalate freq so that we know for each value i where it
	// needs to be inserted in the sorted array
	for (i = 1; i < 11; i++) {
		freq_count[i] = freq_count[i-1] + freq_count[i];
	}
	// insert the item in proper position in sorted array using the position from
	// freq_count array. We start from array size and decrement cause we want to keep the
	// order of the element in the array meaning same value array will appear in same order
	// this property of maintaining the order is called stable sort
	for (i = size-1; i >= 1; i--) {
		lin_sort_arr[freq_count[arr[i]]] = arr[i];
		freq_count[arr[i]]--;
	}

}


void print_arr (int arr[],int size) {
	int i=0;
	for (i = 0; i < size; i++) {
		printf("%d ",arr[i]);
	}
	printf("\n");
}

void bub_sort (int arr[],int size) {
	int i   = 0;
	int j   = 0;
	int tmp = 0;
    // move the smallest element to a[i] position
	// at each iteration of the outer loop
	for (i = 0; i < size; i++) {
		for (j = i+1; j < size ;j++) {
			if (arr[i] >= arr[j] ) {
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}

}

void insert_sort (int arr[],int size) {
	int i   = 0;
	int j   = 0;
	int tmp = 0;
	// we start from 1 so that the initial boundary is (0,1)
	// and everything will be sorted between them, so for each ith postion
	// 0 to i-1 pos are sorted and we insert the ith element in right position and get
	// 0 to i sorted elems
	for (i = 1; i < size; i++) {
		tmp = arr[i];
		for (j = i; j >= 0; j--){
			// we move every element which is greater than tmp to the right and find the position
			// to insert tmp at right position. j denotes the postion to enter tmp
			if ( j && (tmp <= arr[j-1])) {
				arr[j] = arr[j-1];
			} else{
				break;
			}
		}
		arr[j] = tmp;
	}
}
// Here p ,q and r are indices speacially r is the last index in the array
void merge_arr (int arr[], int p,int q,int r) {

	int left[MAX_ENTRY];
	int right[MAX_ENTRY];
	int i         = 0;
	int j         = 0;
	int k         = 0;
	int len_left  = 0;
	int len_right = 0;

#define INFINITY 10000
	for (i = 0; i<MAX_ENTRY; i++) {
		left[i] = right[i] = INFINITY;
	}

	for (i = p, j = 0 ; i <= q; i++) {
		left[j++] = arr[i];
	}
	len_left = j;

	for (i = q+1, j = 0; i<=r; i++ ) {
		right[j++] = arr[i];
	}
	len_right = j;

	j = k = 0;
	for (i = p; i <= r; i++) {
		if (left[j] <= right[k] && j < len_left) {
			arr[i] = left[j++];
		} else {
			if (k < len_right)
				arr[i] = right[k++];
		}
	}
}
// Here p  is the starting index and r is the end index not size
void merge_sort (int arr[],int p,int r) {
	int q = 0;
	if ( p < r) {
		q = (p+r)/2;
		printf ("%u %u : %u %u\n",p,q,q+1,r);
		merge_sort(arr,p,q);
		merge_sort(arr,q+1,r);
		merge_arr(arr,p,q,r);
	}

}

#define left_child(i)   ((i) << 1)
#define right_child(i)  (((i) << 1) + 1)
#define parent(i) ((i) >> 1)

void max_heapify (int arr[],int i) {

	uint32_t largest = i;
	uint32_t left    = left_child(i);
	uint32_t right   = right_child(i);
	uint32_t temp    = 0;

	if (left < MAX_ENTRY && arr[i] < arr[left]) {
		largest = left_child(i);
	}
	if (right < MAX_ENTRY && arr[largest] < arr[right]) {
		largest = right_child(i);
	}
	if (i != largest) {
		temp = arr[largest];
		arr[largest] = arr [i];
		arr[i] = temp;
		max_heapify(arr, largest);
	}
}

void build_max_heap(int arr[],int size) {

	int i = 0;
	for (i = size/2; i >= 1 ; i--) {
		max_heapify(arr,i);
	}
}
void heap_sort(int arr[], int size) {

	int i   = size;
	int tmp = 0;

	build_max_heap(arr,size);
	for (i = size; i>=2 ; i--) {
		tmp = arr[1];
		arr[1] = arr[i];
		arr[i] = tmp;
		max_heapify(arr,1);
	}
}
int partition (int arr[],int p,int r) {

	int x = arr[r];
	int j = p;
	int i = p-1;
	int tmp;
    // we move all element <= x to the left side and
	// all elem > x to the right
	// Note: we have to loop from p to r-1,
	// r-1 is the element before r and we have to loop to r-1
	// so the loop breaking condition is "j <= r-1"
	for (j = p;j <= r-1;j++) {
		if(arr[j] <= x) {
			i++;
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
	}
	// finally move x to its right position and return the position to qsort
	i++;
	tmp = arr[i];
	arr[i] = arr[r];
	arr[r] = tmp;
	return i;


}
void q_sort (int arr[],int p,int r) {
    // get q value from partition after partion all value <= q will be left of q
	// and all val > q will be right of q
	int q = 0;
	// if p >= r we have the minimal array which is sorted by default
	// this could be use as the recursion termination condition
	if (p < r) {
		q = partition(arr,p,r);
		// now we recursively sort the subarr[p ,q-1] and arr[q+1,r]
		// note a[q] is in right position
		q_sort(arr,p,q-1);
		q_sort(arr,q+1,r);
	}
}

int main (){

	//printf("Before \n");
	//print_arr(unsort_arr, MAX_ENTRY);
	//bub_sort(unsort_arr, MAX_ENTRY);

	//insert_sort(unsort_arr, MAX_ENTRY);
	//printf("After Insert Sort\n");
	//merge_sort(unsort_arr, 0,9);
	//build_max_heap(un_heap_arr , MAX_ENTRY);
	//printf("After build heap\n");
	//print_arr(un_heap_arr, MAX_ENTRY+1);
#define LIST_TEST 1
#define QSORT_TEST 2
#define CSORT_TEST 3
#define CREATE_BST_TEST 4
#define CREATE_ARR_TEST 5
#define NEW_ARR_TEST 6
	uint32_t data,opt;
	List *elem;
	opt = NEW_ARR_TEST;
	switch (opt) {

	case LIST_TEST:
	{
		printf("List test\n");

	    for (int i = 1 ; i<=2; i++){
			//insert_at_head(&head_ptr,data);
	    	scanf("%u",&data);
			insert_at_head(&head_ptr,data);
		}
		print_list(&head_ptr);
		/*printf ("Search ?\n");
		data = 5;
		//scanf("%u",&data);
		elem = find_entry(&head_ptr, data);

		if (elem)
			printf("Found %u\n",elem->data);
		delete_from_list_unsorted(&head_ptr, data);
		print_list(&head_ptr);
		printf("Exiting test code\n");*/

        if (list_palindrome(&head_ptr)) {
        	printf("Yes\n");
        } else {
        	printf("NO\n");
        }

		break;
	}
	case QSORT_TEST:
	{
		printf("QSort test\n");
		printf("Before \n");
		print_arr(unsort_arr, MAX_ENTRY);
		q_sort(unsort_arr,0,MAX_ENTRY-1);
		printf("After \n");
		print_arr(unsort_arr, MAX_ENTRY);
		break;
	}
	case CSORT_TEST:
	{
		printf("CSort test\n");
		printf("Before \n");
		print_arr(lin_unsort_arr, MAX_ENTRY+1);
		count_sort(lin_unsort_arr,11);
		printf("After \n");
		print_arr(lin_sort_arr, MAX_ENTRY+1);
		break;
	}
	case CREATE_BST_TEST:
	{
		printf("Create BST test\n");
		q_sort(unsort_arr,0,MAX_ENTRY-1);
		printf("Sorted Array \n");
		print_arr(unsort_arr, MAX_ENTRY);

		root_ptr = create_bstree(unsort_arr,0,MAX_ENTRY-1);
		if (root_ptr) {
			printf("root %u\n",root_ptr->data);
			printf("InOrder : ");
			in_order_traversal(root_ptr);
			printf("\n");

			printf("PreOrder : ");
			pre_order_traversal(root_ptr);
			printf("\n");

			printf("PostOrder : ");
			post_order_traversal(root_ptr);
			printf("\n");
		}
		break;
	}
	case CREATE_ARR_TEST:
	{
		/*char *input_str1 = NULL;
		//char *input_str2 = NULL;
		size_t sz_s1 = 0;
		//size_t sz_s2 = 0;
		// here getsline is used becasue gets is not a safe function its does not specify or check buffer size
		// which could cause serious prblems
		getline(&input_str1, &sz_s1,stdin);
		//getline(&input_str2, &sz_s2,stdin);
		//int edit = one_edit(input_str1,input_str2);
		//int palindrom = is_palindrom_bit(input_str1);
		if(input_str1[strlen(input_str1)-1] == '\n')
			input_str1[strlen(input_str1)-1] = '\0';
		compressed(input_str1);
		free(input_str1);
		//free(input_str2);*/

		/*int a2d[4][4] = {{1,2,3,4},
		                 {5,6,7,8},
						 {9,10,11,12},
						 {13,14,15,16}};
		rotate90(a2d,4);*/
		int arr[7] = { 10, 3, 6, 8, 9, 4, 3 };
		max_diff(arr,7);


		break;

	}
	case NEW_ARR_TEST:
	{
		struct ListNode *L1 = NULL;
		struct ListNode *L2 = NULL;
		struct ListNode *sum = NULL;
		int arr1 [5] = {1,2,3};
		int arr2 [5] = {6,7,8,9,9};
		L1 = create_from_array (arr1,3);
		L2 = create_from_array (arr2,5);
        sum = addTwoNumbers(L2,L1);
        printf("Hello!\n");
		char str[100];
		strcpy(str,"abdcdclmnop");
        int len = lengthOfLongestSubstring(str);
        printf(" len = %d \n",len);

	}


	}
	return 0;
}
