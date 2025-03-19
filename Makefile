CC = g++ -std=c++17
CFLAGS = 
DEBUG_FLAGS = -Wall -Wextra -Wshadow -g -static-libasan -fanalyzer -fsanitize=address
RELEASE_FLAGS = -O3
LDFLAGS = -lglfw -lvulkan -ldl -lpthread
EXE_OUTPUT = ./output/VulkanTest
src = ./src/


VulkanTest: $(src)main.cpp
	$(CC) $(DEBUG_FLAGS) -o $(EXE_OUTPUT) $(src)*.cpp $(LDFLAGS)

test: VulkanTest
	./$(EXE_OUTPUT)

VulkanRun: $(src)main.cpp
	$(CC) $(RELEASE_FLAGS) -o $(EXE_OUTPUT) $(src)*.cpp $(LDFLAGS)

run: VulkanRun
		./$(EXE_OUTPUT)

run: VulkanRun
clean: 
	rm -rf $(EXE_OUTPUT)
