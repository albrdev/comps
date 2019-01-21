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

BIN			:= test.exe

CMD_CP		:= cp -f
CMD_RM		:= rm -f
CMD_LN		:= ln -sf
CMD_PRINT	:= @printf

SRCS_C		:= $(wildcard $(DIR_SRC)/*.c)
OBJS_C		:= $(patsubst $(DIR_SRC)/%.c,$(DIR_OBJ)/%.o,$(SRCS_C))

SCRS_CPP	:= $(wildcard $(DIR_SRC)/*.cpp)
OBJS_CPP	:= $(patsubst $(DIR_SRC)/%.cpp,$(DIR_OBJ)/%.o,$(SCRS_CPP))

OBJS		:= $(OBJS_C) $(OBJS_CPP)

.PHONY: all
all: debug

.PHONY: release
release: CC_FLAGS += $(FLAGS_RLS)
release: $(DIR_BIN)/$(BIN)

.PHONY: debug
debug: CC_FLAGS += $(FLAGS_DBG)
debug: $(DIR_BIN)/$(BIN)


.PHONY: clean
clean:
	$(CMD_RM) $(OBJS)

.PHONY: distclean
distclean: clean
	$(CMD_RM) $(DIR_BIN)/$(BIN)

.PHONY: run
run: $(DIR_BIN)/$(BIN)
	./$< $(args)

$(DIR_BIN)/$(BIN): $(OBJS)
	$(CC_CPP) $(CC_LIBS) $(OBJS) -o $(DIR_BIN)/$(BIN)

$(DIR_OBJ)/main.o: $(DIR_SRC)/main.cpp
	$(CC_CPP) $(CC_FLAGS) -I$(DIR_INC) -D__USE_MINGW_ANSI_STDIO=1 -c $< -o $@

$(DIR_OBJ)/StandardResistor.o: $(DIR_SRC)/StandardResistor.cpp $(DIR_INC)/StandardResistor.hpp
	$(CC_CPP) $(CC_FLAGS) -I$(DIR_INC) -c $< -o $@

$(DIR_OBJ)/Resistor.o: $(DIR_SRC)/Resistor.cpp $(DIR_INC)/Resistor.hpp
	$(CC_CPP) $(CC_FLAGS) -I$(DIR_INC) -c $< -o $@

$(DIR_OBJ)/ResistorBase.o: $(DIR_SRC)/ResistorBase.cpp $(DIR_INC)/ResistorBase.hpp
	$(CC_CPP) $(CC_FLAGS) -I$(DIR_INC) -c $< -o $@

$(DIR_OBJ)/Component.o: $(DIR_SRC)/Component.cpp $(DIR_INC)/Component.hpp
	$(CC_CPP) $(CC_FLAGS) -I$(DIR_INC) -c $< -o $@

$(DIR_OBJ)/NumberSeries.o: $(DIR_SRC)/NumberSeries.cpp $(DIR_INC)/NumberSeries.hpp
	$(CC_CPP) $(CC_FLAGS) -I$(DIR_INC) -c $< -o $@

$(DIR_OBJ)/Prefix.o: $(DIR_SRC)/Prefix.cpp $(DIR_INC)/Prefix.hpp
	$(CC_CPP) $(CC_FLAGS) -I$(DIR_INC) -c $< -o $@

$(DIR_OBJ)/xmath.o: $(DIR_SRC)/xmath.c $(DIR_INC)/xmath.h
	$(CC_C) $(CC_FLAGS) -I$(DIR_INC) -c $< -o $@
