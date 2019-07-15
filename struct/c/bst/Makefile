
default: build

CC=gcc
CCCOLOR="\033[34m"
LINKCOLOR="\033[34;1m"
SRCCOLOR="\033[33m"
BINCOLOR="\033[37;1m"
MAKECOLOR="\033[32;1m"
ENDCOLOR="\033[0m"

OBJ=bst.o main.o
NAME=bst

build: $(OBJ)
	@echo ""
	@printf '    %b %b\n' $(MAKECOLOR)Make Build...$(ENDCOLOR)
	@echo ""
	$(CC) -g -o $^ -o $(NAME)

%.o: %.c
	@echo ""
	@printf '    %b %b\n' $(MAKECOLOR)Make $<...$(ENDCOLOR)
	@echo ""
	$(CC) -g -std=c99 -c $<

.PHONY: build 

clean:
	rm -rf *.o $(NAME)

.PHONY: clean

