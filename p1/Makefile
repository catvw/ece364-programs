MAKE_PREFIX=-make.
CLEAN_PREFIX=-clean.

SUBDIRS=hash spell
SUBDIRS_MAKE=$(addprefix $(MAKE_PREFIX), $(SUBDIRS))
SUBDIRS_CLEAN=$(addprefix $(CLEAN_PREFIX),$(SUBDIRS))

SPELL_DEPS=$(addsuffix /*.o,$(SUBDIRS))

.DEFAULT .PHONY .NOTPARALLEL: spellcheck_all
spellcheck_all: -subdirs spellcheck

-subdirs: $(SUBDIRS_MAKE)

.PHONY: $(SUBDIRS_MAKE)
$(SUBDIRS_MAKE):
	$(MAKE) -C $(subst $(MAKE_PREFIX),,$@)

spellcheck: main.cpp $(wildcard $(SPELL_DEPS))
	g++ -g -o spellcheck $(SPELL_DEPS) main.cpp

.PHONY: test
test: spellcheck_all
	./test.sh

.PHONY: debug
debug: spellcheck_all
	mkdir -p tmp/
	lldb spellcheck

.PHONY: clean
clean: $(SUBDIRS_CLEAN)
	rm -rf spellcheck tmp/

.PHONY: $(SUBDIRS_CLEAN)
$(SUBDIRS_CLEAN):
	$(MAKE) -C $(subst $(CLEAN_PREFIX),,$@) clean
