CC=g++

CXXFLAGS= -g 
LDFLAGS= -g

RBT:main.cc rbt.h rbt_node.h color.h
	$(CC) $(CXXFLAGS) -o RBT main.cc

.PHONY:clean

clean:
	@rm -f *.o
	@rm -f RBT
	@rm -fr RBT.dSYM

