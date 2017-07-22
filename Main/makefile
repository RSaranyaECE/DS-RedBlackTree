SRCS := $(wildcard *.c)
TARGETS := $(SRCS:.c=.out)
LFLAG := -L ../Library -lrb_tree
CFLAG := -I ../Include

all : ${TARGETS}

%.out : %.c
	gcc $^ ${LFLAG} ${CFLAG} -o $@

clean :
	rm ${TARGETS} 
	
