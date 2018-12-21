EXEC := run_tests
MAIN := test_lib
TESTS := test_interface test_print test_rpcCall test_signature test_tuple
FIXTURES := Arduino


CC := g++
INCLUDE_PATH := .
CC_ARGS := -Wno-pmf-conversions


OBJS := $(addsuffix .o, $(TESTS) $(FIXTURES))

.PHONY: clean distclean


all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -o $@ $(MAIN).cc $^

%.o: %.cc
	$(CC) $(CC_ARGS) -I $(INCLUDE_PATH) -c $<

clean:
	rm -f $(OBJS)

distclean: clean
	rm -f $(EXEC)
