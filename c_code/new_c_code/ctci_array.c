/*
 * ctci_array.c
 *
 *  Created on: Jun 10, 2017
 *      Author: wmamun
 */
#include <stdio.h>
#include <stdlib.h>
#include "data_struct.h"
#include <string.h>

#define is_upper(ch) ((ch)>='A' && (ch)<='Z')
#define is_lower(ch)  ((ch)>='a' && (ch)<='z')
#define is_char(ch) (is_upper((ch)) || is_lower((ch)))
#define to_upper(ch) ((ch)-'a' + 'A')
#define to_lower(ch) ((ch)-'A' + 'a')
#define STACK_SIZE 20

int frequency [256];
int top;
int stack_min = 10000;
Stack stack[STACK_SIZE];

int is_unique (char *str) {
	if(!str)
		return 1;
	while(*str) {
		if(is_lower(*str)){
			*str = to_upper(*str);
		}
		if (frequency[(int)*str] == 0 )
			frequency[(int)*str]++;
		else
			break;
		str++;
	}
	if(*str) {
		return 0;
	}
	else
		return 1;

}

int is_permutation(char *str1, char *str2) {

	if (strlen(str1)!=strlen(str2))
		return 0;
	while(*str1) {
		frequency[*str1]++;
		frequency[*str2]--;
		str1++;
		str2++;
	}
	for (int i = 0; i < 256; i++) {
		if (frequency[i])
			return 0;
	}
	return 1;


}
int is_palindrom(char *str) {

	int count = 0;
	while(*str) {
		if (is_char(*str)) {
			frequency[*str]++;
		}
		str++;
	}
	for (int i = 0; i < 256; i++) {
		if (frequency[i] % 2 !=0 )
			count++;
	}
	if (count > 1)
		return 0;
	else
		return 1;

}
int is_one_bit_set(uint32_t bitmap) {
	// only one bit set, for example if bitmap is 000100 and bitmap-1 000011
	// now 000100 & 000011 equals zero , so if one bit is set it will return zero
	// otherwise return non zero
	return !((bitmap & (bitmap-1)));

}
int is_palindrom_bit(char *str) {

	uint32_t char_set_bit = 0; // bitmap for char in string
	uint32_t char_mask = 0 ;
	uint8_t num_val;

	while(*str) {
		if (is_char(*str)) {
			char_mask = 1;
			*str = to_upper(*str);
			num_val = (uint8_t)((*str) - 'A');
			char_mask = char_mask << num_val;
			// setting the char bit mask for the char in the string
			if (char_set_bit & char_mask) {
				// the bit is set and we encounter the same char again we need to unset this bit
				char_set_bit = char_set_bit & ~char_mask;

			} else {
			    // the bit is not set so set the bit
				char_set_bit = char_set_bit | char_mask;
			}
			printf("char set bit 0x%x\n",char_set_bit);
		}
		str++;
	}
	printf("char set bit 0x%x\n",char_set_bit);
	if (char_set_bit) {
		// the bitmap is nonzero,
		// if only one bit is set in bitmap then its palindrome otherwise not
		return (is_one_bit_set(char_set_bit));
	} else {
		// if the bit map  is zero then we have even count for all chars in the string
		// so this is a palindrome
		return 1;
	}

}

int is_insert_or_delete(char *str1, char *str2) {

	int count = 0;
    // move str1 & str2 if both maches if not only move str1, this can only happen once for one edit
	while (*str1) {

		if (*str1 != *str2) {
			str1++;
			count++;
			if (count > 1) {
				return 0;
			}
			continue;
		}
		str1++;
		str2++;
	}

	return 1;
}
int is_replace (char *str1, char *str2) {

	int count = 0;

	while(*str1){
		if (*str1 != *str2) {
			count++;
			if( count > 1) {
				return 0;
			}
		}
		str1++;
		str2++;
	}
	return 1;
}

int one_edit (char *str1, char *str2) {

	int len1 = strlen(str1);
	int len2 = strlen(str2);

    if(abs(len1 -len2) >= 2)
    	return 0;
	if(len1 == len2 ) {
		return is_replace(str1,str2);
	} else if (len1 > len2) {
		return is_insert_or_delete(str1,str2);
	} else {
		return is_insert_or_delete(str2,str1);
	}
}

void compressed(char *str) {
    //assuming max char length wont be more than 100
	char compressed_str[200];
	int  str_count[200];
	char next_ch                 = *str;
	char current_ch              = 0;
	int count                    = 0;
	int non_single_flag          = 0;
	char *str_st                 = str;
	int i                        = 0;

	for(int j=0; j<200; j++)
		str_count[j]=compressed_str[j] = 0;

	while (*str) {
		current_ch = *str;
		next_ch = *(str+1);
		count++;
		if(current_ch != next_ch) {
			if(count > 1) {
				non_single_flag = 1;
			}
			compressed_str[i] = current_ch;
			str_count[i] = count;
			count = 0;
			i++;
		}
		str++;
	}

	if (!non_single_flag) {
		printf("%s",str_st);
		printf("\n");
		return;
	}
	for (int j = 0; j < i; j++) {
		printf("%c%d",compressed_str[j],str_count[j]);
	}
	printf("\n");


}

void print2darr(int a[][4],int size){
	int i = 0;
	int j = 0;

	for (i = 0; i < size; i++) {
		for(j = 0; j < size; j++) {
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}
}

void
rotate90 (int a[][4],int size) {

	int i      = 0;
	int layer  = 0;
	int first  = 0;
	int last   = 0;
	int offset = 0;
	int temp   = 0;

    print2darr(a,size);
    printf("\n");

    for (layer = 0; layer < size/2; layer++) {
    	first = layer;
    	last = size - 1 - first;
    	for (i = first; i < last; i++) {
    		offset                 = i - first;
    		temp                   = a[first][i];
    		a[first][i]            = a[last-offset][first];
    		a[last-offset][first]  = a[last][last-offset];
    		a[last][last-offset]   = a[i][last];
    		a[i][last]             = temp;
    	}
    }


	print2darr(a,size);

}

void
null_row (int a[][4], int row, int size) {
	int i = 0;
	for (i = 0 ; i < size; i++){
		a[row][i] = 0;
	}
}

void
null_col (int a[][4], int col, int size) {
	int i = 0;
	for (i = 0 ; i < size; i++){
		a[i][col] = 0;
	}
}

void
make_zero (int a[][4],int size) {
	int first_row = 0;
	int first_col = 0;

	for (int i = 0; i<size ; i++) {
		if (!a[0][i]) {
			first_row = 1;
		}
		if (!a[i][0]) {
			first_col = 1;
		}
	}
	for (int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			if (!a[i][j]) {
				a[i][0] = 0;
				a[0][j] = 0;
			}
		}
	}
	for (int i = 0; i < size; i++) {
		if (!a[0][i]) {
			null_col(a,i,size);
		}
		if (!a[i][0]) {
			null_row(a,i,size);
		}
	}

	if (first_row) {
		null_row(a,0,size);
	}
	if (first_col) {
		null_col(a,0,size);
	}


}

/*
 * The basic idea here is to start with a difference and a low_point
 * an move along the array to find a bigger difference, if at any time we
 * found a point lower than the low_point we update the low and hope to find
 * a bigger difference in the rest of the array. Note that after updating the low_point
 * with a lower value we have to continue search for  a bigger difference than
 * the current difference if not the older difference was the biggest difference.
 * */
void
max_diff(int arr[], int size) {

	int i          = 0;
	int low        = 0;
	int diff       = 0;
	int curr_diff  = 0;

	low = arr[0];
	for (i = 0; i< size; i++) {
       // get the current diff
		curr_diff = arr[i]-low;
		// update the diff iff the current_diff is greater than diff
		if (curr_diff > diff)
			diff = curr_diff;
		// if the current diff is negative that arr[i] must be lower that low
		if (curr_diff < 0)
			low = arr[i];
	}
	printf ("Diff = %d \n",diff);

}

int is_empty_stack (){
	return (top == -1) ? 1:0;
}
int is_full_stack (){
	return (top == (STACK_SIZE - 1)) ? 1:0;
}
void push (Stack item) {
	top++;
	if (is_full_stack()) {
		printf("Stack is Full\n");
		top--;
		return ;
	}
	if (item.data < stack_min) {
		stack_min = item.data;
	}
	item.min = stack_min;
	stack[top] = item;

}
int stack_minimun (){
	if (is_empty_stack()){
		printf("EMpty stack\n");
		return -1;
	}
	return stack[top].min;
}
int pop () {

	int data = -1;

	if(is_empty_stack()) {
		printf("Stack is empty\n");
		return -1;
	}
	data = stack[top].data;
	top--;
	if (!is_empty_stack())
		stack_min = stack[top].min;
	else
		stack_min = 10000;
	return data;


}

void remove_dup (char* str) {
	long unsigned int frequency = 0;
	int i = 0;
	int j = 0;
	long unsigned int val = 1;

	for(i = 0; str[i]!='\0'; i++) {
		// set the bit depending on that char position
		frequency |= (val << (str[i]-'a'));
	}
    printf("freq 0x%lx\n",frequency);
	for(i = 0; str[i]!='\0'; i++) {
		val = 0;
		val = 1 << (str[i] - 'a');

		if (val & frequency) {
			frequency &= ~val;
			str[j++] = str[i];
		}

	}
	str[j] ='\0';

}

void lower(char *str) {

	int i = 0;
	for (i = 0; str[i]!='\0'; i++) {
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = str[i]- 'A' +'a';
	}
}
long unsigned int freq_set (char* str){
	long unsigned int freq = 0;
	int i = 0;
	for (i = 0; str[i]!='\0'; i++) {
		if (str[i] != ' ')
			freq |= 1 << (str[i] - 'a');
	}
	return freq;
}

// this a VERY INCORRECT way to check anagram it wont work
// because what if we have multiple occurances (more than two) of the same letter
int is_anagram (char* str1, char *str2) {

	unsigned long int freq1 = 0;
	unsigned long int freq2 = 0;
	lower(str1);
	lower(str2);
	printf ("str1 %s  str2 %s",str1,str2);
	freq1 = freq_set(str1);
	freq2 = freq_set(str2);
	if (freq1 == freq2)
		return 1;
	else
		return 0;
}
int index_arr[128];
int lengthOfLongestSubstring(char* s) {
	int max_len = 0;
	int i = 0, j = 0;
    int n  = strlen(s);
	for(i=0; j<n;j++) {
		i = (index_arr[(int)(s[j])] >= i ? index_arr[(int)(s[j])]:i);
		max_len = (max_len >= j-i+1 ? max_len : j-i+1);
		index_arr[(int)(s[j])] = j+1;
	}
	return max_len;
}
