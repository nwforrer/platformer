SOURCE_DIR = source
BUILD_DIR = build

CC := g++
CPP_FILES := $(wildcard $(SOURCE_DIR)/*.cpp)
OBJ_FILES := $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS := `sdl2-config --libs` -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
CC_FLAGS := -std=c++11 -g -Wall -Werror `sdl2-config --cflags` -I./libs/rapidxml-1.13

BINARY := game/platformer

$(BINARY): $(OBJ_FILES)
	$(CC) $(LD_FLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $<

clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/*.d $(BINARY)

CC_FLAGS += -MMD
-include $(OBJ_FILES:.o=.d)
