TARGET = hostapd

SOURCES_PATH = ./:
vpath %.c $(SOURCES_PATH) 
SOURCES = $(wildcard $(subst :,/*.c,$(SOURCES_PATH)))
SOURCES_NODIR = $(notdir $(SOURCES)) 
OBJS = $(patsubst %.c, %.o, $(SOURCES_NODIR))

INCLUDE = -I./
CFLAGS = -lrt

$(TARGET): $(OBJS)
	gcc -o $@ $(INCLUDE) $(CFLAGS) $(OBJS)
