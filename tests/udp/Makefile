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

SERVER_TARGET = $(SOURCES_DIR)/udp.server                  
SERVER_OBJECTS = $(SOURCES_DIR)/udp.server.o

CLIENT_TARGET = $(SOURCES_DIR)/udp.client                     
CLIENT_OBJECTS = $(SOURCES_DIR)/udp.client.o

$(SERVER_TARGET) : $(SERVER_OBJECTS)

$(CLIENT_TARGET) : $(CLIENT_OBJECTS)

new_client: $(CLIENT_TARGET)
	@$(CLIENT_TARGET) -v

new_server: $(SERVER_TARGET)
	@$(SERVER_TARGET) -v

check : $(TARGET)
	@./$(TARGET) -v

recheck: clean check

clean:
	@$(RM) $(TARGET) $(OBJECTS)

val: $(TARGET)
	valgrind --leak-check=yes -s -q ./utest

hell: $(TARGET)
	valgrind --tool=helgrind --max-threads=500 -s ./$(TARGET) 2> hell.log

.PHONY: clean all val hell check recheck


# dependencies
