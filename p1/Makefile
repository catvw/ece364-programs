SUBDIRS=hash spell
SPELL_DEPS=$(addsuffix /*.o,$(SUBDIRS))
.SUFFIXES:

.NOTPARALLEL: spellcheck
spellcheck: main.cpp .subdeps $(wildcard $(SPELL_DEPS))
	g++ -g -o spellcheck $(SPELL_DEPS) main.cpp

# simply because make needs to do this first
.subdeps: | $(SUBDIRS)

.PHONY: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: test
test: spellcheck
	./test.sh

.PHONY: debug
debug: spellcheck
	mkdir -p tmp/
	lldb spellcheck

SUBDIRS_CLEAN=$(addprefix -clean-,$(SUBDIRS))

.PHONY: clean
clean: $(SUBDIRS_CLEAN)
	rm -rf spellcheck tmp/

.PHONY: $(SUBDIRS_CLEAN)
$(SUBDIRS_CLEAN):
	$(MAKE) -C $(subst -clean-,,$@) clean
