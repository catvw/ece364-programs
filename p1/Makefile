SUBDIRS=hash spell
SPELL_DEPS=$(addsuffix /*.o,$(SUBDIRS))

spellcheck: $(SUBDIRS) main.cpp
	g++ -g -o spellcheck $(SPELL_DEPS) main.cpp

.PHONY: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@

SUBDIRS_CLEAN=$(addprefix -clean-,$(SUBDIRS))

.PHONY: clean
clean: $(SUBDIRS_CLEAN)
	rm -f spellcheck

.PHONY: $(SUBDIRS_CLEAN)
$(SUBDIRS_CLEAN):
	$(MAKE) -C $(subst -clean-,,$@) clean
