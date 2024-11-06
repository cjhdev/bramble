bin/main: build/main.o
	@ mkdir -p $(dir $@)
	@ echo linking $@
	@ $(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf build/*

very_clean: clean
	rm -rf bin/*

OBJ := $(subst $(DIR_ROOT),build,$(OBJ3))

FLAGS += -O0 -Wall -Wextra -ggdb -I../../include
FLAGS += -Wduplicated-cond
FLAGS += -Wduplicated-branches
FLAGS += -Wlogical-op
FLAGS += -Wnull-dereference
FLAGS += -Wdouble-promotion
FLAGS += -Wformat=2
FLAGS += -MMD
FLAGS += -pthread

CFLAGS := $(FLAGS)
CXXFLAGS := -std=c++11 $(FLAGS)
LDFLAGS := -ggdb -lstdc++ -lm -lpthread

build/%.o: %.cpp
	@ echo building $@
	@ mkdir -p $(dir $@)
	@ $(CC)  $(CXXFLAGS) -c $< -o $@

check: CC := clang
check: CFLAGS += --analyze -Xanalyzer -analyzer-output=text
check: CXXFLAGS += --analyze -Xanalyzer -analyzer-output=text -stdlib=libc++
check: build/main.o

-include $(shell find build -type f -name '*.d')
