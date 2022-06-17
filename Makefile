
TRANSLATOR_DIR:= src

.PHONY: translator help

translator:
	@cd $(TRANSLATOR_DIR) && $(MAKE) --no-print-directory

help:
	@cd $(TRANSLATOR_DIR) && $(MAKE) --no-print-directory help


