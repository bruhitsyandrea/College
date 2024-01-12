# Assignment 5
Yi-Wen Chen <br>
cruzID: ychen729
## Compilation
to compile the LRU, run the following command <br>
```bash
gcc -Wall -Wextra lru.c test_LRU.c -o test_LRU
./test_LRU
```

## Implementation
### lru_t *lru_new(const int capacity);
I initialized a new lru_t with the size of given capacity.
### bool lru_insert(lru_t *ht, const char *key, void *item);
This function add elememt to LRU and based on the given capacity. If the amount of element trying to add, exceed the capacity of the LRU, then it would removed the least recent used element to make space for new element to be inserted. <br>
I use the following algorithm:
```
if any parameters == NULL
    return false

if LRU is full
    then remove the least recent used element

else (it is not full)
    if the element exit
        then move to the next one
    else
        insert the item
```
### void *lru_find(lru_t *ht, const char *key);
This function use a for loop to fetch the item with the given key
### void lru_print(lru_t *ht, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item));
Printed the LRU from the given file
### void lru_iterate(lru_t *ht, void *arg, void (*itemfunc)(void *arg, const char *key, void *item) );
Iterated through the given file
### void lru_delete(lru_t *ht, void (*itemdelete)(void *item) );
Deleted the entire LRU
