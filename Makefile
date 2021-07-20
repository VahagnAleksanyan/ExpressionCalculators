export PROJECTNAME := ExpressionCalculators
export PROJECTPATH := $(shell pwd)/

ifeq ($(withLogs),)
  withLogs := no
endif

ifeq ($(withLogs),yes)
  MACROS := -DEXPRESSIONCALCULATORS_LOGGING
endif
ifeq ($(withLogs),no)
  MACROS :=
endif

export CXX               := g++
export CXXSTD            := -std=c++20
export CXXCOMPILINGFLAGS := -c -g3 -fPIC -O3 -Wall -Werror -I $(PROJECTPATH)int/include/ $(MACROS)
export CXXLINKINGFLAGS   := -rdynamic -I $(PROJECTPATH)int/include/ -L $(PROJECTPATH)int/lib/ -Wl,--rpath=$(PROJECTPATH)int/lib/

rebuild : clean all

all : int
	@make -C src/ExpressionCalculators
	@make -C src/Client

int :
	@mkdir -p int
	@ln -sf ../src int/include
	@ln -sf ../lib int/lib

clean :
	rm -rf obj lib int ext bin

