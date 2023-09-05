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

TCP_SENSOR_ACCESS_TARGET = $(SOURCES_DIR)/tcp_access_sensor                    
TCP_SENSOR_ACCESS_OBJECTS = $(SOURCES_DIR)/tcp_access_sensor.o $(SOURCES_DIR)/client.o $(SOURCES_DIR)/protocol.o

UDP_SENSOR_TARGET = $(SOURCES_DIR)/udp_sensor                    
UDP_SENSOR_OBJECTS = $(SOURCES_DIR)/udp_sensor.o $(SOURCES_DIR)/protocol.o

UDP_HOTWATER_TARGET = $(SOURCES_DIR)/udp_hot_water                    
UDP_HOTWATER_OBJECTS = $(SOURCES_DIR)/udp_hot_water.o $(SOURCES_DIR)/protocol.o

UDP_CONTROLER_TARGET = $(SOURCES_DIR)/udp_controler                     
UDP_CONTROLER_OBJECTS = $(SOURCES_DIR)/udp_controler.o $(SOURCES_DIR)/event.o\
							 $(SOURCES_DIR)/protocol.o

$(TCP_CONTROLER_TARGET) : $(TCP_CONTROLER_OBJECTS)

$(UDP_CONTROLER_TARGET) : $(UDP_CONTROLER_OBJECTS)

$(TCP_SENSOR_TARGET) : $(TCP_SENSOR_OBJECTS)

$(TCP_SENSOR_ACCESS_TARGET) : $(TCP_SENSOR_ACCESS_OBJECTS)

$(UDP_SENSOR_TARGET) : $(UDP_SENSOR_OBJECTS)

$(UDP_HOTWATER_TARGET) : $(UDP_HOTWATER_OBJECTS)

all: $(TCP_SENSOR_TARGET) $(TCP_SENSOR_ACCESS_TARGET) $(UDP_SENSOR_TARGET) $(TCP_CONTROLER_TARGET) $(UDP_CONTROLER_TARGET) $(UDP_HOTWATER_TARGET)

tcp_sensor: $(TCP_SENSOR_TARGET)
	@./$(TCP_SENSOR_TARGET) -v

tcp_access_sensor: $(TCP_SENSOR_ACCESS_TARGET)
	@./$(TCP_SENSOR_ACCESS_TARGET) -v

udp_sensor: $(UDP_SENSOR_TARGET)
	@./$(UDP_SENSOR_TARGET) -v

udp_hot_water: $(UDP_HOTWATER_TARGET)
	@./$(UDP_HOTWATER_TARGET) -v

tcp_controler: $(TCP_CONTROLER_TARGET)
	@./$(TCP_CONTROLER_TARGET) -v 

udp_controler: $(UDP_CONTROLER_TARGET)
	@./$(UDP_CONTROLER_TARGET) -v

recheck: clean check

clean:
	@$(RM) $(TCP_CONTROLER_TARGET) $(TCP_CONTROLER_OBJECTS)
	@$(RM) $(UDP_CONTROLER_TARGET) $(UDP_CONTROLER_OBJECTS)
	@$(RM) $(TCP_SENSOR_TARGET) $(TCP_SENSOR_OBJECTS)
	@$(RM) $(TCP_SENSOR_ACCESS_TARGET) $(TCP_SENSOR_ACCESS_OBJECTS)
	@$(RM) $(UDP_SENSOR_TARGET) $(UDP_SENSOR_OBJECTS)
	@$(RM) $(UDP_HOTWATER_TARGET) $(UDP_HOTWATER_OBJECTS)

val: $(TCP_CONTROLER_TARGET) $(TCP_SENSOR_TARGET) $(UDP_SENSOR_TARGET) $(TCP_SENSOR_ACCESS_TARGET) $(UDP_CONTROLER_TARGET)
	valgrind --leak-check=yes -s -q ./utest

hell: $(TCP_CONTROLER_TARGET) $(TCP_SENSOR_TARGET) $(UDP_SENSOR_TARGET) $(TCP_SENSOR_ACCESS_TARGET) $(UDP_CONTROLER_TARGET)
	valgrind --tool=helgrind --max-threads=500 -s ./$(TARGET) 2> hell.log

.PHONY: clean all val hell check recheck


# dependencies
$(SOURCES_DIR)/client.o: $(INCLUDES_DIR)/protocol.hpp
$(SOURCES_DIR)/protocol.o: $(INCLUDES_DIR)/protocol.hpp 
$(SOURCES_DIR)/event.o: $(INCLUDES_DIR)/event.hpp