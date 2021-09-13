ifeq ($(OS), Windows_NT)
	INCLUDES := Includes\\
	BUILD := Build\\
	BIN := Bin\\
	EXECUTABLE := $(BIN)Hierholzers.exe
	SOURCE := Source\\
	DELETE := del
else
	INCLUDES := Includes/
	BUILD := Build/
	BIN := Bin/
	EXECUTABLE := $(BIN)Hierholzers
	SOURCE := Source/
	DELETE := rm
endif

CPP := g++
CPPFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -pedantic-errors -O0 -Werror

all: $(EXECUTABLE)

$(EXECUTABLE): $(BUILD)Main.o
	$(CPP) $(CPPFLAGS) $(BUILD)Main.o -o $(EXECUTABLE)

$(BUILD)Main.o: $(SOURCE)Main.cpp 
	$(CPP) $(CPPFLAGS) -c $(SOURCE)Main.cpp -I$(INCLUDES) -o $(BUILD)Main.o

clean:
	-$(DELETE) $(EXECUTABLE) $(BUILD)Main.o
