export PROJECTNAME := ExpressionCalculators
export PROJECTPATH := $(shell pwd)/

export CXX               := g++
export CXXSTD            := -std=c++20
export CXXCOMPILINGFLAGS := -c -g3 -fPIC -O3 -Wall -Werror -I $(PROJECTPATH)int/include/ $(MACROS)
export CXXLINKINGFLAGS   := -rdynamic -L $(PROJECTPATH)int/lib/ -Wl,--rpath=$(PROJECTPATH)int/lib/

ifeq ($(logs),all)
  export LOGS := Core,Client,Tests
else
  export LOGS := $(logs)
endif

rebuild : clean all

tests : all
	@make -C tst/ExpressionCalculatorsTest

all : int
	@make -C src/Core
	@make -C src/Client

int :
	@mkdir -p int
	@mkdir -p int/include
	@ln -sf ../../src int/include/ExpressionCalculators
	@ln -sf ../lib int/lib

clean :
	rm -rf obj lib int ext bin

