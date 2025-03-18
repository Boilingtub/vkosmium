CC = g++ -std=c++17
CFLAGS = 
DEBUG_FLAGS = -Wall -Wextra -Wshadow -g -static-libasan -fanalyzer -fsanitize=address
RELEASE_FLAGS = -03
LDFLAGS = -lglfw -lvulkan -ldl -lpthread
EXE_OUTPUT = ./output/VulkanTest
src = ./src/


VulkanTest: $(src)main.cpp
	$(CC) $(DEBUG_FLAGS) -o $(EXE_OUTPUT) $(src)*.cpp $(LDFLAGS)

test: VulkanTest
	./$(EXE_OUTPUT)

clean: 
	rm -rf $(EXE_OUTPUT)
