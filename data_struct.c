/*
 * data_struct.c

 *
 *  Created on: May 29, 2017
 *      Author: wmamun
 */
#include <stdio.h>
#include <stdlib.h>
#include "data_struct.h"
#define GET_MAX(a,b) ((a) > (b) ? (a):(b))
#define GET_MIN(a,b) ((a) < (b) ? (a):(b))

// insert data at the head
void
insert_at_head(List **head,uint32_t data) {
    // We can always insert at head ,
	// it does not matter if the list is empty or not
	// both cases the data is inserted at the head and the new elem->next
	// points to where head was pointing and after we update head
	List *elem = NULL;
	elem = (List*) malloc(1*sizeof(List));
	elem->data = data;
	elem->next = *head;
	*head = elem;
	printf("inserted data %u\n",data);
}

void
print_list(List **head) {
	List *elem = *head;
	while (elem) {
		printf("%u --> ",elem->data);
		elem = elem->next;
	}
	printf("null\n");
}

// find an entry in list
List*
find_entry(List **head,uint32_t data) {

	List *elem = *head;
	// case 1 empty list
	if (!elem)
		return NULL;
	// case 2 non empty list we move elem pointer to point to the  elemnet
	// we are searching for if the list does not contain it elem points to null
	while (elem && elem->data != data) {
		elem = elem->next;
	}
	return elem;
}

void
insert_into_sorted_list(List **head, uint32_t data) {

	List *elem    = NULL;
	List *prev    = NULL;
	List *pos     = NULL;

	elem = (List*) malloc(1*sizeof(List));
	elem->data = data;
	elem->next = NULL;

	// case 1 empty list or item needs to be inserted  only @ head
	if ( *head == NULL || (*head)->data > data) {
		elem->next = *head;
		*head = elem;
		printf("inserted %u\n",data);
		return;
	}
	// case 2 list not empty and the element will not be inserted @ head
	// at this point there are atlest two entries in the list
	// update the prev & pos pointer
	prev = *head;
	pos = prev->next;
	// find the position in the list after which the data will be inserted
	while (pos && pos->data <= data) {
		prev = prev->next;
		pos = pos->next;
	}
	// now pos points to either null or the data bigger than inserted data
	elem->next = pos;
	prev->next = elem;
	printf("inserted %u\n",data);

}

int
delete_from_list_unsorted(List **head, uint32_t data) {

	List *prev = NULL;
	List *pos  = NULL;

	// case 1 empty list
	if (!*head) {
		printf ("Empty list!\n");
		return 0;
	}
	// case 2 delete the entry pointed by head
	// in this case the list is not empty
	prev = *head;
	pos = prev->next;
	if (prev->data == data) {
		*head = pos;
		free(prev);
		printf("Deleted %u\n",data);
		return 1;
	}
	// the entry to be deleted is not @ head
	// we search in the list for the data to be deleted
	// pos will point to data and prev will pointy to
	// previous element
	while (pos && pos->data != data) {
		pos = pos->next;
		prev = prev->next;
	}
	// found the data to be deleted
	if (pos) {
		prev->next = pos->next;
		free(pos);
		printf("Deleted %u\n",data);
		return 1;
	} else { //no entry found for the data, nothing to delete
		printf("Entry not found %u\n",data);
		return 0;
	}

}

// This will create a binary tree given a sorted array
// the index p, q used here must be of 'int' type
// otherwise if we go below zero for an uint  it will wrap and become a huge value
// when dealing with array index always better to use int instead of uint
Tree*
create_bstree (int arr[],int p, int q) {

	int mid        = 0;
	Tree *node     = NULL;
	// case 1: p > q so there is no mid point, no node will be created
	// and the function will return NULL
	// this is the base case of the recursion
	if (p > q) {
		return NULL;
	}
	// Now p <= q so we can get a mid and create a node
	mid = (p + q)/2;
	node = (Tree*) malloc(1*sizeof(Tree));
	if (!node) {
		printf("Mem alloc failed\n");
		return NULL;
	}
	printf("Created node %u for (%u,%u)\n",arr[mid],p,q);
    node->data = arr[mid];
    // create the left & right sub tree if it exists
    node->left = create_bstree(arr,p,mid-1);
    node->right = create_bstree(arr,mid+1,q);
    return node;
}
// traverse left subtree--> root--> right sub tree
// for a bst inorder traversal gives the sorted list of nodes
void
in_order_traversal (Tree *node) {
	if (node) {
		in_order_traversal(node->left);
		printf("%u ",node->data);
		in_order_traversal(node->right);
	}
}
// traverse root-->left subtree--> right sub tree
void
pre_order_traversal (Tree *node) {
	if (node) {
		printf("%u ",node->data);
		in_order_traversal(node->left);
		in_order_traversal(node->right);
	}
}
// traverse left subtree--> right sub tree --> root
void
post_order_traversal (Tree *node) {
	if (node) {
		in_order_traversal(node->left);
		in_order_traversal(node->right);
		printf("%u ",node->data);
	}
}

int
tree_height(Tree *node) {
	if (!node)
		return 0;
	else {
		return 1 + GET_MAX(tree_height(node->left),tree_height(node->right));
	}
}
int
tree_min_height(Tree *node) {
	if (!node)
		return 0;
	else {
		return 1 + GET_MIN(tree_height(node->left),tree_height(node->right));
	}
}

int is_balance(Tree *node){

	int min_h = 0;
	int max_h = 0;
    // get the max hieght and the min height of a tree
	// if the height diff is more than 1 its not a balanced tree
	// for a tree algo its better to draw the tree and try couple of methods
	min_h = tree_min_height(node);
	max_h = tree_height(node);

	return (((max_h - min_h) < 2 )? 1:0);
}

List*
kth_to_last (List **head ,int k)
{

	int   count      = 1;
	List  *kth       = NULL;
	List  *last      = NULL;

	if (k == 0) {
		printf("Invalid entry\n");
		return NULL;
	}

	if (*head == NULL){
		printf("Empty List\n");
		return NULL;
	}
	// using last as a runner pointer to create distance of k between last and kth
	last = *head;
	while(last->next != NULL && count < k) {
		last = last->next;
		count++;
	}
	if (count == k) {
		kth = *head;
	} else {
		printf("List is not long enough\n");
		return NULL;
	}
	while (last->next != NULL) {
		last = last->next;
		kth = kth->next;
	}

	return kth;

}
void
partition_list (List **head, int val) {

	List* prev = NULL;
	List* pos = NULL;
	List* start = *head;
	List* elem = NULL;
	int on = 1; // 1 = on = found
    // check if empty list
	if (!start) {
		printf("Empty list\n");
		return;
	}
	prev = *head;
	pos = prev->next;
	// check if one elem list if true no need to do anything
	if(!pos) {
		printf("One elem arr\n");
		return;
	}
	// the list has more than one elem
	// prev is pointing to head, pos is pointing to the 2nd elem
	while (pos) {
		if (pos->data < val) {
			//move it to head
			elem = (List*) malloc(1 * sizeof(List));
			elem->data = pos->data;
			elem->next = *head;
			*head = elem;

			// delete it as its moved to head now
			prev->next = pos->next;
			free(pos);
			pos = prev->next;
			// no need to increase pos or prev as after delete pos has moved
			// and prev is pointing to the element before pos
		} else {
			prev = prev->next;
			pos = pos->next;
		}
	}
}

int list_palindrome(List **head) {

	List *start = NULL;
	List *dbl   = NULL;
	List *rev    = NULL;
	List *elem  = NULL;

	start = *head;
	dbl = start->next;

	if(!dbl)
		return 1;


	while (dbl) {
        // add this to the head of the reverese list
		elem = (List*) malloc(1*sizeof(List));
		elem->next = rev;
		rev = elem;
		elem->data = start->data;
		// check if we can move dbl twice
		dbl= dbl->next;
		if(!dbl) {
			break;
		}

		dbl = dbl->next;
		start = start->next;
	}

	elem = rev;
	start = start->next;
	while ( start && start->data == elem->data) {
		start = start->next;
		elem = elem->next;
	}
	if (!start && !elem)
		return 1;

	return 0;
}

int list_intersection (List **l1, List **l2) {
	List *start_l1 = *l1;
	List *start_l2 = *l2;
	int len1 = 0 ;
	int len2 = 0;
	int diff = 0;

	if (!start_l1 || !start_l2)
		return 0;
	// get the length of each list
	while (start_l1->next != NULL) {
		start_l1 = start_l1->next;
		len1++;
	}
	while (start_l2->next != NULL) {
		start_l2 = start_l2->next;
		len2++;
	}
	// both pointers are at the end of list and the dont match so no intersection
	if(start_l1 != start_l2)
		return 0;
	// move the pointers back to head of each list
	start_l1 = *l1;
	start_l2 = *l2;
	// calc the diff in length and move the longer list start pointer by diff + 1
	// so that now both list length will be same and if start comparing each node
	// we will hit the intersection at the same time
	if ( len1 > len2) {
		diff = len1 - len2;
		while (diff) {
			start_l1 = start_l1->next;
			diff--;
		}
		start_l1 = start_l1->next;
	} else if (len2 < len1) {
		diff = len2 - len1;
		while (diff) {
			start_l2 = start_l2->next;
			diff--;
		}
		start_l2 = start_l2->next;
	}
	// check if any intersection by moving both pointer at same speed list length is same
	// so they must hit the intersection at same time
	while (start_l1) {
		if(start_l1 == start_l2)
			return 1;
		start_l1 = start_l1->next;
		start_l2 = start_l2->next;
	}

	return 0;

}


Graph **grph;

void init_graph(int num_nodes, int num_edges) {

	int i = 0;
	int u = -1;
	int v = -1;
	Graph *edge = NULL;

	grph = (Graph**) malloc( num_nodes *sizeof(Graph*));
    // after malloc this needs to manully set to NULL as malloc does not set to NULL
	// calloc also fails to set to NULL
	for (i = 0 ; i <num_nodes; i++ )
		grph[i] = NULL;


	for (i = 1; i <= num_edges; i++ ) {
		scanf("%d %d",&u,&v);
		printf (" adding edge %d->%d\n",u,v);
		edge = (Graph*) malloc(sizeof(Graph) * 1);
		edge->node = v;
		edge->adj_list = grph[u];
		grph[u] = edge;
	}

}

void print_graph_adj_list(int num_nodes) {

	int i = 0;
	Graph *u = NULL;
	printf("Graph\n");
	if (grph == NULL) {
		printf("NO entry\n");
		return;
	}

	for (i = 0; i < num_nodes; i++) {

		u = grph[i];
		while(u) {
			printf("Node %d -> ",u->node);
			u = u->adj_list;

		}
		printf(" NULL\n");

	}
}

void clean_up_graph (int num_nodes, int num_edges) {
	int i = 0;
	for (i = 0; i<num_nodes; i++) {

	}
}

