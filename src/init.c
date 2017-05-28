#include "init.h"
#include "secd.h"

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <unistd.h>
#include <errno.h>

#include <termios.h>
#include <fcntl.h>


int main(int argc, char ** argv) {

	SECD_Machine * machine = initMachine();

	programMachine(machine, "(test (a b) yep yay)");
	executeMachine(machine);

	destroyMachine(machine);

	//initConsole();
}

int old_flags;
struct termios old_config;
struct termios new_config;

void initConsole() {

	// Get old console config
	old_flags = fcntl(STDIN_FILENO, F_GETFL, 0);
	tcgetattr(STDIN_FILENO, &old_config);
	new_config = old_config;

	// Change to new config
	//fcntl(STDIN_FILENO, F_SETFL, old_flags | O_NONBLOCK);
	new_config.c_lflag &= ~(ICANON | ECHO);
	new_config.c_cc[VMIN] = 0;
	new_config.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_config);

	char buffer[9];
	buffer[8] = '\0';
	int prev = 0;
	while(buffer[0] != 'q') {
		int current = read(STDIN_FILENO, buffer, 8);

		if(prev == 0 && current != 0) {
			printf("%s\n", buffer);
		}

		prev = current;
	}

	// Change console back to old config
	//fcntl(STDIN_FILENO, F_SETFL, old_flags);
	tcsetattr(STDIN_FILENO, TCSANOW, &old_config);
}