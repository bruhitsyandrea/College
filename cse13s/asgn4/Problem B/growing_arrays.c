#include "growing_arrays.h"

// returns the index of the item added  
int add_record(Record record) {
    // Your code here
    if (table.nval == table.max) {
    	int new_max = table.max * GROW_SIZE;

	Record *new_records = realloc(table.record, new_max * sizeof(Record));

	if (new_records == NULL) {
		return -1;
	}
	table.record = new_records;
	table.max = new_max;
    }
    table.record[table.nval] = record;
    int index = table.nval++;
    return index;
}

// return 0 if there is no matching record
// return 1 if there is a matching record and deletes it and 
// moves records
int del_record(const char *name) {
    // Your code here
    for (int i = 0; i < table.nval; i++) {
    	if (strcmp(table.record[i].name, name) == 0) {
    		for (int j = i; j < table.nval -1; j++) {
    			table.record[j] = table.record[j+1];
    		}
    		table.nval--;
    		return 1;
    		
    	}
    	
    }
    return 0;
}

// returns id of student record of the first matching record
int get_id(const char *name) {
    // Your code here
    for (int i = 0; i < table.nval; i++) {
    	if (strcmp(table.record[i].name, name) == 0) {
    		return table.record[i].id;
    	}
    }
    return 0;
}

// returns record with a valid index, 0 to max-1 
Record get_record(int index) {
    // Your code here
    if (index >= 0 && index <= table.max-1) {
    	return table.record[index];
    }
    Record defaultRecord = {"", 0};
    return defaultRecord;
}

// Testing code. You can modify this and check your own test cases.
//struct Table table; // If you are using another .c file to test your program comment this line as well.
/*
int main() {
    table.nval = 0;
    table.max = INIT_SIZE;
    table.record = malloc(sizeof(Record) * table.max);

    // test add_record
    Record r1 = {"Alice", 1};
    Record r2 = {"Bob", 2};
    Record r3 = {"Charlie", 3};
    int i1 = add_record(r1);
    int i2 = add_record(r2);
    int i3 = add_record(r3);
    printf("added records at indices %d, %d, %d\n", i1, i2, i3);

    // test get_id and get_record
    int id = get_id("Bob");
    Record r = get_record(i1);
    printf("record at index %d: name=%s, id=%d\n", i1, r.name, r.id);
    printf("record with name 'Bob': id=%d\n", id);

    // test del_record
    int success = del_record("Bob");
    printf("deleted record with name 'Bob': %d\n", success);
    id = get_id("Bob");
    printf("record with name 'Bob': id=%d\n", id);

    free(table.record);
    return 0;
}
*/
/*
Output for the above testing code:

added records at indices 0, 1, 2
record at index 0: name=Alice, id=1
record with name 'Bob': id=2
deleted record with name 'Bob': 1
record with name 'Bob': id=0


*/
