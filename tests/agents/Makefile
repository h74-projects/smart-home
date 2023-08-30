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

TCP_CONTROLER_TARGET = $(SOURCES_DIR)/tcp_controler                     
TCP_CONTROLER_OBJECTS = $(SOURCES_DIR)/tcp_controler.o $(SOURCES_DIR)/client.o $(SOURCES_DIR)/event.o\
							 $(SOURCES_DIR)/protocol.o 

TCP_SENSOR_TARGET = $(SOURCES_DIR)/tcp_sensor                    
TCP_SENSOR_OBJECTS = $(SOURCES_DIR)/tcp_sensor.o $(SOURCES_DIR)/client.o $(SOURCES_DIR)/protocol.o

UDP_SENSOR_TARGET = $(SOURCES_DIR)/udp_sensor                    
UDP_SENSOR_OBJECTS = $(SOURCES_DIR)/udp_sensor.o $(SOURCES_DIR)/udp.o $(SOURCES_DIR)/protocol.o

$(TCP_CONTROLER_TARGET) : $(TCP_CONTROLER_OBJECTS)

$(TCP_SENSOR_TARGET) : $(TCP_SENSOR_OBJECTS)

$(UDP_SENSOR_TARGET) : $(UDP_SENSOR_OBJECTS)

tcp_sensor: $(TCP_SENSOR_TARGET)
	@$(TCP_SENSOR_TARGET) -v

udp_sensor: $(UDP_SENSOR_TARGET)
	@$(UDP_SENSOR_TARGET) -v

tcp_controler: $(TCP_CONTROLER_TARGET)
	@./$(TCP_CONTROLER_TARGET) -v 

recheck: clean check

clean:
	@$(RM) $(TCP_CONTROLER_TARGET) $(TCP_CONTROLER_OBJECTS)
	@$(RM) $(TCP_SENSOR_TARGET) $(TCP_SENSOR_OBJECTS)
	@$(RM) $(UDP_SENSOR_TARGET) $(UDP_SENSOR_OBJECTS)

val: $(TCP_CONTROLER_TARGET) $(TCP_SENSOR_TARGET) $(UDP_SENSOR_TARGET)
	valgrind --leak-check=yes -s -q ./utest

hell: $(TCP_CONTROLER_TARGET) $(TCP_SENSOR_TARGET) $(UDP_SENSOR_TARGET)
	valgrind --tool=helgrind --max-threads=500 -s ./$(TARGET) 2> hell.log

.PHONY: clean all val hell check recheck


# dependencies
$(SOURCES_DIR)/client.o: $(INCLUDES_DIR)/protocol.hpp
$(SOURCES_DIR)/udp.o: $(INCLUDES_DIR)/protocol.hpp
$(SOURCES_DIR)/protocol.o: $(INCLUDES_DIR)/protocol.hpp 
$(SOURCES_DIR)/event.o: $(INCLUDES_DIR)/event.hpp