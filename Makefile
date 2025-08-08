NAME = ircserv
TEST = area
FLAGS = -Wall -Werror -Wextra -g3
OBJ = obj/main.o obj/server.o
TEST_OBJ = test/obj/testing_area.o

$(NAME): $(OBJ)
	@echo "building $@"
	c++ $(FLAGS) -o $(NAME) $^

$(TEST): $(TEST_OBJ)
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

.PHONY: all clean fclean re run test_all test_clean test_fclean test_re test_run
