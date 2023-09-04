CXX = g++
CC = $(CXX)

CFLAGS = -Wall -Werror
CFLAGS+= -Wextra
CFLAGS+= -pedantic -g
CFLAGS+= -pthread

LDFLAGS = -ldl
CXXFLAGS = $(CFLAGS)
CXXFLAGS += -std=c++17 -I$(INCLUDES_DIR)

LDLIBS += -lpthread 
LDLIBS += -ldl

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

TARGET = main     
                   
OBJECTS = main.o $(SOURCES_DIR)/server.o $(SOURCES_DIR)/session.o $(SOURCES_DIR)/protocol.o\
				 $(SOURCES_DIR)/subscribe_manager.o $(SOURCES_DIR)/event.o $(SOURCES_DIR)/session_udp.o\
				 $(SOURCES_DIR)/agent_ac.o $(SOURCES_DIR)/agent_sensor.o $(SOURCES_DIR)/smart_building.o\
				 $(SOURCES_DIR)/udp_server.o


$(TARGET): $(OBJECTS)

check : $(TARGET)
	@./$(TARGET) -v

recheck: clean check

clean:
	@$(RM) $(TARGET) $(OBJECTS)

val: $(TARGET)
	valgrind --leak-check=yes -s -q ./main

hell: $(TARGET)
	valgrind --tool=helgrind --max-threads=500 -s ./$(TARGET) 2> hell.log

.PHONY: clean all val hell check recheck


# dependencies
$(SOURCES_DIR)/event.o: $(INCLUDES_DIR)/event.hpp
$(SOURCES_DIR)/server.o: $(INCLUDES_DIR)/subscribe_manager.hpp $(INCLUDES_DIR)/session.hpp $(INCLUDES_DIR)/agent.hpp $(INCLUDES_DIR)/session_udp.hpp
$(SOURCES_DIR)/udp_server.o: $(INCLUDES_DIR)/subscribe_manager.hpp $(INCLUDES_DIR)/session.hpp $(INCLUDES_DIR)/agent.hpp $(INCLUDES_DIR)/session_udp.hpp
$(SOURCES_DIR)/session.o: $(INCLUDES_DIR)/subscribe_manager.hpp $(INCLUDES_DIR)/protocol.hpp $(INCLUDES_DIR)/subscriber.hpp\
						  $(INCLUDES_DIR)/agent_tempature.hpp $(INCLUDES_DIR)/agent.hpp
$(SOURCES_DIR)/session_udp.o: $(INCLUDES_DIR)/subscribe_manager.hpp $(INCLUDES_DIR)/protocol.hpp $(INCLUDES_DIR)/subscriber.hpp\
						  $(INCLUDES_DIR)/agent_tempature.hpp $(INCLUDES_DIR)/agent.hpp
$(SOURCES_DIR)/protocol.o: $(INCLUDES_DIR)/protocol.hpp
$(INCLUDES_DIR)/agent_controler.hpp : $(INCLUDES_DIR)/protocol.hpp $(INCLUDES_DIR)/agent.hpp
$(SOURCES_DIR)/agent_sensor.o: $(INCLUDES_DIR)/protocol.hpp $(INCLUDES_DIR)/event.hpp $(INCLUDES_DIR)/agent.hpp
$(SOURCES_DIR)/subscribe_manager.o: $(INCLUDES_DIR)/subscriber.hpp $(INCLUDES_DIR)/protocol.hpp
$(SOURCES_DIR)/client.o: $(INCLUDES_DIR)/protocol.hpp
$(SOURCES_DIR)/smart_building.o: $(INCLUDES_DIR)/server.hpp $(INCLUDES_DIR)/agent_tempature.hpp $(INCLUDES_DIR)/agent_ac.hpp\
				 $(INCLUDES_DIR)/subscribe_manager.hpp $(INCLUDES_DIR)/session_udp.hpp $(INCLUDES_DIR)/smart_building.hpp
main.o: $(INCLUDES_DIR)/smart_building.hpp


