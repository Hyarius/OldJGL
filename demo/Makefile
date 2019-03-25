NAME=		graphical_demo

##
##		RESSOURCES
##

INC_DIR = 	$(shell find includes -type d) $(shell find ../includes -type d)
SRC_DIR = 	$(shell find srcs -type d)
OBJ_DIR	=	obj

vpath %.cpp $(foreach dir, $(SRC_DIR), $(dir):)

SRC = 		$(foreach dir, $(SRC_DIR), $(foreach file, $(wildcard $(dir)/*.cpp), $(notdir $(file))))

OBJ=		$(addprefix $(OBJ_DIR)/, $(SRC:%.cpp=%.o))

LIB_DWN =	sdl2 sdl2_image sdl2_mixer sdl2_ttf
LIB =	SDL2 SDL2_image SDL2_mixer SDL2_ttf

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	DWL = sudo apt-get install
	LIB += GLEW GL
	LIB_DWN += glew build-essential libgl1-mesa-dev
else
	DWL = brew
	FRAMEWORK = -framework OpenGL
endif
##
##		COMPILER FLAGS
##

CFLAGS=		-std=c++11 -g -fsanitize=address

IFLAGS =	$(foreach dir, $(INC_DIR), -I$(dir)) $(foreach dir, $(shell find ~/.brew/include -type d), -I$(dir))

LFLAGS = 	-L ~/.brew/lib $(foreach lib, $(LIB), -l$(lib) ) $(FRAMEWORK)

CC=			g++

all:
				make -C .. install
				make $(NAME)

$(NAME):		$(OBJ)
				@echo "Compiling $(NAME) ...\c"
				@$(CC) $(CFLAGS) $(IFLAGS) -o $(NAME) $(OBJ) $(LFLAGS)
				@echo " DONE"

$(OBJ_DIR)/%.o : %.cpp
				@mkdir $(OBJ_DIR) 2> /dev/null || true
				@echo "Compiling $< ...\c"
				@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<
				@echo " DONE"

clean:
				@rm -rf $(OBJ_DIR)
				@echo "clean"

fclean:			clean
				@rm -f $(NAME)
				@echo "fclean"

re:				fclean all

.PHONY:			all clean fclean re
