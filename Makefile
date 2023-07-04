
#编译使用的平台 Windows Linux
# HOST_OS = Windows

#相关配置
ifeq ($(HOST_OS), Windows)
	CC  	= gcc
	LD  	= gcc
	DBG		= gdb

	RM 		= del
	MK_DIR 	= mkdir
	RM_DIR 	= rmdir /s /q

	LINK_SCRIPT = link.ld

	OUT_BIN = scheduler.exe

	CINCLUDE_FILE_FLAG = -Iinclude
else
	CC  	= gcc
	LD  	= gcc
	DBG		= gdb

	RM 		= del
	MK_DIR 	= mkdir
	RM_DIR 	= rm -rf

	LINK_SCRIPT = link_linux.ld

	OUT_BIN = scheduler

	CINCLUDE_FILE_FLAG = -Iinclude
endif

OUT_MAP = scheduler.map

CLINK_FLAGS += -g -ffunction-sections -fdata-sections -Wl,-T "$(LINK_SCRIPT)"
CFLAGS		+= -g -ffunction-sections -fdata-sections -O0

#不需要处理的目录路径
SRC_DIR = src
OUT_DIR = output
#需要处理的目录路径
OBJ_DIR_ORIG = $(OUT_DIR)/obj
BIN_DIR_ORIG = $(OUT_DIR)/bin

#要编译的文件
obj-y += main.o
obj-y += cat_scheduler.o
obj-y += static_prio_sched.o
obj-y += edf_sched.o

#处理要编译的文件
OBJ_TARGET_ORIG = $(patsubst %,$(OBJ_DIR)/%,$(obj-y))

ifeq ($(HOST_OS), Windows)
OBJ_DIR = $(subst /,\\,$(OBJ_DIR_ORIG))
BIN_DIR = $(subst /,\\,$(BIN_DIR_ORIG))
OBJ_TARGET = $(subst /,\\,$(OBJ_TARGET_ORIG))
else
OBJ_DIR = $(OBJ_DIR_ORIG)
BIN_DIR = $(BIN_DIR_ORIG)
OBJ_TARGET = $(OBJ_TARGET_ORIG)
endif

all: $(OUT_BIN)

ifeq ($(HOST_OS), Windows)
$(OUT_BIN): $(BIN_DIR) $(OBJ_TARGET)
	$(LD) $(CLINK_FLAGS) -Wl,-Map,$(BIN_DIR)\\$(OUT_MAP) -o $(BIN_DIR)\\$@ $(OBJ_TARGET)

$(BIN_DIR):
	$(MK_DIR) $(OUT_DIR)
	$(MK_DIR) $(OBJ_DIR)
	$(MK_DIR) $(BIN_DIR)

$(OBJ_DIR)\\%.o: $(SRC_DIR)\\%.c
	$(CC) $(CINCLUDE_FILE_FLAG) $(CFLAGS) -o $@ -c $<

run: $(BIN_DIR)\\$(OUT_BIN)
	@$(BIN_DIR)\\$(OUT_BIN)

dbg: $(BIN_DIR)\\$(OUT_BIN)
	gdb $(BIN_DIR)\\$(OUT_BIN)
else
$(OUT_BIN): $(BIN_DIR) $(OBJ_TARGET)
	$(LD) $(CLINK_FLAGS) -Wl,-Map,$(BIN_DIR)/$(OUT_MAP) -o $(BIN_DIR)/$@ $(OBJ_TARGET)

$(BIN_DIR):
	$(MK_DIR) $(OUT_DIR)
	$(MK_DIR) $(OBJ_DIR)
	$(MK_DIR) $(BIN_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CINCLUDE_FILE_FLAG) $(CFLAGS) -o $@ -c $<

run: $(BIN_DIR)/$(OUT_BIN)
	@$(BIN_DIR)/$(OUT_BIN)

dbg: $(BIN_DIR)/$(OUT_BIN)
	gdb $(BIN_DIR)/$(OUT_BIN)
endif


clean:
	$(RM_DIR) $(OUT_DIR)


