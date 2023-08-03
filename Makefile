COMPILER_DIR:= src/compiler

.PHONY: all translator help run clean

all: compiler

compiler:
	@$(MAKE) -C $(COMPILER_DIR) --no-print-directory

clean: 
	@$(MAKE) -C $(COMPILER_DIR) --no-print-directory clean
	$(RM) -r pn_compiled

# %:
#  	@cd $(COMPILER_DIR) && $(MAKE) --no-print-directory $@

