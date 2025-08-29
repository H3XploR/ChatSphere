NAME = ircserv
TEST = area
FLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address -fsanitize=leak -fsanitize=undefined
OBJ = obj/server.o obj/channel.o obj/client.o obj/parser.o
OBJ_MAIN = obj/main.o 
TEST_OBJ = test/obj/testing_area.o

$(NAME): $(OBJ) $(OBJ_MAIN)
	@echo "building $@"
	c++ $(FLAGS) -o $(NAME) $^

$(TEST): $(OBJ) $(TEST_OBJ)
	@echo "building $@"
	c++ $(FLAGS) -o $(TEST) $^

test/obj/%.o: test/%.cpp
	@mkdir -p test/obj
	@echo "building $@"
	c++ $(FLAGS) -o $@ -c $<

obj/%.o: src/%.cpp
	@mkdir -p obj
	@echo "building $@"
	c++ $(FLAGS) -o $@ -c $<

all: $(NAME)

clean:
	@echo "removing obj..."
	@rm -rf obj

fclean: clean
	@echo "removing all..."
	@rm $(NAME)

re: fclean all

run: all
	@./$(NAME)

test_all: $(TEST)

test_clean:
	@echo "removing obj..."
	@rm -rf test/obj

test_fclean: test_clean
	@echo "removing all..."
	@rm $(TEST)

test_re: test_fclean test_all

test_run: test_all
	@./$(TEST)

test_debug: test_all
	@ lldb $(TEST)
.PHONY: all clean fclean re run test_all test_clean test_fclean test_re test_run
