CXX = g++
CC = $(CXX)

CFLAGS = -Wall -Werror
CFLAGS+= -Wextra
CFLAGS+= -pedantic
CFLAGS+= -g3
CFLAGS+= -pthread

CXXFLAGS = $(CFLAGS)
CXXFLAGS += -std=c++11


INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

TARGET = temp_log_controler

# flags for preprocessor
CPPFLAGS = -I$(INCLUDES_DIR)

LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
LDLIBS += -lpthread

OBJECTS = temp_log_controler.o $(SOURCES_DIR)/plot.o $(SOURCES_DIR)/line.o $(SOURCES_DIR)/grid.o $(SOURCES_DIR)/curve.o\
	 $(SOURCES_DIR)/axis.o $(SOURCES_DIR)/area.o $(SOURCES_DIR)/client.o $(SOURCES_DIR)/protocol.o $(SOURCES_DIR)/event.o

all: $(TARGET)

check : $(TARGET)
	@./$(TARGET) -v

recheck: clean check

$(TARGET) : $(OBJECTS)

valgrind: $(TARGET)
	valgrind --log-file=memleak.log --leak-check=full --track-origins=yes -s ./$<

clean:
	@$(RM) demo $(OBJECTS)

.PHONY: clean all

# dependencies
temp_log_controler.o: temp_log_controler.cpp
$(SOURCES_DIR)/event.o: $(SOURCES_DIR)/event.cpp
$(SOURCES_DIR)/client.o: $(SOURCES_DIR)/client.cpp
$(SOURCES_DIR)/protocol.o: $(SOURCES_DIR)/protocol.cpp
$(SOURCES_DIR)/plot.o: $(SOURCES_DIR)/plot.cpp
$(SOURCES_DIR)/line.o: $(SOURCES_DIR)/line.cpp
$(SOURCES_DIR)/grid.o: $(SOURCES_DIR)/grid.cpp
$(SOURCES_DIR)/curve.o: $(SOURCES_DIR)/curve.cpp
$(SOURCES_DIR)/axis.o: $(SOURCES_DIR)/axis.cpp
$(SOURCES_DIR)/area.o: $(SOURCES_DIR)/area.cpp
