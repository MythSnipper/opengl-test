
CXX = g++
CXXFLAGS = -std=c++23 \
-Wall \
-Wextra \
-Wno-write-strings \
-Wno-old-style-cast \
-Wno-sign-conversion \
-Iinclude \
-O0 \
-g
CXXFLAGS_LIB := -std=c++23 \
-Wall \
-Wextra \
-Wno-write-strings \
-Wno-old-style-cast \
-Wno-sign-conversion \
-Iinclude \
-O3
CXXLIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

CXX_WIN = x86_64-w64-mingw32-g++
CXXFLAGS_WIN = -std=c++23 \
-Wall \
-Wextra \
-Wno-write-strings \
-Wno-old-style-cast \
-Wno-sign-conversion \
-Iinclude \
-O0 \
-g
CXXFLAGS_LIB_WIN := -std=c++23 \
-Wall \
-Wextra \
-Wno-write-strings \
-Wno-old-style-cast \
-Wno-sign-conversion \
-Iinclude \
-Iinclude/imgui \
-Iinclude/imgui/backends \
-O3
CXXLIBS_WIN = -Llibs/glfw -lglfw3 -lopengl32 -lgdi32 -luser32 -lkernel32 -static


#source files
SRC := $(shell find src -maxdepth 1 -type f \( -name '*.c' -o -name '*.cpp' \))
#source files of library
SRC_LIB := $(shell find src -maxdepth 20 -mindepth 2 -type f \( -name '*.c' -o -name '*.cpp' \))

#objects to compile for program
OBJ_COMP := $(patsubst src/%.cpp,obj/linux/%.o,$(filter %.cpp,$(SRC))) $(patsubst src/%.c,obj/linux/%.o,$(filter %.c,$(SRC)))
OBJ_COMP_WIN := $(patsubst src/%.cpp,obj/windows/%.o,$(filter %.cpp,$(SRC))) $(patsubst src/%.c,obj/windows/%.o,$(filter %.c,$(SRC)))

#objects to compile for library
OBJ_LIB := $(patsubst src/%.cpp,obj/linux/%.o,$(filter %.cpp,$(SRC_LIB))) $(patsubst src/%.c,obj/linux/%.o,$(filter %.c,$(SRC_LIB)))
OBJ_LIB_WIN := $(patsubst src/%.cpp,obj/windows/%.o,$(filter %.cpp,$(SRC_LIB))) $(patsubst src/%.c,obj/windows/%.o,$(filter %.c,$(SRC_LIB)))

#all objects that needs to be linked together to make final executable
OBJ = $(shell find obj/linux -type f)
OBJ_WIN = $(shell find obj/windows -type f)

#final executable targets
TARGET := build/main
TARGET_WIN := build/main.exe

#debug or no
DEBUG ?= 0


$(info SRC: $(SRC))
$(info SRC_LIB: $(SRC_LIB))
$(info OBJ_COMP: $(OBJ_COMP))
$(info OBJ_COMP_WIN: $(OBJ_COMP_WIN))
$(info OBJ_LIB: $(OBJ_LIB))
$(info OBJ_LIB_WIN: $(OBJ_LIB_WIN));
$(info )

.PHONY: build include libs obj shaders src $(TARGET) $(OBJ_COMP) $(TARGET_WIN) $(OBJ_COMP_WIN)

linux: $(OBJ_LIB) $(TARGET)
linux_refresh: $(OBJ_LIB) linux_fast

linux_fast: $(OBJ_LIB)
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o obj/linux/main.o
	$(CXX) $(OBJ) -o $(TARGET) $(CXXLIBS)

$(TARGET): $(OBJ_COMP) #linking
	$(info Linking program for linux)
	$(CXX) $(OBJ) -o $(TARGET) $(CXXLIBS)
ifeq ($(DEBUG),0)
	strip $(TARGET)
endif

#compiling
$(OBJ_COMP):
	$(info Compiling program for linux)
	for obj in $(OBJ_COMP); do \
		src=$$(echo $$obj | sed 's|obj/linux/|src/|' | sed 's|\.o$$||'); \
		if [ -f "$${src}.cpp" ]; then \
			src="$${src}.cpp"; \
		elif [ -f "$${src}.c" ]; then \
			src="$${src}.c"; \
		else \
			echo "Error: No matching source for $$obj"; \
			exit 1; \
		fi; \
		echo "Compiling $$src -> $$obj"; \
		mkdir -p $$(dirname $$obj); \
		$(CXX) $(CXXFLAGS) -c $$src -o $$obj; \
	done

#compiling libs
$(OBJ_LIB):
	$(info Compiling libs for linux)
	for obj in $(OBJ_LIB); do \
		src=$$(echo $$obj | sed 's|obj/linux/|src/|' | sed 's|\.o$$||'); \
		if [ -f "$${src}.cpp" ]; then \
			src="$${src}.cpp"; \
		elif [ -f "$${src}.c" ]; then \
			src="$${src}.c"; \
		else \
			echo "Error: No matching source for $$obj"; \
			exit 1; \
		fi; \
		echo "Compiling $$src -> $$obj"; \
		mkdir -p $$(dirname $$obj); \
		$(CXX) $(CXXFLAGS_LIB) -c $$src -o $$obj; \
	done







win: $(OBJ_LIB_WIN) $(TARGET_WIN)
win_refresh: $(OBJ_LIB_WIN) win_fast

win_fast: $(OBJ_LIB_WIN)
	$(CXX_WIN) $(CXXFLAGS_WIN) -c src/main.cpp -o obj/windows/main.o
	$(CXX_WIN) $(OBJ_WIN) -o $(TARGET_WIN) $(CXXLIBS_WIN)

$(TARGET_WIN): $(OBJ_COMP_WIN) #linking
	$(info Linking program for windows)
	$(CXX_WIN) $(OBJ_WIN) -o $(TARGET_WIN) $(CXXLIBS_WIN)
ifeq ($(DEBUG),0)
	strip $(TARGET_WIN)
endif

#compiling
$(OBJ_COMP_WIN):
	$(info Compiling program for windows)
	for obj in $(OBJ_COMP_WIN); do \
		src=$$(echo $$obj | sed 's|obj/windows/|src/|' | sed 's|\.o$$||'); \
		if [ -f "$${src}.cpp" ]; then \
			src="$${src}.cpp"; \
		elif [ -f "$${src}.c" ]; then \
			src="$${src}.c"; \
		else \
			echo "Error: No matching source for $$obj"; \
			exit 1; \
		fi; \
		echo "Compiling $$src -> $$obj"; \
		mkdir -p $$(dirname $$obj); \
		$(CXX_WIN) $(CXXFLAGS_WIN) -c $$src -o $$obj; \
	done

#compiling libs
$(OBJ_LIB_WIN):
	$(info Compiling libs for windows)
	for obj in $(OBJ_LIB_WIN); do \
		src=$$(echo $$obj | sed 's|obj/windows/|src/|' | sed 's|\.o$$||'); \
		if [ -f "$${src}.cpp" ]; then \
			src="$${src}.cpp"; \
		elif [ -f "$${src}.c" ]; then \
			src="$${src}.c"; \
		else \
			echo "Error: No matching source for $$obj"; \
			exit 1; \
		fi; \
		echo "Compiling $$src -> $$obj"; \
		mkdir -p $$(dirname $$obj); \
		$(CXX_WIN) $(CXXFLAGS_LIB_WIN) -c $$src -o $$obj; \
	done


clean:
	rm -f $(OBJ_COMP)
	rm -f $(OBJ_COMP_WIN)

nuke:
	rm -rf obj/linux/*
	rm -rf obj/windows/*


test: linux run
fast: linux_refresh run

test_win: win run_win
fast_win: win_fast run_win

run:
	build/main
run_win:
	wine build/main.exe





