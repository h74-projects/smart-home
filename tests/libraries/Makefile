CXX = g++
CC = $(CXX)

CFLAGS = -Wall -Werror
CFLAGS+= -Wextra
CFLAGS+= -pedantic -g
CFLAGS+= -fPIC

CXXFLAGS = $(CFLAGS)
CXXFLAGS += -std=c++17 -I$(INCLUDES_DIR)

TARGET = agent_tempature.so
OBJS = $(SOURCES_DIR)/agent_tempature.o

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src


temp_agent: $(TARGET)

$(TARGET): $(OBJS) 
	$(CC) $(CXXFLAGS) -shared -o $(TARGET) $(OBJS) 

recheck: clean check

.c.o:
	$(CC) $(CXXFLAGS) -cpp $<  -o $@

clean:
	$(RM) $(OBJS) $(TARGET)

.PHONY: clean

$(SOURCES_DIR)/agent_tempature.o: $(INCLUDES_DIR)/agent_tempature.hpp $(INCLUDES_DIR)/agent.hpp $(INCLUDES_DIR)/agent_sensor.hpp
