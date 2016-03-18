SRCS      = $(wildcard *.c)
OBJS      = $(patsubst %.c, %.o, $(SRCS))

all : $(OBJS)
	@echo $@ "\$\@"
	@echo $^
	@echo $%
	@echo $<
	@echo $*

$(OBJS):$(SRCS)
