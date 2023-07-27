COMPILER_DIR:= src/compiler

.PHONY: all translator help run clean

all: compiler

compiler:
	@$(MAKE) -C $(COMPILER_DIR) --no-print-directory

run: compiler
	$(RM) -r pn_compiled
	./bin/compiler tests/sample.pn


runmake : run
	@$(MAKE) -C pn_compiled --no-print-directory run

clean: 
	@$(MAKE) -C $(COMPILER_DIR) --no-print-directory clean

# %:
#  	@cd $(COMPILER_DIR) && $(MAKE) --no-print-directory $@

