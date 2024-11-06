INCLUDE += -Iinclude

release: single_include/bramble.hpp

single_include/bramble.hpp: $(shell ls include/*.hpp) Makefile
	@ mkdir -p $(dir $@)
	@ ruby tools/sea_pool.rb --include=include --output="$@" include/bramble.hpp

include/bramble_version.hpp: templates/include/bramble_version.hpp.erb version
	@ erb -T 1 $< > $@

doxygen: single_include/bramble.hpp
	mkdir -p tmp/output
	cd doxygen && make release
	cp doxygen/tmp/*.zip tmp/output/

clean:
	rm -rf single_include/*

.PHONY: clean doxygen release
