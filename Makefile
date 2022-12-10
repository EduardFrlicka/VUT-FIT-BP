COMPILER_DIR:= src/compiler

.PHONY: all translator help run clean

all: compiler

compiler:
	@$(MAKE) -C $(COMPILER_DIR) --no-print-directory

run: compiler
	./bin/compiler tests/sample.pn

clean: 
	@$(MAKE) -C $(COMPILER_DIR) --no-print-directory clean

# %:
#  	@cd $(COMPILER_DIR) && $(MAKE) --no-print-directory $@

