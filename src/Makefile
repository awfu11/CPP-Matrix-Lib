CPP = g++
FLAGS = -Wall -Werror -Wextra -std=c++17
CPP_FILES = $(wildcard *.cpp)
OBJ_FILES = $(patsubst %.cpp,%.o,${CPP_FILES})
HEADER_FILES = $(patsubst %.cpp,%.hpp,${CPP_FILES})
LIB = s21_matrix_oop.a

all: test

clean:
	rm -rf $(LIB)
	rm -rf *.gcda *.gcno unit_tests
	rm -rf .clang-format

$(LIB):
	@$(CPP) $(FLAGS) -c $(CPP_FILES)
	@ar r $(LIB) $(OBJ_FILES)
	@ranlib $(LIB)
	@rm -rf $(OBJ_FILES)

test: $(LIB)
	@$(CPP) $(FLAGS) -lgtest -coverage tests/*.cpp $(LIB) -o unit_tests
	@./unit_tests
	@rm -rf *.gcda *.gcno

leaks: test
	@leaks -atExit -- ./unit_tests
	@rm -rf *.gcda *.gcno

clang:
	@cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -n -style=google $(CPP_FILES) $(HEADER_FILES) $(TEST_FILES)
	clang-format -i -style=google $(CPP_FILES) $(HEADER_FILES) $(TEST_FILES)
	@rm -rf .clang-format