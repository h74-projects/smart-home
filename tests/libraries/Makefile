CXX = g++
CC = $(CXX)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

CFLAGS = -Wall -Werror -Wextra -pedantic -g -fPIC
CXXFLAGS = $(CFLAGS)
CXXFLAGS += -std=c++17 -I$(INCLUDES_DIR)

TARGET_TEMPATURE_SENSOR = libagent_tempature.so
OBJS_TEMPATURE_SENSOR = $(SOURCES_DIR)/agent_tempature.o $(SOURCES_DIR)/protocol.o $(SOURCES_DIR)/event.o\
						$(SOURCES_DIR)/agent_sensor.o

TARGET_ACCESS_SENSOR = libagent_access.so
OBJS_ACCESS_SENSOR = $(SOURCES_DIR)/agent_access.o $(SOURCES_DIR)/protocol.o $(SOURCES_DIR)/event.o\
						$(SOURCES_DIR)/agent_sensor.o

TARGET_AC_SENSOR = libagent_ac.so
OBJS_AC_SENSOR = $(SOURCES_DIR)/agent_ac.o $(SOURCES_DIR)/protocol.o $(SOURCES_DIR)/event.o

TARGET_DOOR_SENSOR = libagent_door.so
OBJS_DOOR_SENSOR = $(SOURCES_DIR)/agent_door.o $(SOURCES_DIR)/protocol.o $(SOURCES_DIR)/event.o

tempature_agent: $(TARGET_TEMPATURE_SENSOR)

access_agent: $(TARGET_ACCESS_SENSOR)

ac_agent: $(TARGET_AC_SENSOR)

door_agent: $(TARGET_DOOR_SENSOR)

$(TARGET_TEMPATURE_SENSOR): $(OBJS_TEMPATURE_SENSOR) 
	$(CC) $(CXXFLAGS) -shared -o $(TARGET_TEMPATURE_SENSOR) $(OBJS_TEMPATURE_SENSOR)

$(TARGET_ACCESS_SENSOR): $(OBJS_ACCESS_SENSOR) 
	$(CC) $(CXXFLAGS) -shared -o $(TARGET_ACCESS_SENSOR) $(OBJS_ACCESS_SENSOR)

$(TARGET_AC_SENSOR): $(OBJS_AC_SENSOR) 
	$(CC) $(CXXFLAGS) -shared -o $(TARGET_AC_SENSOR) $(OBJS_AC_SENSOR)

$(TARGET_DOOR_SENSOR): $(OBJS_DOOR_SENSOR) 
	$(CC) $(CXXFLAGS) -shared -o $(TARGET_DOOR_SENSOR) $(OBJS_DOOR_SENSOR)

.c.o:
	$(CC) $(CXXFLAGS) -cpp $< -o $@

clean:
	$(RM) $(OBJS_TEMPATURE_SENSOR) $(TARGET_TEMPATURE_SENSOR)
	$(RM) $(OBJS_ACCESS_SENSOR) $(TARGET_ACCESS_SENSOR) 
	$(RM) $(OBJS_AC_SENSOR) $(TARGET_AC_SENSOR)
	$(RM) $(OBJS_DOOR_SENSOR) $(TARGET_DOOR_SENSOR)

.PHONY: clean

$(SOURCES_DIR)/agent_tempature.o: $(INCLUDES_DIR)/protocol.hpp $(INCLUDES_DIR)/event.hpp $(INCLUDES_DIR)/agent_sensor.hpp
$(SOURCES_DIR)/agent_access.o: $(INCLUDES_DIR)/protocol.hpp $(INCLUDES_DIR)/event.hpp $(INCLUDES_DIR)/agent_sensor.hpp
$(SOURCES_DIR)/agent_ac.o: $(INCLUDES_DIR)/protocol.hpp $(INCLUDES_DIR)/event.hpp $(INCLUDES_DIR)/agent_controler.hpp
$(SOURCES_DIR)/agent_door.o: $(INCLUDES_DIR)/protocol.hpp $(INCLUDES_DIR)/event.hpp $(INCLUDES_DIR)/agent_controler.hpp
$(SOURCES_DIR)/protocol.o: $(INCLUDES_DIR)/protocol.hpp
$(SOURCES_DIR)/event.o: $(INCLUDES_DIR)/event.hpp
$(SOURCES_DIR)/agent_sensor.o: $(INCLUDES_DIR)/protocol.hpp $(INCLUDES_DIR)/event.hpp $(INCLUDES_DIR)/agent.hpp
$(INCLUDES_DIR)/agent_controler.hpp : $(INCLUDES_DIR)/protocol.hpp $(INCLUDES_DIR)/agent.hpp
