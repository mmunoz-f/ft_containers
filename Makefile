# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/30 18:50:48 by mmunoz-f          #+#    #+#              #
#    Updated: 2021/10/07 21:34:02 by mmunoz-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = clang++
CXXFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

M =

NAME =

SRCS =
OBJS = $(SRCS:.cpp=.o)

PRUEBA_SRCS = test/pruebas.cpp
PRUEBA_OBJS = $(PRUEBA_SRCS:.cpp=.o)

TEST_SRCS = test/utils_tester.cpp test/vector_test.cpp test/ft_vector_test.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

prueba: $(PRUEBA_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(PRUEBA_OBJS)
	./$@

tester: test/pruebas.o
	$(CXX) $(CXXFLAGS) -o $@ $^
	./$@

v: fclean test/vector_test.o test/ft_vector_test.o
	$(CXX) $(CXXFLAGS) -o vector_test test/vector_test.o
	./vector_test
	$(CXX) $(CXXFLAGS) -o ft_vector_test test/ft_vector_test.o
	./ft_vector_test

clean:
	rm -f $(OBJS) $(PRUEBA_OBJS) $(TEST_OBJS)

fclean: clean
	rm -f $(NAME) prueba tester vector_test ft_vector_test

re: fclean all

push: fclean
	git add .
	git commit -m "$M"
	git push origin master

.PHONY: all clean fclean re prueba tester v push
