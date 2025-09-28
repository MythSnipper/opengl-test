

CXX = g++
CXXFLAGS = -std=c++23 \
-Wall \
-Wextra \
-Iinclude \
-O0 \
-g
CXXLIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

CXX_WIN = x86_64-w64-mingw32-g++
CXXFLAGS_WIN = -std=c++23 \
-Wall \
-Wextra \
-Iinclude \
-O0 \
-g
CXXLIBS_WIN = -Llibs/glfw -lglfw3 -lopengl32 -lgdi32 -luser32 -lkernel32 -static


OBJ = obj/main.o \
obj/glad_linux.o

OBJ_WIN = obj/main.o \
obj/glad_windows.o

TARGET = build/main
TARGET_WIN = build/main.exe



linux: $(TARGET) clean_objs

$(TARGET): objs #linking
	$(CXX) $(OBJ) -o $(TARGET) $(CXXLIBS)

#compiling
objs: #paths are hard coded because I crash out
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o obj/main.o 

windows: $(TARGET_WIN) clean_objs

$(TARGET_WIN): windows_objs #linking
	$(CXX_WIN) $(OBJ_WIN) -o $(TARGET_WIN) $(CXXLIBS_WIN)

#compiling
windows_objs: #paths are hard coded because I crash out
	$(CXX_WIN) $(CXXFLAGS_WIN) -c src/main.cpp -o obj/main.o

#clean up
clean_objs:
	rm obj/main.o



test: clean linux run

test_win: clean windows run_windows

run:
	build/main

run_windows:
	wine build/main.exe



clean:
	rm -rf build/*

