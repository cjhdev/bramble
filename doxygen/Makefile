VERSION := $(shell cat ../version)

output:
	(cat doxygen.cfg; echo "PROJECT_NUMBER=v$(VERSION)") | doxygen -

release: clean output
	rm -rf tmp
	mkdir -p tmp/bramble-$(VERSION)-docs
	cp -r output/html/* tmp/bramble-$(VERSION)-docs
	cd tmp && zip -r bramble-$(VERSION)-docs.zip bramble-$(VERSION)-docs

clean:
	rm -rf output
	rm -rf tmp

# we embed this style
fetch_css:
	rm -rf tmp
	rm -rf doxygen-awesome-css
	git clone --depth 1 -b v2.3.3 https://github.com/jothepro/doxygen-awesome-css tmp
	mkdir -p doxygen-awesome-css
	cp tmp/doxygen-awesome* doxygen-awesome-css
	cp tmp/LICENSE doxygen-awesome-css
	rm -rf tmp

.PHONY: fetch_css api-docs release clean output
