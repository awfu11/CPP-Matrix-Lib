CXX = g++
CXXFLAGS = -O2 -Wall -Werror -Wextra -std=c++17 -fsanitize=address
GTEST = -lgtest

CXX_FILES = $(wildcard *.cpp)
OBJ_FILES = $(patsubst %.cpp,%.o,${CXX_FILES})
HEADER_FILES = $(patsubst %.cpp,%.h,${CXX_FILES})

CXX_TEST_FILES = $(wildcard tests/*.cpp)

LIB = s21_matrix_oop.a

all: test

clean:
	rm -rf $(LIB)
	rm -rf *.gcda *.gcno unit_tests
	rm -rf .clang-format

$(LIB):
	@$(CXX) $(CXXFLAGS) -c $(CXX_FILES)
	@ar r $(LIB) $(OBJ_FILES)
	@ranlib $(LIB)
	@rm -rf $(OBJ_FILES)

test: $(LIB)
	@$(CXX) $(CXXFLAGS) $(GTEST) -coverage $(CXX_TEST_FILES) $(LIB) -o unit_tests
	@./unit_tests
	@rm -rf *.gcda *.gcno

leaks: test
	@leaks -atExit -- ./unit_tests
	@rm -rf *.gcda *.gcno

clang:
	@brew install clang-format
	clang-format -n -style=google $(CXX_FILES) $(HEADER_FILES) $(TEST_FILES)
	clang-format -i -style=google $(CXX_FILES) $(HEADER_FILES) $(TEST_FILES)
	@rm -rf .clang-format
