SRCS := $(wildcard *.c)
TARGETS := $(SRCS:.c=.out)
LFLAG := -L ../Library -lfun -lbitwise -lslist -lins_dis -linfix -lastack -lqueue -lbinarysearch -lclist -lsort -lbs_tree -lapc -ldlist -lhash -lindexer -lrb_tree
CFLAG := -I ../Include

all : ${TARGETS}

%.out : %.c
	gcc $^ ${LFLAG} ${CFLAG} -o $@

clean :
	rm ${TARGETS} 
	
