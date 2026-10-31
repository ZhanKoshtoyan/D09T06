CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
LDFLAGS = -lm

# Пути к исходным папкам (относительно текущей директории Makefile)
DATA_LIBS_DIR = ../data_libs
DATA_MODULE_DIR = ../data_module
DECISION_DIR = ../yet_another_decision_module

# Исходные файлы
SRCS = $(DATA_LIBS_DIR)/data_io.c \
       $(DATA_LIBS_DIR)/data_stat.c \
       $(DATA_MODULE_DIR)/data_process.c \
       $(DECISION_DIR)/decision.c \
       main_executable_module.c

# Целевой файл (в корне репозитория, папка build)
TARGET = ../../build/Quest_3

# Пути для заголовков
INCLUDES = -I$(DATA_LIBS_DIR) -I$(DATA_MODULE_DIR) -I$(DECISION_DIR)

all: $(TARGET)

$(TARGET): $(SRCS)
	@mkdir -p ../../build
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild