# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/30 18:50:48 by mmunoz-f          #+#    #+#              #
#    Updated: 2021/12/06 19:43:43 by mmunoz-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = clang++
CXXFLAGS = -Wall -Werror -Wextra -fsanitize=address -g3
LEAKS = -D M_LEAKS=1 

M =

NAME =

SRCS =
OBJS = $(SRCS:.cpp=.o)

TEST_SRCS = test/utils_tester.cpp test/std_vector_test.cpp test/ft_vector_test.cpp test/std_map_test.cpp test/ft_map_test.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

all: utils v m

utils: test/utils_tester.o
	$(CXX) $(CXXFLAGS) -o $@ $^
	./$@

v: fclean test/std_vector_test.o test/ft_vector_test.o
	$(CXX) $(CXXFLAGS) -o std_vector_test test/std_vector_test.o
	$(CXX) $(CXXFLAGS) -o ft_vector_test test/ft_vector_test.o
	./ft_vector_test > uno
	./std_vector_test > dos
	diff uno dos
	rm uno dos

m: fclean test/std_map_test.o test/ft_map_test.o
	$(CXX) $(CXXFLAGS) -o std_map_test test/std_map_test.o
	$(CXX) $(CXXFLAGS) -o ft_map_test test/ft_map_test.o
	./ft_map_test > uno
	./std_map_test > dos
	diff uno dos
	rm uno dos

v_leaks: fclean
	$(CXX) $(CXXFLAGS) $(LEAKS) -o ft_vector_test test/ft_vector_test.cpp
	./ft_vector_test

m_leaks: fclean
	$(CXX) $(CXXFLAGS) $(LEAKS) -o ft_map_test test/ft_map_test.cpp
	./ft_map_test

clean:
	rm -f $(OBJS) $(PRUEBA_OBJS) $(TEST_OBJS)

fclean: clean
	rm -f $(NAME) tester std_vector_test ft_vector_test std_map_test ft_map_test

re: fclean all

push: fclean
	git add .
	git commit -m "$M"
	git push origin master

.PHONY: all clean fclean re prueba tester v push
