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

TARGET = utest                     
OBJECTS = utest.o

SERVER_TARGET = $(SOURCES_DIR)/chat_server                     
SERVER_OBJECTS = $(SOURCES_DIR)/chat_server.o

CLIENT_TARGET = $(SOURCES_DIR)/chat_client                     
CLIENT_OBJECTS = $(SOURCES_DIR)/chat_client.o $(SOURCES_DIR)/client.o $(SOURCES_DIR)/event.o

$(TARGET) : $(OBJECTS)

$(SERVER_TARGET) : $(SERVER_OBJECTS)

$(CLIENT_TARGET) : $(CLIENT_OBJECTS)

new_client: $(CLIENT_TARGET)
	@$(CLIENT_TARGET) -v

new_server: $(SERVER_TARGET)
	@$(SERVER_TARGET) 3001 -v


check : $(TARGET)
	@./$(TARGET) -v

recheck: clean check

clean:
	@$(RM) $(TARGET) $(OBJECTS)
	@$(RM) $(SERVER_TARGET) $(SERVER_OBJECTS)
	@$(RM) $(CLIENT_TARGET) $(CLIENT_OBJECTS)

val: $(TARGET)
	valgrind --leak-check=yes -s -q ./utest

hell: $(TARGET)
	valgrind --tool=helgrind --max-threads=500 -s ./$(TARGET) 2> hell.log

.PHONY: clean all val hell check recheck


# dependencies
$(SOURCES_DIR)/chat_client.o: $(INCLUDES_DIR)/chat_message.hpp $(INCLUDES_DIR)/event.hpp\
							  $(INCLUDES_DIR)/client.hpp
$(SOURCES_DIR)/chat_server.o: $(INCLUDES_DIR)/chat_message.hpp
$(SOURCES_DIR)/client.o: $(INCLUDES_DIR)/client.hpp $(INCLUDES_DIR)/chat_message.hpp
