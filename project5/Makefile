TARGET   = StarDefender
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -O2

SRCS = main.cpp \
       Entity.cpp \
       Map.cpp \
       LevelScene.cpp \
       MenuScene.cpp \
       Level1.cpp \
       Level2.cpp \
       Level3.cpp \
       WinScene.cpp \
       BossScene.cpp


UNAME := $(shell uname -s 2>/dev/null || echo Windows)

ifeq ($(UNAME), Darwin)
    RAYLIB_INC = /opt/homebrew/include
    RAYLIB_LIB = /opt/homebrew/lib
    LINK_FLAGS = -L$(RAYLIB_LIB) -lraylib \
                 -framework OpenGL -framework Cocoa \
                 -framework IOKit -framework CoreAudio -framework CoreVideo
else ifeq ($(findstring Windows,$(UNAME)), Windows)
    RAYLIB_INC = C:/raylib/include
    RAYLIB_LIB = C:/raylib/lib
    LINK_FLAGS = -L$(RAYLIB_LIB) -lraylib -lopengl32 -lgdi32 -lwinmm
    TARGET     = StarDefender.exe
else
    RAYLIB_INC = /usr/local/include
    RAYLIB_LIB = /usr/local/lib
    LINK_FLAGS = -L$(RAYLIB_LIB) -lraylib \
                 -lGL -lm -lpthread -ldl -lrt -lX11
endif

all:
	$(CXX) $(CXXFLAGS) -I$(RAYLIB_INC) $(SRCS) -o $(TARGET) $(LINK_FLAGS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) StarDefender.exe

.PHONY: all run clean