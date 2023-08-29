CXX = g++
CC = $(CXX)

CFLAGS = -Wall -Werror
CFLAGS+= -Wextra
CFLAGS+= -pedantic -g
CFLAGS+= -pthread

CXXFLAGS = $(CFLAGS)
CXXFLAGS += -std=c++17 -I$(INCLUDES_DIR)

LDLIBS += -lpthread

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

AGENT_SENSOR_TARGET = $(SOURCES_DIR)/udp_agent                  
AGENT_SENSOR_OBJECTS = $(SOURCES_DIR)/udp_agent.o $(SOURCES_DIR)/client.o $(SOURCES_DIR)/event.o $(SOURCES_DIR)/protocol.o 

SENSOR_TARGET = $(SOURCES_DIR)/tcp_sensor                    
SENSOR_OBJECTS = $(SOURCES_DIR)/tcp_sensor.o $(SOURCES_DIR)/client.o $(SOURCES_DIR)/protocol.o

$(AGENT_SENSOR_TARGET) : $(AGENT_SENSOR_OBJECTS)

$(SENSOR_TARGET) : $(SENSOR_OBJECTS)

tcp_sensor: $(SENSOR_TARGET)
	@$(SENSOR_TARGET) -v

udp_agent: $(AGENT_SENSOR_TARGET)
	@$(AGENT_SENSOR_TARGET) -v

check : $(TARGET)
	@./$(TARGET) -v

recheck: clean check

clean:
	@$(RM) $(AGENT_SENSOR_TARGET) $(AGENT_SENSOR_OBJECTS)
	@$(RM) $(SENSOR_TARGET) $(SENSOR_OBJECTS)

val: $(AGENT_SENSOR_TARGET) $(SENSOR_TARGET)
	valgrind --leak-check=yes -s -q ./utest

hell: $(AGENT_SENSOR_TARGET) $(SENSOR_TARGET)
	valgrind --tool=helgrind --max-threads=500 -s ./$(TARGET) 2> hell.log

.PHONY: clean all val hell check recheck


# dependencies
$(SOURCES_DIR)/client.o: $(INCLUDES_DIR)/protocol.hpp
$(SOURCES_DIR)/protocol.o: $(INCLUDES_DIR)/protocol.hpp 
$(SOURCES_DIR)/event.o: $(INCLUDES_DIR)/event.hpp
$(SOURCES_DIR)/udp_agent.o: $(INCLUDES_DIR)/client.hpp $(INCLUDES_DIR)/event.hpp