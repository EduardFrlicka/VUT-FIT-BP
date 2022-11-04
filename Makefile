
COMPILER_DIR:= src/compiler

.PHONY: all translator help

all: translator

translator:
	@cd $(COMPILER_DIR) && $(MAKE) --no-print-directory

help:
	@cd $(COMPILER_DIR) && $(MAKE) --no-print-directory help

%:
	@cd $(COMPILER_DIR) && $(MAKE) --no-print-directory $@

