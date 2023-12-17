BUILD_DIR := build
SRC_DIR := src
INC_DIR := include
TEST_DIR := test

JOBS ?= 4

.PHONY: all
all: test

.PHONY: init
init:
	git submodule init
	git submodule update

.PHONY: build
build: init
	cmake -S $(PWD) -B $(PWD)/$(BUILD_DIR)
	cmake --build $(PWD)/$(BUILD_DIR) --parallel $(JOBS)

.PHONY: test
test: build
	export GTEST_COLOR=1 && ctest --test-dir $(PWD)/$(BUILD_DIR)/test --parallel $(JOBS) --output-on-failure

.PHONY: clean
.SILENT: clean
clean:
	rm -rf $(PWD)/$(BUILD_DIR)
