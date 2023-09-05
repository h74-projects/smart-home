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

TARGET_HOTWATER_SENSOR = libagent_hot_water.so
OBJS_HOTWATER_SENSOR = $(SOURCES_DIR)/agent_hotwater.o $(SOURCES_DIR)/protocol.o $(SOURCES_DIR)/event.o\
						$(SOURCES_DIR)/agent_sensor.o

TARGET_ACCESS_SENSOR = libagent_access.so
OBJS_ACCESS_SENSOR = $(SOURCES_DIR)/agent_access.o $(SOURCES_DIR)/protocol.o $(SOURCES_DIR)/event.o\
						$(SOURCES_DIR)/agent_sensor.o

TARGET_AC_CONTROLER = libagent_ac.so
OBJS_AC_CONTROLER = $(SOURCES_DIR)/agent_ac.o $(SOURCES_DIR)/protocol.o $(SOURCES_DIR)/event.o

TARGET_DOOR_CONTROLER = libagent_door.so
OBJS_DOOR_CONTROLER = $(SOURCES_DIR)/agent_door.o $(SOURCES_DIR)/protocol.o $(SOURCES_DIR)/event.o

TARGET_WINDOW_CONTROLER = libagent_window.so
OBJS_WINDOW_CONTROLER = $(SOURCES_DIR)/agent_window.o $(SOURCES_DIR)/protocol.o $(SOURCES_DIR)/event.o

TARGET_BOILER_CONTROLER = libagent_boiler.so
OBJS_BOILER_CONTROLER = $(SOURCES_DIR)/agent_boiler.o $(SOURCES_DIR)/protocol.o $(SOURCES_DIR)/event.o

TARGET_LOG_CONTROLER = libagent_log.so
OBJS_LOG_CONTROLER = $(SOURCES_DIR)/agent_log_tempature.o $(SOURCES_DIR)/protocol.o $(SOURCES_DIR)/event.o

all: tempature_agent access_agent ac_agent door_agent window_agent log_agent boiler_agent hot_water_agent

tempature_agent: $(TARGET_TEMPATURE_SENSOR)

hot_water_agent: $(TARGET_HOTWATER_SENSOR)

access_agent: $(TARGET_ACCESS_SENSOR)

ac_agent: $(TARGET_AC_CONTROLER)

door_agent: $(TARGET_DOOR_CONTROLER)

window_agent: $(TARGET_WINDOW_CONTROLER)

boiler_agent: $(TARGET_BOILER_CONTROLER)

log_agent: $(TARGET_LOG_CONTROLER)

$(TARGET_TEMPATURE_SENSOR): $(OBJS_TEMPATURE_SENSOR) 
	$(CC) $(CXXFLAGS) -shared -o $(TARGET_TEMPATURE_SENSOR) $(OBJS_TEMPATURE_SENSOR)

$(TARGET_HOTWATER_SENSOR): $(OBJS_HOTWATER_SENSOR) 
	$(CC) $(CXXFLAGS) -shared -o $(TARGET_HOTWATER_SENSOR) $(OBJS_HOTWATER_SENSOR)

$(TARGET_ACCESS_SENSOR): $(OBJS_ACCESS_SENSOR) 
	$(CC) $(CXXFLAGS) -shared -o $(TARGET_ACCESS_SENSOR) $(OBJS_ACCESS_SENSOR)

$(TARGET_AC_CONTROLER): $(OBJS_AC_CONTROLER) 
	$(CC) $(CXXFLAGS) -shared -o $(TARGET_AC_CONTROLER) $(OBJS_AC_CONTROLER)

$(TARGET_DOOR_CONTROLER): $(OBJS_DOOR_CONTROLER) 
	$(CC) $(CXXFLAGS) -shared -o $(TARGET_DOOR_CONTROLER) $(OBJS_DOOR_CONTROLER)

$(TARGET_WINDOW_CONTROLER): $(OBJS_WINDOW_CONTROLER) 
	$(CC) $(CXXFLAGS) -shared -o $(TARGET_WINDOW_CONTROLER) $(OBJS_WINDOW_CONTROLER)

$(TARGET_LOG_CONTROLER): $(OBJS_LOG_CONTROLER) 
	$(CC) $(CXXFLAGS) -shared -o $(TARGET_LOG_CONTROLER) $(OBJS_LOG_CONTROLER)

$(TARGET_BOILER_CONTROLER): $(OBJS_BOILER_CONTROLER) 
	$(CC) $(CXXFLAGS) -shared -o $(TARGET_BOILER_CONTROLER) $(OBJS_BOILER_CONTROLER)

.c.o:
	$(CC) $(CXXFLAGS) -cpp $< -o $@

clean:
	$(RM) $(OBJS_TEMPATURE_SENSOR) $(TARGET_TEMPATURE_SENSOR)
	$(RM) $(OBJS_HOTWATER_SENSOR) $(TARGET_HOTWATER_SENSOR)
	$(RM) $(OBJS_ACCESS_SENSOR) $(TARGET_ACCESS_SENSOR) 
	$(RM) $(OBJS_AC_CONTROLER) $(TARGET_AC_CONTROLER)
	$(RM) $(OBJS_DOOR_CONTROLER) $(TARGET_DOOR_CONTROLER)
	$(RM) $(OBJS_WINDOW_CONTROLER) $(TARGET_WINDOW_CONTROLER)
	$(RM) $(OBJS_LOG_CONTROLER) $(TARGET_LOG_CONTROLER)
	$(RM) $(OBJS_BOILER_CONTROLER) $(TARGET_BOILER_CONTROLER)

.PHONY: clean

$(SOURCES_DIR)/agent_tempature.o: $(INCLUDES_DIR)/protocol.hpp $(INCLUDES_DIR)/event.hpp $(INCLUDES_DIR)/agent_sensor.hpp
$(SOURCES_DIR)/agent_hotwater.o: $(INCLUDES_DIR)/protocol.hpp $(INCLUDES_DIR)/event.hpp $(INCLUDES_DIR)/agent_sensor.hpp
$(SOURCES_DIR)/agent_access.o: $(INCLUDES_DIR)/protocol.hpp $(INCLUDES_DIR)/event.hpp $(INCLUDES_DIR)/agent_sensor.hpp
$(SOURCES_DIR)/agent_ac.o: $(INCLUDES_DIR)/protocol.hpp $(INCLUDES_DIR)/event.hpp $(INCLUDES_DIR)/agent_controler.hpp
$(SOURCES_DIR)/agent_door.o: $(INCLUDES_DIR)/protocol.hpp $(INCLUDES_DIR)/event.hpp $(INCLUDES_DIR)/agent_controler.hpp
$(SOURCES_DIR)/agent_window.o: $(INCLUDES_DIR)/protocol.hpp $(INCLUDES_DIR)/event.hpp $(INCLUDES_DIR)/agent_controler.hpp
$(SOURCES_DIR)/agent_boiler.o: $(INCLUDES_DIR)/protocol.hpp $(INCLUDES_DIR)/event.hpp $(INCLUDES_DIR)/agent_controler.hpp
$(SOURCES_DIR)/agent_log_tempature.o: $(INCLUDES_DIR)/protocol.hpp $(INCLUDES_DIR)/event.hpp $(INCLUDES_DIR)/agent_controler.hpp
$(SOURCES_DIR)/protocol.o: $(INCLUDES_DIR)/protocol.hpp
$(SOURCES_DIR)/event.o: $(INCLUDES_DIR)/event.hpp
$(SOURCES_DIR)/agent_sensor.o: $(INCLUDES_DIR)/protocol.hpp $(INCLUDES_DIR)/event.hpp $(INCLUDES_DIR)/agent.hpp
$(INCLUDES_DIR)/agent_controler.hpp : $(INCLUDES_DIR)/protocol.hpp $(INCLUDES_DIR)/agent.hpp
