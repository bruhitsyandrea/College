#include "hashtable.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Create a new (empty) hashtable; return NULL if error. */
hashtable_t *hashtable_new(const int num_slots) {
	hashtable_t *ht = malloc(sizeof(hashtable_t));
	if (ht == NULL) {
		return NULL;
	}
	
	ht->num_slots = num_slots;
	ht->sets = malloc(num_slots * sizeof(set_t *));
	if (ht->sets == NULL) {
		free(ht);
		return NULL;
	}
	
	for (int i = 0; i < num_slots; i++) {
		ht->sets[i] = NULL;
	}
	return ht;
}

/* Insert item, identified by key (string), into the given hashtable.
 * The key string is copied for use by the hashtable.
 * Return false if key exists in ht, any parameter is NULL, or error;
 * return true iff new item was inserted.
 */
bool hashtable_insert(hashtable_t *ht, const char *key, void *item) {
	//if NULL, then return false
	if (ht == NULL || key == NULL || item == NULL) {
		return false;
	}
	
	//check if exist
	for (int i = 0; i < ht->num_slots; i++) {
		set_t *curr = ht->sets[i];
		while (curr != NULL) {
			if (strcmp(curr->key, key) == 0) {
				return false;
			}
			curr = curr->next;
		}
	}
	
	//check to see if insertable
	for (int i = 0; i <ht->num_slots; i++) {
		if (ht->sets[i] == NULL) {
			//new set
			set_t *new_set = malloc(sizeof(set_t));
			if (new_set == NULL) {
				//if NULL , return false
				return false;
			}
			
			//copy
			new_set->key = strdup(key);
			if (new_set->key == NULL) {
				free(new_set);
				return false;
			}
			
			new_set->item = item;
			new_set->next = ht->sets[i];
			ht->sets[i] = new_set;
			
			return true;
		}
	}
	return false;
}

/* Return the item associated with the given key;
 * return NULL if hashtable is NULL, key is NULL, key is not found.
 */
void *hashtable_find(hashtable_t *ht, const char *key) {
	//check NULL parameters
	if (ht == NULL || key == NULL) {
		return NULL;
	}
	
	for (int i = 0; i < ht->num_slots; i++) {
		set_t *curr = ht->sets[i];
		while (curr != NULL) {
			if (strcmp(curr->key,key) == 0) {
				return curr->item;
			}
			curr = curr->next;
		}
	}
	
	
	return NULL;
}

/* Print the whole table; provide the output file and func to print each item.
 * Ignore if NULL fp. Print (null) if NULL ht.
 * Print a table with no items if NULL itemprint.
 */
void hashtable_print(hashtable_t *ht, FILE *fp,
                     void (*itemprint)(FILE *fp, const char *key, void *item)) 
{
	if (fp == NULL) {
		return; //ignore
	}
	
	if (ht == NULL) {
		fprintf(fp, "(null)");
	} else {
		for (int i = 0; i < ht->num_slots; i++) {
			set_t *curr = ht->sets[i];
			
			while (curr != NULL) {
				if (itemprint != NULL) {
					itemprint(fp, curr->key, curr->item);
				} else {
					fprintf(fp, "(null)");
				}
				
				curr = curr->next;
				if (curr != NULL) {
					fprintf(fp, ",");
				}
			}
		}
		
	}
		
}
/* Iterate over all items in the table; in undefined order.
 * Call the given function on each item, with (arg, key, item).
 * If ht==NULL or itemfunc==NULL, do nothing.
 */
void hashtable_iterate(hashtable_t *ht, void *arg,
               void (*itemfunc)(void *arg, const char *key, void *item) ) {
	if (ht == NULL || itemfunc == NULL) {
		return; //do nothing
	}
	
	for (int i = 0; i < ht->num_slots; i++) {
		set_t *curr = ht->sets[i];
		while (curr != NULL) {
			itemfunc(arg, curr->key, curr->item);
			curr = curr->next;
		}
	}
}

/* Delete the whole hashtable; ignore NULL ht.
 * Provide a function that will delete each item (may be NULL).
 */
void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item) ) {
	if (ht == NULL) {
		return; 
	}
	
	for (int i = 0; i < ht->num_slots; i++) {
		set_t *curr = ht->sets[i];
		while (curr != NULL) {
			set_t *next = curr->next;
			
			if (itemdelete != NULL) {
				itemdelete(curr->item);
			}
			
			free(curr->key);
			free(curr);
			
			curr=next;
		}
		
		ht->sets[i] = NULL;
	}
}
