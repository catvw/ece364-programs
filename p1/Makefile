SUBDIRS=hash spell

spellcheck: $(SUBDIRS) main.cpp
	g++ -g -o spellcheck hash/hash.o spell/checker.o main.cpp

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
