# Variables

# C++ compiler
CXX = g++

# C++ standard
STDCXX = -std=c++20

# Source file
SRC = hello.cxx

# Executable name
EXE = hello

# Build directory
BUILDDIR = build

# Recipes are a name followed by a colon and its dependencies
# eg. `name: dep1 dep2`

# Builds debug and release
all: debug release

# Builds release and runs
run: all run-release

# Cleans output files
clean:
	@echo "Cleaning..."
	rm $(BUILDDIR)/**/$(EXE)
	@echo "Done!"

# Runs the release build
run-release: release
	$(BUILDDIR)/release/$(EXE)

# Builds release config
release: dirs
	@echo "Compiling Release..."
	$(CXX) $(STDCXX) -o $(BUILDDIR)/release/$(EXE) $(SRC)
	@echo  "Done!"

# Runs debug build
run-debug: debug
	$(BUILDDIR)/debug/$(EXE)

# Build debug config
debug: dirs
	@echo "Compiling Debug..."
	$(CXX) -g $(STDCXX) -o $(BUILDDIR)/debug/$(EXE) $(SRC)
	@echo  "Done!"

# Create need directories
dirs:
	@echo "Making output directories..."
	mkdir -p $(BUILDDIR)/debug
	mkdir -p $(BUILDDIR)/release
	@echo "Done!"