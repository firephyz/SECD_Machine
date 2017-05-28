#include "secd.h"

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <limits.h>

SECD_Machine * initMachine() {

	SECD_Machine * machine = malloc(sizeof(SECD_Machine));
	machine->stack = 0;
	machine->env = 0;
	machine->code = 0;
	machine->dump = 0;
	machine->mem = malloc(sizeof(Cell) * MEMORY_SIZE);
	machine->free_mem = &machine->mem[1];

	// Link the memory together
	for(int i = 1; i < MEMORY_SIZE - 1; ++i) {
		machine->mem[i].car = 0;
		machine->mem[i].cdr += 1;
		machine->mem[i].meta = CELL_GENERAL;
	}
	machine->mem[0] = (Cell){CELL_GENERAL, 0, 0};
	machine->mem[MEMORY_SIZE - 1] = (Cell){CELL_GENERAL, 0, 0};

	return machine;
}

void destroyMachine(SECD_Machine * machine) {
	free(machine->mem);
	free(machine);
}

void programMachine(SECD_Machine * machine, char * code) {

	char * string = NULL;

	while(string != (char *)1) {
		getNextToken(code, &string);
		if(string != (char *)1 && string != NULL) printf("%s\n", string);
	}
}

void executeMachine(SECD_Machine * machine) {

}

Cell * getFreeCell(SECD_Machine * machine) {
	
	Cell * result = machine->free_mem;
	machine->free_mem += 1;
	return result;
}

void getNextToken(char * code, char ** string) {

	static int index = 0;
	static int hasComputedLength = 0;
	static int length = -1;

	if(!hasComputedLength) {
		length = strlen(code);
		hasComputedLength = 1;
	}

	if(index >= length) {
		*string = (char *)1;
		return;
	}

	if(*string != NULL) {
		free(*string);
	}

	if(code[index] == '(') {
		*string = malloc(sizeof(char) + 1);
		memcpy(*string, "(", 2);
		index++;
	}
	else if (code[index] == ')') {
		*string = malloc(sizeof(char) + 1);
		memcpy(*string, ")", 2);
		index++;
	}
	else if (code[index] == ' ') {
		*string = NULL;
		index++;
	}
	else {
		int length = indexOf(' ', code + index);
		int length1 = indexOf(')', code + index);
		if (length1 < length) {
			length = length1;
		}

		*string = malloc(sizeof(char) * length + 1);
		memcpy(*string, code + index, length);
		(*string)[index + length] = '\0';

		index += length;
	}
}

int indexOf(char target, char * string) {

	int length = strlen(string);
	for(int i = 0; i < length; ++i) {
		if(string[i] == target) {
			return i;
		}
	}

	return INT_MAX;
}