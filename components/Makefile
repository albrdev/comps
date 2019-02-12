VER_MAJOR		:= 0
VER_MINOR		:= 1
VER_MAINTENANCE	:= 0
VER_REVISION	:= a
VER_BUILD		:= 0

APP_TITLE		:= Comp
APP_DESCRIPTION	:= Electrical component/circuit calculator
APP_VERSION		:= $(VER_MAJOR).$(VER_MINOR).$(VER_MAINTENANCE)$(VER_REVISION)
APP_AUTHOR		:= albrdev
APP_WEBSITE		:= https://github.com/albrdev/comp
APP_LICENSE		:= GNU GPLv3
APP_BIN			:= comp

CC_C		:= gcc
CC_CPP		:= g++
CC_FLAGS	:= -pedantic -Wall -Wextra -Wconversion -std=c++14
CC_LIBS		:= 

FLAGS_DBG	:= -g
FLAGS_RLS	:= -DNDEBUG

DIR_INC		:= inc
DIR_SRC		:= src
DIR_OBJ		:= obj
DIR_BIN		:= bin

CMD_CP		:= cp -f
CMD_RM		:= rm -f
CMD_LN		:= ln -sf
CMD_PRINT	:= @printf

SRCS_C		:= $(filter-out $(DIR_SRC)/%_main.c,$(wildcard $(DIR_SRC)/*.c))
OBJS_C		:= $(patsubst $(DIR_SRC)/%.c,$(DIR_OBJ)/%.o,$(SRCS_C))

SRCS_CPP	:= $(filter-out $(DIR_SRC)/%_main.cpp,$(wildcard $(DIR_SRC)/*.cpp))
OBJS_CPP	:= $(patsubst $(DIR_SRC)/%.cpp,$(DIR_OBJ)/%.o,$(SRCS_CPP))

SRCS_MAIN	:= $(wildcard $(DIR_SRC)/*_main.cpp)
OBJS_MAIN	:= $(patsubst $(DIR_SRC)/%.cpp,$(DIR_OBJ)/%.o,$(SRCS_MAIN))

TRG_BINS	:= $(patsubst $(DIR_OBJ)/%_main.o,$(DIR_BIN)/$(APP_BIN)_%,$(OBJS_MAIN))

OBJS		:= $(OBJS_C) $(OBJS_CPP)

BIN_RESISTOR	:= $(APP_BIN)_resistor
BIN_LOGICGATES	:= $(APP_BIN)_logicgates

TRG_BIN		:= $(DIR_BIN)/$(APP_BIN)

.PHONY: all
all: debug

.PHONY: release
release: CC_FLAGS += $(FLAGS_RLS)
release: $(TRG_BINS)

.PHONY: debug
debug: CC_FLAGS += $(FLAGS_DBG)
debug: $(TRG_BINS)

.PHONY: clean
clean:
	$(CMD_RM) $(DIR_OBJ)/*.o

.PHONY: distclean
distclean: clean
	$(CMD_RM) $(TRG_BINS) $(patsubst %,%.exe,$(TRG_BINS))

.PHONY: run
run: $(TRG_BIN)
	./$< $(args)

$(DIR_BIN)/$(BIN_RESISTOR): $(OBJS) $(DIR_OBJ)/resistor_main.o
	$(CC_CPP) $(CC_LIBS) $? -o $@

$(DIR_BIN)/$(BIN_LOGICGATES): $(OBJS) $(DIR_OBJ)/logicgates_main.o
	$(CC_CPP) $(CC_LIBS) $? -o $@

$(DIR_OBJ)/resistor_main.o: $(DIR_SRC)/resistor_main.cpp
	$(CC_CPP) $(CC_FLAGS) -I$(DIR_INC) -D__USE_MINGW_ANSI_STDIO=1 -c $< -o $@

$(DIR_OBJ)/logicgates_main.o: $(DIR_SRC)/logicgates_main.cpp
	$(CC_CPP) $(CC_FLAGS) -I$(DIR_INC) -D__USE_MINGW_ANSI_STDIO=1 -c $< -o $@

$(DIR_OBJ)/LogicGates.o: $(DIR_SRC)/LogicGates.cpp $(DIR_INC)/LogicGates.hpp
	$(CC_CPP) $(CC_FLAGS) -I$(DIR_INC) -c $< -o $@

$(DIR_OBJ)/Resistor.o: $(DIR_SRC)/Resistor.cpp $(DIR_INC)/Resistor.hpp
	$(CC_CPP) $(CC_FLAGS) -I$(DIR_INC) -c $< -o $@

$(DIR_OBJ)/Component.o: $(DIR_SRC)/Component.cpp $(DIR_INC)/Component.hpp
	$(CC_CPP) $(CC_FLAGS) -I$(DIR_INC) -c $< -o $@

$(DIR_OBJ)/ESeries.o: $(DIR_SRC)/ESeries.cpp $(DIR_INC)/ESeries.hpp
	$(CC_CPP) $(CC_FLAGS) -I$(DIR_INC) -c $< -o $@

$(DIR_OBJ)/Prefix.o: $(DIR_SRC)/Prefix.cpp $(DIR_INC)/Prefix.hpp
	$(CC_CPP) $(CC_FLAGS) -I$(DIR_INC) -c $< -o $@

$(DIR_OBJ)/xmath.o: $(DIR_SRC)/xmath.c $(DIR_INC)/xmath.h
	$(CC_C) $(CC_FLAGS) -I$(DIR_INC) -c $< -o $@
