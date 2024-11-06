DIR_ROOT := $(shell cd ..; pwd)

CC := gcc

VPATH += .
VPATH += $(DIR_ROOT)

INCLUDES += -I.
INCLUDES += -I$(DIR_ROOT)/include

FLAGS += -O0 -Wall -Wextra -ggdb -pthread $(INCLUDES) $(DEBUG_DEFINES)
FLAGS += -Wduplicated-cond
FLAGS += -Wduplicated-branches
FLAGS += -Wlogical-op
FLAGS += -Wnull-dereference
FLAGS += -Wdouble-promotion
FLAGS += -Wformat=2
FLAGS += -MMD

CFLAGS := $(FLAGS)
CXXFLAGS := -std=c++11 $(FLAGS)
LDFLAGS := -ggdb -lgtest -lgmock -lpthread -lstdc++ -lm

TESTS += argument_test
TESTS += encoder_test
TESTS += get_opt_test
TESTS += decoder_test
TESTS += server_test

LINE := ================================================================

.PHONY: clean all line check

all: $(addprefix bin/, $(TESTS))

line:
	@ echo $(LINE)

build_and_run:
	@ FAIL=0; \
	for tc in $(addprefix bin/, $(TESTS)); do \
		echo $(LINE); \
		echo ""; \
		echo "$$tc:"; \
		echo ""; \
		make clean $$tc \
		&& echo "" \
		&& if ! ./$$tc; then FAIL=1; fi; \
		echo ""; \
	done; \
	exit $$FAIL

build/%.o: %.cpp $(shell ls $(DIR_ROOT)/include/*.h)
	@ echo building $@
	@ mkdir -p $(dir $@)
	@ $(CC)  $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build/*

very_clean: clean
	rm -rf bin/*

mccabe:
	pmccabe -vt $(SRCS)

bin/%: build/%.o
	@ mkdir -p $(dir $@)
	@ echo linking $@
	@ $(CC) $^ -o $@ $(LDFLAGS)
