# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agerbaud <agerbaud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/30 14:21:12 by agerbaud          #+#    #+#              #
#    Updated: 2025/05/27 11:45:53 by agerbaud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = PmergeMe

SRCS =	sources/main.cpp		\
		sources/Pair.cpp		\
		sources/PmergeMe.cpp

CXX = c++
CFLAGS = -Wall -Wextra -Werror -MMD -std=c++98

OBJECTS = $(SRCS:.cpp=.o)
DEPENDENCIES = $(SRCS:.cpp=.d)


all: $(NAME)

$(NAME): $(OBJECTS)
	$(CXX) $(CFLAGS) -o $@ $^

-include $(DEPENDENCIES)

%.o: %.cpp
	$(CXX) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJECTS) $(DEPENDENCIES)

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re