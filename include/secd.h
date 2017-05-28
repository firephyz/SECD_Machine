#ifndef SECD_INCLUDED
	#define SECD_INCLUDED

	#include <stdint.h>

	#define MEMORY_SIZE 4096

	// Cell types
	#define CELL_GENERAL 0
	#define CELL_

	typedef struct cell_t Cell;

	struct cell_t {
		uint8_t meta; // Least sig 4 bits are used for type info
		uint16_t car;
		uint16_t cdr;
	};

	typedef struct {
		Cell * stack;
		Cell * env;
		Cell * code;
		Cell * dump;

		Cell * mem;
		uint16_t free_mem;
	} SECD_Machine;

	SECD_Machine * initMachine();
	void destroyMachine(SECD_Machine * machine);
	void programMachine(SECD_Machine * machine, char * code);
	void executeMachine(SECD_Machine * machine);

	void setCellData(SECD_Machine * machine, uint16_t cell_index, uint8_t type, uint16_t car, uint16_t cdr, int mask);
	void getCellData(SECD_Machine * machine, uint16_t cell_index, uint8_t * type, uint16_t *car, uint16_t * cdr, int mask);

	int indexOf(char target, char * string);
	void getNextToken(char * code, char ** string);

#endif