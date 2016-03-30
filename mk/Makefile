SRCS      = $(wildcard *.c)
OBJS      = $(patsubst %.c, %.o, $(SRCS))

i% : $(OBJS)
	@echo $@ "1 \$\@"
	@echo $^ "3 \$\^"
	@echo $% "2 \$\%"
	@echo $<
	@echo $*

%.o : %.c
	@echo $* "\$\*"

clean: 
	rm -rf $(OBJS)
