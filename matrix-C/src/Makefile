CC := gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
GCOVFLAGS = -g -fprofile-arcs -ftest-coverage
LDFLAGS := -lcheck -lm -lsubunit

TARGET = s21_matrix.a
TEST_TARGET := test

TARGETDIR := .
BUILDDIR := ./build
TESTDIR := ./tests
GCOVDIR := ./gcov
SOURCEDIR := .

SOURCES = $(wildcard ./*.c)
OBJECTS := $(patsubst %.c, %.o, $(SOURCES))
TEST_SOURCES := $(wildcard $(TESTDIR)/*.c)
TEST_OBJECTS := $(foreach object, $(patsubst %.c, %.o, $(SOURCES)), $(notdir $(object)))

$(TARGET): $(OBJECTS)
	ar rcs $(TARGETDIR)/$@ $(foreach object,$^,$(BUILDDIR)/$(notdir $(object)))

%.o: %.c
	@mkdir -p $(BUILDDIR)
	@$(CC) $(CFLAGS) -c $< -o $(foreach object,$@,$(BUILDDIR)/$(notdir $(object)))

all: $(TARGET)

clean:
	@rm -rf $(BUILDDIR)/* $(TARGETDIR)/$(TARGET) test $(GCOVDIR) valgrind.txt *.gcda *.gcno
	@rm -rf *.gcov *.info out test_coverage
	@rm -f ../src/*.o

clang-n:
	clang-format --style=google -n $(TESTDIR)/*.c $(TESTDIR)/*.h $(TARGETDIR)/*.c $(TARGETDIR)/*.h

clang-i:
	clang-format --style=google -i $(TESTDIR)/*.c $(TESTDIR)/*.h $(TARGETDIR)/*.c $(TARGETDIR)/*.h

test: LDFLAGS += -lcheck -lsubunit -lrt -lm -lpthread
test: all
	$(CC) -o test $(TEST_SOURCES) $(foreach object, $(TEST_OBJECTS), $(BUILDDIR)/$(object)) $(LDFLAGS) -L. -l:s21_matrix.a
	./test

gcov_report: CFLAGS += $(GCOVFLAGS)
gcov_report: clean
	$(foreach source,$(SOURCES),$(CC) $(CFLAGS) -c $(source) -o $(basename $(notdir $(source))).o;)
	$(CC) $(CFLAGS) $(TEST_SOURCES) *.o -o test_coverage $(LDFLAGS) -lsubunit
	./test_coverage
	gcov $(SOURCES)
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory out

valgrind: LDFLAGS += -lcheck -lsubunit -lrt -lm -lpthread
valgrind: all $(TEST_OBJECTS)
	$(CC) -o test $(TEST_SOURCES) $(foreach object, $(TEST_OBJECTS), $(BUILDDIR)/$(object)) $(LDFLAGS) -L. -l:s21_matrix.a
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --log-file="valgrind.txt" ./test

.PHONY: all clean test gcov_report valgrind