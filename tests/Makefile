EXEC := run_tests
MAIN := test_lib
TESTS := test_tuple test_vector test_print test_read test_write test_types \
  test_signature test_interface test_rpcCall
FIXTURES := arduino-serial-fixture/src/Arduino
LIBS := ../src/plugins/hardwareserial/io


CC := g++
INCLUDE_PATH := arduino-serial-fixture/src
CC_ARGS := -Wno-pmf-conversions -std=c++11


OBJS := $(addsuffix .o, $(TESTS) $(FIXTURES) $(LIBS))

.PHONY: all check clean distclean


all: $(EXEC)

$(EXEC): $(MAIN).cc $(OBJS)
	$(CC) $(CC_ARGS) -I $(INCLUDE_PATH) -o $@ $^

%.o: %.cpp
	$(CC) $(CC_ARGS) -I $(INCLUDE_PATH) -o $@ -c $<

%.o: %.cc
	$(CC) $(CC_ARGS) -I $(INCLUDE_PATH) -o $@ -c $<

check: all
	valgrind ./$(EXEC)

clean:
	rm -f $(OBJS)

distclean: clean
	rm -f $(EXEC)
