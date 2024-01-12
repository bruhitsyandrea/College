#include "lru.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Create a new (empty) lru; return NULL if error. */
lru_t *lru_new(const int capacity) {
	lru_t *ht = malloc(sizeof(lru_t));
	if(ht == NULL) {
		return NULL;
	}
	
	ht->capacity = capacity;
	ht->sets = malloc(capacity * sizeof(set_t *));
	if (ht->sets == NULL) {
		free(ht);
		return NULL;
	}

	for (int i = 0; i < capacity; i++) {
		ht->sets[i] = NULL;
	}
	return ht;
}

/* Insert item, identified by key (string), into the given lru.
 * The key string is copied for use by the lru.
 * Return false if key exists in ht, any parameter is NULL, or error;
 * return true iff new item was inserted.
 */
bool lru_insert(lru_t *ht, const char *key, void *item) {
	//if NULL, then return false
    if (ht == NULL || key == NULL || item == NULL) {
        return false;
    }
    
    //check if LRU is full
    if (ht->sets[ht->capacity - 1] != NULL) {
    	//remove the lru item
    	set_t *temp = ht->sets[ht->capacity - 1];
    	ht->sets[ht->capacity -1] = temp->next;
    	free(temp->key);
    	free(temp);
    }
    //check if exist
    for (int i = 0; i < ht->capacity; i++) {
        set_t *curr = ht->sets[i];
        while (curr != NULL) {
            if (strcmp(curr->key, key) == 0) {
                return false;
            }
            curr = curr->next;
        }
    }
    
    //insert the new item
    for (int i = ht->capacity -1; i > 0; i--) {
    	ht->sets[i] = ht->sets[i -1];
    }
    
    
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
    new_set->next = NULL;
    
    ht->sets[0] = new_set;
    
    return true;
    
}

/* Return the item associated with the given key;
 * return NULL if lru is NULL, key is NULL, key is not found.
 */
void *lru_find(lru_t *ht, const char *key) {
	//check NULL parameters
	if (ht == NULL || key == NULL) {
		return NULL;
	}
	
	for (int i = 0; i < ht->capacity; i++) {
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
void lru_print(lru_t *ht, FILE *fp,
                     void (*itemprint)(FILE *fp, const char *key, void *item)) 
{
	if (fp == NULL) {
		return; //ignore
	}
	
	if (ht == NULL) {
		fprintf(fp, "(null)");
	} else {
		for (int i = 0; i < ht->capacity; i++) {
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
void lru_iterate(lru_t *ht, void *arg,
               void (*itemfunc)(void *arg, const char *key, void *item) )
{
	if (ht == NULL || itemfunc == NULL) {
		return; //do nothing
	}
	
	for (int i = 0; i < ht->capacity; i++) {
		set_t *curr = ht->sets[i];
		while (curr != NULL) {
			itemfunc(arg, curr->key, curr->item);
			curr = curr->next;
		}
	}
}

/* Delete the whole lru; ignore NULL ht.
 * Provide a function that will delete each item (may be NULL).
 */
void lru_delete(lru_t *ht, void (*itemdelete)(void *item) ) {
	if (ht == NULL) {
		return; 
	}
	
	for (int i = 0; i < ht->capacity; i++) {
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


