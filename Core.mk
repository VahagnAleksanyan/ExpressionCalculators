CURDIR := $(shell pwd)/

ifeq ($(findstring src,$(CURDIR)),src)
  SUBPROJECTTYPE := src
endif
ifeq ($(findstring tst,$(CURDIR)),tst)
  SUBPROJECTTYPE := tst
endif

ifeq ($(SUBPROJECTKIND),lib)
  SUBPROJECTCOMPILINGFLAGS :=
  SUBPROJECTLINKINGFLAGS   := -shared
  SUBPROJECTTARGET         := ../../lib/lib$(PROJECTNAME)$(SUBPROJECTNAME).so
endif
ifeq ($(SUBPROJECTKIND),bin)
  SUBPROJECTCOMPILINGFLAGS :=
  SUBPROJECTLINKINGFLAGS   :=
  SUBPROJECTTARGET         := ../../bin/$(PROJECTNAME)$(SUBPROJECTNAME)
endif

SUBPROJECTSOURCES := $(addprefix $(CURDIR),$(notdir $(shell find  -name '*.cpp')))
SUBPROJECTOBJECTS := $(subst .cpp,.obj,$(subst $(SUBPROJECTTYPE),obj,$(SUBPROJECTSOURCES)))

.PHONY: all
all : $(SUBPROJECTTARGET)
$(SUBPROJECTTARGET) : $(SUBPROJECTOBJECTS)
	@mkdir -p $(dir $(SUBPROJECTTARGET))
	/usr/bin/time -f '%E %MKb -- for $@' $(CXX) $(CXXSTD) $(SUBPROJECTOBJECTS) -o $@ $(CXXLINKINGFLAGS) $(SUBPROJECTLINKINGFLAGS) $(SUBPROJECTLIBS)

$(SUBPROJECTOBJECTS) :
	@mkdir -p $(dir $(SUBPROJECTOBJECTS))
	/usr/bin/time -f '%E %MKb -- for $@' $(CXX) $(CXXSTD) $(subst obj,$(SUBPROJECTTYPE),$(subst .obj,.cpp,$@)) -o $@ $(CXXCOMPILINGFLAGS) $(SUBPROJECTCOMPILINGFLAGS) -MMD -MF $(subst .obj,.dep,$@)

-include $(subst .obj,.dep,$(SUBPROJECTOBJECTS))
