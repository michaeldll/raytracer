CXX ?= clang++
CXXFLAGS ?= -std=c++14 -O0 -ggdb -march=native -Wall -Wextra -Wpedantic -I./src

SRCDIR := src
SOURCES := $(wildcard $(SRCDIR)/*.cpp)

OBJDIR := bin
BIN := $(OBJDIR)/main

OUTDIR := renders
OUTFILE := $(OUTDIR)/render.ppm

.PHONY: build build-dev build-prod render clear test

build: build-dev

# Force rebuild for dev and prod, to override binary when necessary
build-dev: | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(SOURCES)

# Remove debug information on prod
build-prod: CXXFLAGS := $(subst -O0,-O2,$(filter-out -ggdb,$(CXXFLAGS)))
build-prod: | $(OBJDIR)
build-prod:
	$(CXX) $(CXXFLAGS) -o $(BIN) $(SOURCES)

$(BIN): $(SOURCES) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -o $@ $(SOURCES)

$(OBJDIR):
	mkdir -p $@

# Render an image from binary
render: build
	@mkdir -p $(OUTDIR)
	@$(BIN) > $(OUTFILE)
	@echo "Wrote $(OUTFILE)"

test:
	@bash tests/run_tests.sh

# Delete binary and render folders
clear: 
	rm -rf ./bin	
	rm -rf ./renders