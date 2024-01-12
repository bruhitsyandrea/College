#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Create a new (empty) set; return NULL if error. */
set_t* set_new(void) {
	set_t *set = malloc(sizeof(set_t));
	
	if (set == NULL) {
		return NULL;
	}
	set->key = NULL;
	set->item = NULL;
	set->next = NULL;
	return set;
}

/* Insert item, identified by a key (string), into the given set.
 * The key string is copied for use by the set.
 * Return false if key exists, any parameter is NULL, or error;
 * return true iff new item was inserted.
 */
bool set_insert(set_t *set, const char *key, void *item) {
	//if NULL, then return false
	if (set == NULL || key == NULL || item == NULL) {
		return false;
	}
	
	//if key exists, then return false
	set_t *curr_set = set->next;
	while (curr_set != NULL) {
		if (strcmp(curr_set->key, key) == 0) {
			return false;
		}
		curr_set = curr_set->next;
	}
	
	//create a new set and check error
	set_t *new_set = malloc(sizeof(set_t));
	if (new_set == NULL) {
		return false;
	}
	
	//copy the key
	new_set->key = strdup(key);
	if (new_set->key == NULL) {
		free(new_set);
		return false;
	}
	
	new_set->item = item;
	new_set->next = set->next;
	set->next = new_set;
	
	return true;
}

/* Return the item associated with the given key;
 * return NULL if set is NULL, key is NULL, or key is not found.
 */
void *set_find(set_t *set, const char *key) {
	if (set == NULL || key == NULL) {
		return NULL;
	}
	set_t *curr = set->next;
	while (curr != NULL) {
		if (strcmp(curr->key,key) == 0) {
			return curr->item;
		}
		curr = curr->next;
	}
	return NULL;
}

/* Print the whole set; provide the output file and func to print each item.
 * Ignore if NULL fp. Print (null) if NULL set.
 * Print a set with no items if NULL itemprint.
*/
void set_print(set_t *set, FILE *fp,
               void (*itemprint)(FILE *fp, const char *key, void *item) ) {
 	if (fp == NULL) {
 		//ignore if NULL
 		return;
 	} 
 	
 	
 	
 	if (set == NULL) {
 		fprintf(fp, "(null)");
 	} else {
 		set_t *curr = set->next;
 		
 		while (curr != NULL) {
 			if (itemprint != NULL) {
 				itemprint(fp, curr->key, curr->item);
 			} else {
 				fprintf(fp, "(null)");
 			}
 			
 			curr = curr->next;
 			if (curr != NULL) {
 				fprintf(fp, ", ");
 			}
 		}
 	}
 	
 }

/* Iterate over all items in the set, in undefined order.
 * Call the given function on each item, with (arg, key, item).
 * If set==NULL or itemfunc==NULL, do nothing.
 */
void set_iterate(set_t *set, void *arg,
                 void (*itemfunc)(void *arg, const char *key, void *item) ) {
	if (set == NULL || itemfunc == NULL) {
		return; //do nothing
	}
	
	set_t *curr = set->next;
	while (curr != NULL) {
		itemfunc(arg, curr->key, curr->item);
		curr = curr->next;
	}                 
}

/* Delete the whole set; ignore NULL set.
 * Provide a function that will delete each item (may be NULL).
 */
void set_delete(set_t *set, void (*itemdelete)(void *item) ) {
	if (set == NULL) {
		return;
	}
	set_t *curr = set->next;
	while (curr != NULL) {
		set_t *next = curr->next;
		
		if (itemdelete != NULL) {
			itemdelete(curr->item);
		}
		
		free(curr->key);
		free(curr);
		
		curr=next;
	}
	
	set->next = NULL;


}
