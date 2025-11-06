.PHONY: build include libs obj shaders src

CXX = g++
CXXFLAGS = -std=c++23 \
-Wall \
-Wextra \
-Iinclude \
-O0 \
-g
CXXLIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
CXXFLAGS += -Wno-write-strings -Wno-old-style-cast -Wno-sign-conversion



CXX_WIN = x86_64-w64-mingw32-g++
CXXFLAGS_WIN = -std=c++23 \
-Wall \
-Wextra \
-Iinclude \
-O0 \
-g
CXXLIBS_WIN = -Llibs/glfw -lglfw3 -lopengl32 -lgdi32 -luser32 -lkernel32 -static
CXXFLAGS_WIN += -Wno-write-strings -Wno-old-style-cast -Wno-sign-conversion 







SRC := $(wildcard src/*.cpp) $(wildcard src/*.c)

OBJ_COMP := $(patsubst src/%.cpp,obj/linux/%.o,$(SRC))
OBJ_COMP_WIN := $(patsubst src/%.cpp,obj/windows/%.o,$(SRC))

OBJ = $(wildcard obj/linux/*.o)
OBJ_WIN = $(wildcard obj/windows/*.o)

TARGET = build/main
TARGET_WIN = build/main.exe






linux: $(TARGET) clean_obj

$(TARGET): $(OBJ_COMP) #linking
	$(CXX) $(OBJ) -o $(TARGET) $(CXXLIBS)
	strip $(TARGET)

#compiling
obj/linux/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean_obj:
	rm $(OBJ_COMP)
	




win: $(TARGET_WIN) clean_obj_win

$(TARGET_WIN): $(OBJ_COMP_WIN) #linking
	$(CXX_WIN) $(OBJ_WIN) -o $(TARGET_WIN) $(CXXLIBS_WIN)

#compiling
obj/windows/%.o: src/%.cpp
	$(CXX_WIN) $(CXXFLAGS_WIN) -c $< -o $@

clean_obj_win:
	rm $(OBJ_COMP_WIN)












LIBCXXFLAGS := -std=c++23 \
-Wall \
-Wextra \
-Iinclude \
-O3

GLAD := $(shell find src/glad -type f)
IMGUI := $(shell find src/imgui -type f)
LIB_TARGET := obj/linux
LIB_TARGET_WIN := obj/windows

libs: 
	
$(GLAD_TARGET):
	$(CXX) $(LIBCXXFLAGS) -c $(GLAD) -o $(GLAD_TARGET)
	strip $(GLAD_TARGET)

$(GLAD_TARGET_WIN):
	$(CXX_WIN) $(LIBCXXFLAGS) -c $(GLAD) -o $(GLAD_TARGET_WIN)
	strip $(GLAD_TARGET_WIN)

$(IMGUI_TARGET):
	$(CXX) $(LIBCXXFLAGS) -c $(IMGUI) -o $(IMGUI_TARGET)
	strip $(IMGUI_TARGET)

$(IMGUI_TARGET_WIN):
	$(CXX_WIN) $(LIBCXXFLAGS) -c $(IMGUI) -o $(IMGUI_TARGET_WIN)
	strip $(IMGUI_TARGET_WIN)





test: linux run

test_win: win run_win

run:
	build/main

run_win:
	wine build/main.exe

clean:
	rm -rf build/*

