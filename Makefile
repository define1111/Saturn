ROOT_INCLUDE_DIR           := include/Saturn
ROOT_SOURCE_DIR            := src
ROOT_TEST_DIR              := test

SOURCE_SUBDIR_ALG          := algebraic_structures
SOURCE_SUBDIR_DATA         := data_structures

SOURCE_FILES               += $(ROOT_SOURCE_DIR)/$(SOURCE_SUBDIR_ALG)/numerical_group_ring_cyclic_group_8bit.c
SOURCE_FILES               += $(ROOT_SOURCE_DIR)/$(SOURCE_SUBDIR_ALG)/permutation.c

SOURCE_FILES               += $(ROOT_SOURCE_DIR)/$(SOURCE_SUBDIR_DATA)/set.c
SOURCE_FILES               += $(ROOT_SOURCE_DIR)/$(SOURCE_SUBDIR_DATA)/bitset.c
SOURCE_FILES               += $(ROOT_SOURCE_DIR)/$(SOURCE_SUBDIR_DATA)/bitset_tree.c
SOURCE_FILES               += $(ROOT_SOURCE_DIR)/$(SOURCE_SUBDIR_DATA)/stack.c

TEST_GR_OP_FILES           += $(ROOT_TEST_DIR)/numerical_group_ring_cyclic_group/test_add.c

TEST_BITSET_FILES          = $(ROOT_TEST_DIR)/data_structures/test_bitset.c

TARGET_ZERO_DIVISORS_FILES += $(ROOT_SOURCE_DIR)/target/search_zero_divisors.c

OBJECT_FILES                         := $(SOURCE_FILES:.o=.c)
OBJECT_TEST_GR_OP_FILES              := $(TEST_GR_OP_FILES:.o=.c)
OBJECT_TEST_BITSET_FILES             := $(TEST_BITSET_FILES:.o=.c)
OBJECT_TARGET_ZERO_DIVISORS_FILES    := $(TARGET_ZERO_DIVISORS_FILES:.o=.c)

%.o: %.c
	$(CC) $(CLAGS) -c $< -o $@

CC = gcc
CFLAGS = -O3 -Wall -Wextra -I $(ROOT_INCLUDE_DIR) -lm

test_gr_op: $(OBJECT_FILES) $(OBJECT_TEST_GR_OP_FILES)
	$(CC) $^ -o $@ $(CFLAGS)

test_bitset: $(OBJECT_FILES) $(OBJECT_TEST_BITSET_FILES)
	$(CC) $^ -o $@ $(CFLAGS)

target_zero_divisors: $(OBJECT_FILES) $(OBJECT_TARGET_ZERO_DIVISORS_FILES)
	$(CC) $^ -o $@ $(CFLAGS)
