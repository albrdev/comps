VER_MAJOR		:= 0
VER_MINOR		:= 1
VER_MAINTENANCE	:= 0
VER_REVISION	:= a
VER_BUILD		:= 0

APP_TITLE		:= Components
APP_DESCRIPTION	:= Electrical component/circuit calculator
APP_VERSION		:= $(VER_MAJOR).$(VER_MINOR).$(VER_MAINTENANCE)$(VER_REVISION)
APP_AUTHOR		:= albrdev
APP_WEBSITE		:= https://gitlab.com/albrdev/components
APP_LICENSE		:= GNU GPLv3
APP_BIN			:= components

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

SRCS_C		:= $(wildcard $(DIR_SRC)/*.c)
OBJS_C		:= $(patsubst $(DIR_SRC)/%.c,$(DIR_OBJ)/%.o,$(SRCS_C))
SCRS_CPP	:= $(wildcard $(DIR_SRC)/*.cpp)
OBJS_CPP	:= $(patsubst $(DIR_SRC)/%.cpp,$(DIR_OBJ)/%.o,$(SCRS_CPP))
OBJS		:= $(OBJS_C) $(OBJS_CPP)

TRG_BIN		:= $(DIR_BIN)/$(APP_BIN)

.PHONY: all
all: debug

.PHONY: release
release: CC_FLAGS += $(FLAGS_RLS)
release: $(TRG_BIN)

.PHONY: debug
debug: CC_FLAGS += $(FLAGS_DBG)
debug: $(TRG_BIN)

.PHONY: clean
clean:
	$(CMD_RM) $(DIR_OBJ)/*.o

.PHONY: distclean
distclean: clean
	$(CMD_RM) $(TRG_BIN) $(patsubst %,%.exe,$(TRG_BIN))

.PHONY: run
run: $(TRG_BIN)
	./$< $(args)

$(TRG_BIN): $(OBJS)
	$(CC_CPP) $(CC_LIBS) $? -o $@

$(DIR_OBJ)/main.o: $(DIR_SRC)/main.cpp
	$(CC_CPP) $(CC_FLAGS) -I$(DIR_INC) -D__USE_MINGW_ANSI_STDIO=1 -c $< -o $@

$(DIR_OBJ)/LogicGate1x.o: $(DIR_SRC)/LogicGate1x.cpp $(DIR_INC)/LogicGate1x.hpp
	$(CC_CPP) $(CC_FLAGS) -I$(DIR_INC) -c $< -o $@

$(DIR_OBJ)/LogicGate2x.o: $(DIR_SRC)/LogicGate2x.cpp $(DIR_INC)/LogicGate2x.hpp
	$(CC_CPP) $(CC_FLAGS) -I$(DIR_INC) -c $< -o $@

$(DIR_OBJ)/NOT.o: $(DIR_SRC)/NOT.cpp $(DIR_INC)/NOT.hpp
	$(CC_CPP) $(CC_FLAGS) -I$(DIR_INC) -c $< -o $@

$(DIR_OBJ)/OR.o: $(DIR_SRC)/OR.cpp $(DIR_INC)/OR.hpp
	$(CC_CPP) $(CC_FLAGS) -I$(DIR_INC) -c $< -o $@

$(DIR_OBJ)/NOR.o: $(DIR_SRC)/NOR.cpp $(DIR_INC)/NOR.hpp
	$(CC_CPP) $(CC_FLAGS) -I$(DIR_INC) -c $< -o $@

$(DIR_OBJ)/AND.o: $(DIR_SRC)/AND.cpp $(DIR_INC)/AND.hpp
	$(CC_CPP) $(CC_FLAGS) -I$(DIR_INC) -c $< -o $@

$(DIR_OBJ)/NAND.o: $(DIR_SRC)/NAND.cpp $(DIR_INC)/NAND.hpp
	$(CC_CPP) $(CC_FLAGS) -I$(DIR_INC) -c $< -o $@

$(DIR_OBJ)/XOR.o: $(DIR_SRC)/XOR.cpp $(DIR_INC)/XOR.hpp
	$(CC_CPP) $(CC_FLAGS) -I$(DIR_INC) -c $< -o $@

$(DIR_OBJ)/XNOR.o: $(DIR_SRC)/XNOR.cpp $(DIR_INC)/XNOR.hpp
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
