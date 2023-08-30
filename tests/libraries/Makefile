CXX = g++ -c
CC = $(CXX)

CFLAGS = -Wall -Werror
CFLAGS+= -Wextra
CFLAGS+= -pedantic -g
CFLAGS+= -fPIC

CXXFLAGS = $(CFLAGS)
CXXFLAGS += -std=c++17 -I$(INCLUDES_DIR)

LDLIBS += -lpthread

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

TARGET = agent_tempature.so
OBJECTS =  $(INCLUDES_DIR)/agent_sensor.o $(INCLUDES_DIR)/agent_tempature.o $(INCLUDES_DIR)/agent.o

temp_agent: $(SOURCES_DIR)/agent_tempature
			$(CC) -shared -o $(TARGET) $(OBJECTS)

recheck: clean check

clean:


val: $(TCP_CONTROLER_TARGET) $(TCP_SENSOR_TARGET) $(UDP_SENSOR_TARGET)
	valgrind --leak-check=yes -s -q ./utest

hell: $(TCP_CONTROLER_TARGET) $(TCP_SENSOR_TARGET) $(UDP_SENSOR_TARGET)
	valgrind --tool=helgrind --max-threads=500 -s ./$(TARGET) 2> hell.log

.PHONY: clean all val hell check recheck


# dependencies
$(SOURCES_DIR)/agent_sensor.o: $(INCLUDES_DIR)/agent_sensor.hpp
$(SOURCES_DIR)/agent_tempature.o: $(INCLUDES_DIR)/agent_tempature.hpp
$(SOURCES_DIR)/agent.o: $(INCLUDES_DIR)/agent.hpp 
