CC=g++

CXXFLAGS= -g 
LDFLAGS= -g

RBTree:main.cc rbtree.h rbtreeNode.h
	$(CC) $(CXXFLAGS) -o RBTree main.cc

.PHONY:clean

clean:
	@rm -f *.o
	@rm -f RBTree

