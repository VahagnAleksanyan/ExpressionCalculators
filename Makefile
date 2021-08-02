export PROJECTNAME := ExpressionCalculators
export PROJECTPATH := $(shell pwd)

export CXX               := g++
export CXXSTD            := -std=c++20
export CXXCOMPILINGFLAGS := -c -g3 -fPIC -O3 -Wall -Werror -I $(PROJECTPATH)/int/include/ $(MACROS)
export CXXLINKINGFLAGS   := -rdynamic -L $(PROJECTPATH)/int/lib/ -Wl,--rpath=$(PROJECTPATH)/int/lib/

ifeq ($(logs),all)
  export LOGS := Core,Client,Tests
else
  export LOGS := $(logs)
endif


# Dependencies
tests                          : int src.Core tst.ExpressionCalculatorsTest
all                            : int src.Core src.Client
deps.ExpressionCalculatorsTest : int src.Core
deps.Client                    : int src.Core
deps.Core                      : int

include Common.mk

