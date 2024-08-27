CC = gcc
CC+ = g++
FLAGS = -Wall -Wextra -Werror
FLAGS_CXX = -Wall -Wextra -Werror  -std=c++17
FLAGS_C= -Wall -Werror -Wextra -std=c11
SANITIZE=-fsanitize=address -g
TESTFLAGS=-lgtest 
LCOVFLAGS= --ignore-errors inconsistent --ignore-errors mismatch
SNAKE_TERM_MAKE=2
TETRIS_TERM_MAKE=2	
SNAKE_MODE=1



BACK_SNAKE=$(wildcard brick_game/snake/*.cpp)
BACK_TETRIS=$(wildcard brick_game/tetris/*.c)
OBJ_BACK_SNAKE=$(BACK_SNAKE:.cpp=.o)
OBJ_BACK_TETRIS=$(BACK_TETRIS:.c=.o)
all: install

bool_cli_tetris:
	$(MAKE) TETRIS_TERM_MAKE=1 main_tetris_term

bool_cli_snake: 
	$(MAKE) SNAKE_TERM_MAKE=1 main_snake_term
	 

%.o: %.cpp
ifeq ($(SNAKE_TERM_MAKE), 1)
	$(CC+) $(FLAGS_CXX) $(SANITIZE) -D SNAKE_CLI -c $< -o $@
else
	$(CC+) $(FLAGS_CXX) -D SNAKE_DESK -c $< -o $@
endif

%.o: %.c
ifeq ($(TETRIS_TERM_MAKE), 1)
	$(CC) $(FLAGS_C) -D TETRIS_CLI -c $< -o $@
else
	$(CC) $(FLAGS_C) -D TETRIS_DESK -c $< -o $@
endif


clang-format:
	clang-format -i *.cpp *.h brick_game/*/*.cpp brick_game/*/*.h gui/*/*.cpp gui/*/*.h

test: mkbuild back_lib_snake
	$(CC+) $(FLAGS_CXX) $(TESTFLAGS) build/back_lib_snake.a tests/check.cpp -o test 

gcov_report: add_coverage_flag test
	./test
	lcov -t "check" -o check.info -c -d ./  --no-external $(LCOVFLAGS)
	genhtml -o report check.info $(LCOVFLAGS)
	open report/index.html

add_coverage_flag:
	$(eval FLAGS_CXX += --coverage)

$(LIB_NAME).a: $(OBJS)
	ar rc $(LIB_NAME).a $^
	ranlib $(LIB_NAME).a
	rm -rf *.o

snake_cmake_desktop:
	cd build && cmake ../ -DSNAKE_MODE=1 && make snake_desktop  && ./snake_desktop.app/Contents/MacOS/snake_desktop

clean:
	rm -rf dist.tar.gz doxygen latex report html */*.o test */*.a build rm -rf *.o tests/*.o test *.a *.gcno *.gcda *.gcov *.html *.css  *.dSYM */*/*.a */*/*.gcno */*/*.gcda */*/*.gcov */*/*.html */*/*.css  */*/*.dSYM

install: mkbuild back_lib_snake snake_cmake_desktop

desktop_tetris: mkbuild back_lib_tetris tetris_cmake_desktop

tetris_cmake_desktop:
	cd build && cmake ../ -DSNAKE_MODE=0 && make tetris_desktop && ./tetris_desktop.app/Contents/MacOS/tetris_desktop

term_tetris: mkbuild bool_cli_tetris
	echo "\033[32mGame installed \033[0m"
	cd build && ./tetris_term

term_snake : mkbuild bool_cli_snake 
	echo "\033[32mGame installed \033[0m"
	cd build && ./snake_term

mkbuild:
	rm -rf build/
	mkdir build

main: mkbuild back_lib_snake
	$(CC+) $(FLAGS_CXX) build/back_lib_snake.a main.cpp -o main 


front_lib_cli:
	$(CC) $(FLAGS_C) -D SNAKE_CLI -c gui/cli/cview.c -o gui/cli/cview.o
	ar rc build/front_lib_cli.a gui/cli/cview.o
	ranlib build/front_lib_cli.a 
	rm  gui/cli/*.o

back_lib_snake : $(OBJ_BACK_SNAKE) 
	ar rc build/back_lib_snake.a $^
	ranlib build/back_lib_snake.a 
	rm brick_game/snake/*.o

main_snake_term: back_lib_snake front_lib_cli
	$(CC+) $(FLAGS_CXX) $(SANITIZE) -lncurses -D SNAKE_CLI build/back_lib_snake.a build/front_lib_cli.a snake.cpp -o build/snake_term

main_tetris_term: back_lib_tetris front_lib_cli
	$(CC+) $(FLAGS_CXX) $(SANITIZE) -lncurses -D TETRIS_CLI build/back_lib_tetris.a build/front_lib_cli.a tetris.cpp -o build/tetris_term


back_lib_tetris : $(OBJ_BACK_TETRIS) 
	ar rc build/back_lib_tetris.a $^
	ranlib build/back_lib_tetris.a 
	rm brick_game/tetris/*.o

dvi:
	@doxygen .Doxyfile
	@open doxygen/html/index.html
dist: install
	@rm -rf dist.tar.gz
	@tar -cvzf dist.tar.gz build/snake_desktop.app/Contents/MacOS/snake_desktop