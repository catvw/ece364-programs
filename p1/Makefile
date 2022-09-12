SUBDIRS=hash spell
SPELL_DEPS=$(addsuffix /*.o,$(SUBDIRS))

spellcheck: main.cpp $(wildcard $(SPELL_DEPS)) | $(SUBDIRS)
	g++ -g -o spellcheck $(SPELL_DEPS) main.cpp

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
