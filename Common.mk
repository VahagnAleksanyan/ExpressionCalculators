src.% : deps.%
	@$(MAKE) -C $(PROJECTPATH)/src/$* all

tst.% : deps.%
	@$(MAKE) -C $(PROJECTPATH)/tst/$* all

.PHONY: int
int :
	@mkdir -p $(PROJECTPATH)/int
	@mkdir -p $(PROJECTPATH)/int/include
	@ln -sfn $(PROJECTPATH)/src $(PROJECTPATH)/int/include/ExpressionCalculators
	@ln -sfn $(PROJECTPATH)/lib $(PROJECTPATH)/int/lib
	@echo ====== Internal dependency ======

.PHONY: clean
clean :
	rm -rf obj lib int ext bin

