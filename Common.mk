src.% : deps.%
	@$(MAKE) -C $(PROJECTPATH)/src/$* all

tst.% : deps.%
	@$(MAKE) -C $(PROJECTPATH)/tst/$* all

.PHONY: int
int :
	@mkdir -p int
	@mkdir -p int/include
	@ln -sf $(PROJECTPATH)/src int/include/ExpressionCalculators
	@ln -sf $(PROJECTPATH)/lib int/lib

.PHONY: clean
clean :
	rm -rf obj lib int ext bin

