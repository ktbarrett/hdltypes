# project automation makefile
# this was only ever intended for the developer and *not* for official use
# in CI or distribution. If that level of PA is required, a cross-platform
# solution should be developed. gh-27

.PHONY:
	configure
	build
	install
	uninstall
	clean
	test
	coverage

BUILD_DIR ?= build/
CXX_FLAGS ?= -Wall -Wextra
CXX_STANDARD ?= 14

ifdef COVERAGE
	CXX_FLAGS += -O0 -g --coverage
else ifneq ($(CMAKE_BUILD_TYPE),)
	CMAKE_ARGS += -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE)
endif

CMAKE_ARGS += -DCMAKE_CXX_FLAGS="$(CXX_FLAGS)" -DCMAKE_CXX_STANDARD=$(CXX_STANDARD)

CURRENT_LIST_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

test: build
	cmake --build $(BUILD_DIR) --target test_hdltypes
	$(BUILD_DIR)/tests/test_hdltypes

coverage:
	$(MAKE) COVERAGE=1 test
	lcov -c -d $(BUILD_DIR)/tests/CMakeFiles/ -o $(BUILD_DIR)/cov.info \
		--include "$(CURRENT_LIST_DIR)include/*" \
		--include "$(CURRENT_LIST_DIR)src/*"
	genhtml $(BUILD_DIR)/cov.info -o $(BUILD_DIR)/cov_html
	xdg-open $(BUILD_DIR)/cov_html/index.html

configure:
	cmake -S $(CURRENT_LIST_DIR) -B $(BUILD_DIR) $(CMAKE_ARGS)

build: configure
	cmake --build $(BUILD_DIR)

install: build
	cmake --install $(BUILD_DIR)

uninstall:
	-@test -f $(BUILD_DIR)/install_manifest.txt && xargs rm -fv < $(BUILD_DIR)/install_manifest.txt

clean: uninstall
	-@rm -rf $(BUILD_DIR)

format:
	git ls-files | grep --color=never ".\(hpp\|cpp\|h\|c\)$$" | xargs clang-format -i
