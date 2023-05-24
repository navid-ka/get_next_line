NAME = GNL
CFLAGS = -Wall -Werror -Wextra -D BUFFER_SIZE=xx 
OBJECTS = get_next_line.c get_next_line_utils.c
COLOR_RESET = \033[0m
COLOR = \033[32m
KAOMOJI_SUCCESS = (づ ᴗ _ᴗ)づ♡
KAOMOJI_REMOVE = (ノಠ益ಠ)ノ彡┻━┻

${NAME}: ${OBJECTS}
	@cc ${CFLAGS} ${OBJECTS} -o ${NAME}
	@printf "$(COLOR)Main program compiled successfully!$(COLOR_RESET)\n"

all: ${NAME}

fclean: clean
	@rm -rf ${NAME}
	@printf "$(COLOR)Cleaned directory! $(KAOMOJI_REMOVE)$(COLOR_RESET)\n"

clean:
	@rm -f ${NAME}
	@printf "$(COLOR)Cleaned object files! $(KAOMOJI_REMOVE)$(COLOR_RESET)\n"

re: fclean all

git: fclean
	@echo "Commit:"
	@read message; \
	git commit -am "$$message"
	git push

.PHONY: clean all fclean re main
