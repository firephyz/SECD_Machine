############################################
# Program building and installing makefile #
#                                          #
# Requires a directory structure as:       #
# $(TOP_DIR)                               #
#     - Makefile                           # 
#     - $(SRC_DIR)                         # 
#     - $(INCLUDE_DIR)                     #
#     - $(OTHER_REQUIRED_STUFF)            #
#                                          #
# Required libraries are listed like so:   #
#     :lib1 :lib2 :lib3...etc.             #
#                                          #
############################################

#################### Basic Info###################
NAME =secd
DIR =$(shell pwd)
CC =gcc

################# Directories ################
SRC_DIR =$(DIR)/src/
INCLUDE_DIR =$(DIR)/include/
BUILD_DIR =$(DIR)/build/
BIN_DIR =$(DIR)/bin/

################# Flags #######################
CCFLAGS = -g -Wall -std=c99
INCLUDE_FLAGS = 
LIB_FLAGS = 
ALL_FLAGS = $(CCFLAGS)$(LIB_FLAGS)$(INCLUDE_FLAGS)

################ Program files ####################
SRC_FILES :=$(wildcard $(SRC_DIR)*.c)
BUILD_FILES :=$(subst .c,.o,$(subst src,build,$(SRC_FILES)))

################## Targets #######################
all: | clean init $(BUILD_FILES)
	$(CC) $(ALL_FLAGS) $(BUILD_FILES) -o $(BIN_DIR)$(NAME)

%.o:
	$(CC) -c $(CCFLAGS) $(subst build,src,$*.c) -o $*.o -I$(INCLUDE_DIR)

clean:
	rm -r -f $(BUILD_DIR)
	rm -r -f $(BIN_DIR)

############# Utilies ###################

init:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BIN_DIR)
