EXEC := tests
MAIN := test_lib
TESTS := test_types test_print
FIXTURES := Arduino


CC := g++
INCLUDE_PATH := .


OBJS := $(addsuffix .o, $(TESTS) $(FIXTURES))

.PHONY: clean distclean


all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -I $(INCLUDE_PATH) -o $@ $(MAIN).cc $^

%.o: %.cc
	$(CC) -I $(INCLUDE_PATH) -c $<

clean:
	rm -f $(OBJS)

distclean: clean
	rm -f $(EXEC)
