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
			$(SOURCES_DIR)/subscriber.o $(SOURCES_DIR)/subscribe_manager.o
                    
CLIENT_OBJECTS = $(SOURCES_DIR)/chat_client.o

$(TARGET) : $(OBJECTS)

$(CLIENT_TARGET) : $(CLIENT_OBJECTS)

new_client: $(CLIENT_TARGET)
	@$(CLIENT_TARGET) -v

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
$(SOURCES_DIR)/chat_client.o: $(INCLUDES_DIR)/chat_message.hpp
$(SOURCES_DIR)/server.o: $(INCLUDES_DIR)/subscribe_manager.hpp $(INCLUDES_DIR)/session.hpp 
$(SOURCES_DIR)/session.o: $(INCLUDES_DIR)/subscribe_manager.hpp $(INCLUDES_DIR)/protocol.hpp $(INCLUDES_DIR)/subscriber.hpp 
$(SOURCES_DIR)/protocol.o:  
$(SOURCES_DIR)/subscriber.o: $(INCLUDES_DIR)/protocol.hpp  
$(SOURCES_DIR)/subscribe_manager.o: $(INCLUDES_DIR)/subscriber.hpp $(INCLUDES_DIR)/protocol.hpp
main.o: $(INCLUDES_DIR)/server.hpp


