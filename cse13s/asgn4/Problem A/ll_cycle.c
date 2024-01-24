#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    /* TODO: Implement ll_has_cycle */
    // two-pointers at the head of the list
    node *fast_ptr = head;
    node *slow_ptr = head;
    
    while (fast_ptr != NULL && fast_ptr->next != NULL) {
    	// advance by two nodes
    	fast_ptr = fast_ptr->next->next;
    	// advance by one nodes
    	slow_ptr = slow_ptr->next;
    	//check if list is cyclic
    	if (fast_ptr == slow_ptr) {
    		return 1;
    	}
    }
    
    return 0;
}
