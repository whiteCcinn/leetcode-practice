
default: help

CC=gcc
CCCOLOR="\033[34m"
LINKCOLOR="\033[34;1m"
SRCCOLOR="\033[33m"
BINCOLOR="\033[37;1m"
MAKECOLOR="\033[32;1m"
ENDCOLOR="\033[0m"

AL=invertTree lcp-1

.PHONY: help
help:
	@echo ""
	@printf '    %b %b %b %b %b\n' make [$(SRCCOLOR)$(AL)$(ENDCOLOR)]
	@echo ""

clean:
	rm -rf $(AL)

.PHONY: clean

.PHONY: invertTree

invertTree:
	gcc -std=c99 -lbst -L. -I../struct/c/bst invertTree.c -o invertTree
	@printf '%b %b\n' $(MAKECOLOR)[build complete...]$(ENDCOLOR)

.PHONY: lcp-1

lcp-1:
	gcc -std=c99 lcp-1.c -o lcp-1
	@printf '%b %b\n' $(MAKECOLOR)[build complete...]$(ENDCOLOR)

.PHONY: isUnivalTree

isUnivalTree:
	gcc -std=c99 -lbst -L. -I../struct/c/bst isUnivalTree.c -o isUnivalTree
	@printf '%b %b\n' $(MAKECOLOR)[build complete...]$(ENDCOLOR)

.PHONY: coinChange

coinChange:
	gcc -std=c99 coinChange.c -o coinChange
	@printf '%b %b\n' $(MAKECOLOR)[build complete...]$(ENDCOLOR)

.PHONY: LRU

LRU:
	gcc -std=c99 LRU.c -o LRU
	@printf '%b %b\n' $(MAKECOLOR)[build complete...]$(ENDCOLOR)