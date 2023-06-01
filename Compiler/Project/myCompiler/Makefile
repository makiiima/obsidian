CXX = clang++
LEX = flex
YACC = bison

CXXFLAGS = -g -Wall
BUILD_DIR = build
SRC_DIR = src

.PHONY: all clean

all: $(BUILD_DIR)/compiler

$(BUILD_DIR)/compiler: $(BUILD_DIR)/main.o $(BUILD_DIR)/compiler.tab.o $(BUILD_DIR)/compiler.yy.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -ll

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(BUILD_DIR)/compiler.tab.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/compiler.tab.o: $(SRC_DIR)/compiler.y | $(BUILD_DIR)
	$(YACC) -d -o $(BUILD_DIR)/compiler.tab.c $<
	$(CXX) $(CXXFLAGS) -c -o $@ $(BUILD_DIR)/compiler.tab.c

$(BUILD_DIR)/compiler.yy.o: $(SRC_DIR)/compiler.l | $(BUILD_DIR)
	$(LEX) -o $(BUILD_DIR)/compiler.yy.c $<
	$(CXX) $(CXXFLAGS) -c -o $@ $(BUILD_DIR)/compiler.yy.c

$(BUILD_DIR)/compiler.tab.h: $(SRC_DIR)/compiler.y | $(BUILD_DIR)
	$(YACC) -d -o $(BUILD_DIR)/compiler.tab.c $<

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: clean-all
clean-all: clean
	rm -f compiler
