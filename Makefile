# ------------------- EDIT THIS SECTION -------------------
BIN_NAME ?= nclass

BIN_DIR ?= .
BUILD_DIR ?= ./build
SRC_DIRS ?= ./src ./include
INC_DIRS += ./include ./njson/include
CPPFLAGS ?= -Wall -Wextra -std=c++11

NJSON := njson/libnjson.a

LDFLAGS ?= -L njson/ -lnjson

MAC_LDFLAGS :=
WIN_LDFLAGS :=
LINUX_LDFLAGS :=

# --------------------------- END -------------------------

SRCS := $(shell find $(SRC_DIRS) -name *.cpp) $(shell find $(SRC_DIRS) -name *.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
INC_FLAGS += $(addprefix -I,$(INC_DIRS))
CPPFLAGS += -fPIC $(INC_FLAGS) -MMD -MP
CFLAGS += -fPIC $(INC_FLAGS) -MMD -MP

# --------------------------- OS DETECTION ----------------

# ifeq ($(OS),Windows_NT)
# 	LDFLAGS += $(WIN_LDFLAGS)
# else
# 	UNAME_S := $(shell uname -s)
# 	ifeq ($(UNAME_S),Linux)
# 	LDFLAGS += $(LINUX_LDFLAGS)
# 	endif
# 	ifeq ($(UNAME_S),Darwin)
# 	LDFLAGS += $(MAC_LDFLAGS)
# 	endif
# endif

TARGET := $(BIN_NAME)

# -------------------------------- END ---------------------

.PHONY: all

all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJS)
	@echo "Linking files..."
	@$(CXX) -o $@ $(OBJS) $(LDFLAGS)
	@echo "Done!"

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp $(NJSON)
	@$(MKDIR_P) $(dir $@)
	@echo "Compiling: " $<
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(NJSON):
	$(MAKE) -C njson/

# c source
$(BUILD_DIR)/%.c.o: %.c
	@$(MKDIR_P) $(dir $@)
	@echo "Compiling: " $<
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: fclean clean re

clean:
	$(RM) -r $(BUILD_DIR)

fclean: clean
	$(RM) $(BIN_DIR)/$(TARGET)

re: clean all

-include $(DEPS)

MKDIR_P ?= mkdir -p