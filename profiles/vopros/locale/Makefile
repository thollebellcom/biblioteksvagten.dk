ROOT = ../../..
COMBINED=da.po
MODULES = $(shell ls -d ../modules/vopros/vopros*)
MODULE_POTS = $(shell ls ../modules/vopros/vopros*/translations/*.pot)
THEME_FILES = ../themes/vopros_admin/template.php,../themes/vopros_admin/vopros_admin.info
PROFILE_FILES = profiles/vopros/vopros.install,profiles/vopros/vopros.profile,profiles/vopros/vopros.info
PROFILE_POT = $(ROOT)/profiles/vopros/translations/vopros.pot
POT_FILES = $(MODULE_POTS) $(PROFILE_POT)

master: $(COMBINED)

templates: modules $(PROFILE_POT)

translations: $(patsubst %.pot,%.po,$(POT_FILES))

vopros: $(PROFILE_POT)

# Merge in 
import:
	msgcat --use-first $(COMBINED) $(FILE) > import.po
	msgmerge import.po vopros.pot > da.po
	rm import.po

$(PROFILE_POT):
	drush potx single --files=$(PROFILE_FILES) && \
	mv $(ROOT)/installer.pot $(ROOT)/profiles/vopros/translations/vopros.pot

modules:
	for path in $(MODULES); do \
	  module=`basename $$path` && \
	  echo $$module && \
	  drush potx single --modules=$$module ; \
	  mkdir -p $$path/translations && \
	  mv $(ROOT)/general.pot $$path/translations/$$module.pot ; \
	done

# no strings in theme at the moment.
# themes:
# 	drush potx single --files=$(THEME_FILES) && \
# 	mv $(ROOT)/general.pot themes/vopros_admin/translations/vopros_admin.pot

$(patsubst %.pot,%.po,$(POT_FILES)): %.po: %.pot $(COMBINED)
	# Update with new strings.
	msgmerge $(COMBINED) $< | msgattrib --no-fuzzy --no-obsolete > $(dir $@)/da.po

vopros.pot: $(POT_FILES)
	msgcat $(POT_FILES) > vopros.pot

$(COMBINED): vopros.pot
	msgmerge -U da.po vopros.pot
	# | msgattrib --no-obsolete > $(patsubst %.pot,%.po,$@)
