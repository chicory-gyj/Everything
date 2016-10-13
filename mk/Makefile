SRCS      = $(wildcard *.c)
OBJS      = $(patsubst %.c, %.o, $(SRCS))
all : $(OBJS)

a.o b.o : a.c b.c
	gcc $<
	@echo $@
	@echo 'xixi'

clean: 
	rm -rf $(OBJS)
