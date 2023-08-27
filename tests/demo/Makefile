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

TARGET = main     
                   
OBJECTS = main.o $(SOURCES_DIR)/server.o $(SOURCES_DIR)/session.o $(SOURCES_DIR)/protocol.o\
			$(SOURCES_DIR)/subscriber.o $(SOURCES_DIR)/subscribe_manager.o $(SOURCES_DIR)/event.o\
			$(SOURCES_DIR)/agent_tempature.o

AGENT_CONTROLER_TARGET = $(SOURCES_DIR)/agent_controler                     
AGENT_CONTROLER_OBJECTS = $(SOURCES_DIR)/agent_controler.o $(SOURCES_DIR)/client.o $(SOURCES_DIR)/event.o\
							 $(SOURCES_DIR)/protocol.o

$(TARGET) : $(OBJECTS)

$(AGENT_CONTROLER_TARGET) : $(AGENT_CONTROLER_OBJECTS)

check : $(TARGET)
	@./$(TARGET) -v

agent_controler: $(AGENT_CONTROLER_TARGET)
	@./$(AGENT_CONTROLER_TARGET) -v 

recheck: clean check

clean:
	@$(RM) $(TARGET) $(OBJECTS)
	@$(RM) $(AGENT_CONTROLER_TARGET) $(AGENT_CONTROLER_OBJECTS)

val: $(TARGET)
	valgrind --leak-check=yes -s -q ./main

hell: $(TARGET)
	valgrind --tool=helgrind --max-threads=500 -s ./$(TARGET) 2> hell.log

.PHONY: clean all val hell check recheck


# dependencies
$(SOURCES_DIR)/event.o: $(INCLUDES_DIR)/event.hpp
$(SOURCES_DIR)/server.o: $(INCLUDES_DIR)/subscribe_manager.hpp $(INCLUDES_DIR)/session.hpp $(INCLUDES_DIR)/agent_tempature.hpp
$(SOURCES_DIR)/session.o: $(INCLUDES_DIR)/subscribe_manager.hpp $(INCLUDES_DIR)/protocol.hpp $(INCLUDES_DIR)/subscriber.hpp\
						  $(INCLUDES_DIR)/agent_tempature.hpp	
$(SOURCES_DIR)/protocol.o: $(INCLUDES_DIR)/protocol.hpp
$(SOURCES_DIR)/subscriber.o: $(INCLUDES_DIR)/protocol.hpp  
$(SOURCES_DIR)/subscribe_manager.o: $(INCLUDES_DIR)/subscriber.hpp $(INCLUDES_DIR)/protocol.hpp
$(SOURCES_DIR)/client.o: $(INCLUDES_DIR)/protocol.hpp
$(SOURCES_DIR)/agent_tempature.o: $(INCLUDES_DIR)/protocol.hpp $(INCLUDES_DIR)/event.hpp
main.o: $(INCLUDES_DIR)/server.hpp


