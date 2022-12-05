# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/21 15:45:25 by eraita            #+#    #+#              #
#    Updated: 2022/09/01 17:44:56 by ecamara          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC =   ft_isalpha.c\
		ft_isdigit.c\
		ft_isalnum.c\
		ft_isascii.c\
		ft_isprint.c\
		ft_strlen.c\
		ft_strlcpy.c\
		ft_strlcat.c\
		ft_strncmp.c\
		ft_strcmp.c\
		ft_toupper.c\
		ft_tolower.c\
		ft_strnstr.c\
		ft_atoi.c\
		ft_strchr.c\
		ft_strrchr.c\
		ft_memset.c\
		ft_bzero.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_calloc.c\
		ft_strdup.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_strtrim.c\
		ft_split.c\
		ft_itoa.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_strmapi.c\
		ft_striteri.c\
		get_next_line.c\
		get_next_line_utils.c\
		ft_lstnew.c\
		ft_lstadd_front.c\
        ft_lstsize.c\
        ft_lstlast.c\
        ft_lstadd_back.c\
        ft_lstdelone.c\
        ft_lstclear.c\
        ft_lstiter.c\
        ft_lstmap.c\
		ft_atoi_double.c\
		ft_printf_csdi.c\
		ft_printf_u.c\
		ft_printf_xxp.c\
		ft_printf.c\
		ft_atod.c\
		ft_strlen2d.c\
		ft_c_str_cmp.c\
		ft_split_str.c\
		ft_dtoa.c	\
		
INCLUDES = libft.h

OBJ = $(SRC:.c=.o)

CC = gcc
AR = ar rc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f



all: $(NAME)

$(NAME) : $(OBJ) $(INCLUDES)
	@$(AR) $(NAME) $(OBJ)

%.o : %.c
	@$(CC) $(CFLAGS) -c $(SRC) $(SRC_BONUS)



clean:
	@$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
