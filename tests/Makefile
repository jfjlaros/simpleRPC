EXEC := run_tests
MAIN := test_lib
TESTS := test_interface test_print test_rpcCall test_types test_signature \
  test_tuple test_read test_write
FIXTURES := arduino-serial-fixture/src/Arduino


CC := g++
INCLUDE_PATH := arduino-serial-fixture/src
CC_ARGS := -Wno-pmf-conversions -std=c++11


OBJS := $(addsuffix .o, $(TESTS) $(FIXTURES))

.PHONY: check clean distclean


all: $(EXEC)

$(EXEC): $(MAIN).cc $(OBJS)
	$(CC) -o $@ $^

%.o: %.cc
	$(CC) $(CC_ARGS) -I $(INCLUDE_PATH) -o $@ -c $<

check: all
	./$(EXEC)

clean:
	rm -f $(OBJS)

distclean: clean
	rm -f $(EXEC)
