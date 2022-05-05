EXEC := run_tests
MAIN := test_lib
TESTS := test_tuple test_vector test_print test_read test_write test_types \
  test_signature test_interface test_rpcCall
FIXTURES := arduino-serial-fixture/src/Arduino


CC := g++
CC_ARGS := -std=c++11 -Wno-pmf-conversions \
  -I arduino-serial-fixture/src -I plugins


OBJS := $(addsuffix .o, $(TESTS) $(FIXTURES))

.PHONY: all check clean distclean


all: $(EXEC)

$(EXEC): $(MAIN).cc $(OBJS)
	$(CC) $(CC_ARGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CC_ARGS) -o $@ -c $<

%.o: %.cc
	$(CC) $(CC_ARGS) -o $@ -c $<

check: all
	valgrind ./$(EXEC)

clean:
	rm -f $(OBJS)

distclean: clean
	rm -f $(EXEC)
