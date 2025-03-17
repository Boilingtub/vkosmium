CC = g++ -std=c++17
CFLAGS = 
DEBUG_FLAGS = -Wall
RELEASE_FLAGS = -03
LDFLAGS = -lglfw -lvulkan -ldl -lpthread
EXE_OUTPUT = ../output/VulkanTest

VulkanTest: main.cpp
	$(CC) $(DEBUG_FLAGS) -o $(EXE_OUTPUT) main.cpp $(LDFLAGS)

.PHONY: test clean

test: VulkanTest
	./$(EXE_OUTPUT)

clean: 
	rm -rf $(EXE_OUTPUT)
