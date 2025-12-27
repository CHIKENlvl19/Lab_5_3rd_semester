CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O2
DEBUG_FLAGS = -g -O0 -DDEBUG
INCLUDE_PATH = -I./include

# Директории
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
DOMAIN_DIR = $(SRC_DIR)/domain
SERVICES_DIR = $(SRC_DIR)/services
FACTORIES_DIR = $(SRC_DIR)/factories
REPOSITORIES_DIR = $(SRC_DIR)/repositories
STRATEGIES_DIR = $(SRC_DIR)/strategies

# Выходные файлы
TARGET = $(BIN_DIR)/grade_system
TARGET_DEBUG = $(BIN_DIR)/grade_system_debug

# Исходные файлы
DOMAIN_SOURCES = $(wildcard $(DOMAIN_DIR)/*.cpp)
SERVICES_SOURCES = $(wildcard $(SERVICES_DIR)/*.cpp)
FACTORIES_SOURCES = $(wildcard $(FACTORIES_DIR)/*.cpp)
REPOSITORIES_SOURCES = $(wildcard $(REPOSITORIES_DIR)/*.cpp)
STRATEGIES_SOURCES = $(wildcard $(STRATEGIES_DIR)/*.cpp)
MAIN_SOURCE = $(SRC_DIR)/main.cpp

# Все исходники (без main.cpp)
SOURCES = $(DOMAIN_SOURCES) $(SERVICES_SOURCES) $(FACTORIES_SOURCES) \
          $(REPOSITORIES_SOURCES) $(STRATEGIES_SOURCES)

# Объектные файлы
DOMAIN_OBJECTS = $(patsubst $(DOMAIN_DIR)/%.cpp,$(OBJ_DIR)/domain/%.o,$(DOMAIN_SOURCES))
SERVICES_OBJECTS = $(patsubst $(SERVICES_DIR)/%.cpp,$(OBJ_DIR)/services/%.o,$(SERVICES_SOURCES))
FACTORIES_OBJECTS = $(patsubst $(FACTORIES_DIR)/%.cpp,$(OBJ_DIR)/factories/%.o,$(FACTORIES_SOURCES))
REPOSITORIES_OBJECTS = $(patsubst $(REPOSITORIES_DIR)/%.cpp,$(OBJ_DIR)/repositories/%.o,$(REPOSITORIES_SOURCES))
STRATEGIES_OBJECTS = $(patsubst $(STRATEGIES_DIR)/%.cpp,$(OBJ_DIR)/strategies/%.o,$(STRATEGIES_SOURCES))
MAIN_OBJECT = $(OBJ_DIR)/main.o

ALL_OBJECTS = $(DOMAIN_OBJECTS) $(SERVICES_OBJECTS) $(FACTORIES_OBJECTS) \
              $(REPOSITORIES_OBJECTS) $(STRATEGIES_OBJECTS) $(MAIN_OBJECT)

# Правила по умолчанию
.PHONY: all clean run debug help rebuild distclean info valgrind gdb directories

# Основная цель
all: directories $(TARGET)
	@echo "Build successful!  Run with:  make run"

# Цель отладки
debug:  CXXFLAGS += $(DEBUG_FLAGS)
debug: directories $(TARGET_DEBUG)
	@echo "Debug build successful! Run with: make run-debug"

# Создание директорий
directories: 
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)/domain
	@mkdir -p $(OBJ_DIR)/services
	@mkdir -p $(OBJ_DIR)/factories
	@mkdir -p $(OBJ_DIR)/repositories
	@mkdir -p $(OBJ_DIR)/strategies

# Сборка основного исполняемого файла
$(TARGET): $(ALL_OBJECTS)
	@echo "Linking:  $@"
	@$(CXX) $(CXXFLAGS) $(INCLUDE_PATH) -o $@ $^
	@echo "Executable:  $@"

# Сборка отладочного исполняемого файла
$(TARGET_DEBUG): $(ALL_OBJECTS)
	@echo "Linking (Debug): $@"
	@$(CXX) $(CXXFLAGS) $(INCLUDE_PATH) -o $@ $^
	@echo "Debug executable: $@"

# Правила компиляции для domain
$(OBJ_DIR)/domain/%.o: $(DOMAIN_DIR)/%.cpp
	@echo "Compiling: $<"
	@$(CXX) $(CXXFLAGS) $(INCLUDE_PATH) -c $< -o $@

# Правила компиляции для services
$(OBJ_DIR)/services/%.o: $(SERVICES_DIR)/%.cpp
	@echo "Compiling: $<"
	@$(CXX) $(CXXFLAGS) $(INCLUDE_PATH) -c $< -o $@

# Правила компиляции для factories
$(OBJ_DIR)/factories/%.o: $(FACTORIES_DIR)/%.cpp
	@echo "Compiling: $<"
	@$(CXX) $(CXXFLAGS) $(INCLUDE_PATH) -c $< -o $@

# Правила компиляции для repositories
$(OBJ_DIR)/repositories/%.o: $(REPOSITORIES_DIR)/%.cpp
	@echo "Compiling: $<"
	@$(CXX) $(CXXFLAGS) $(INCLUDE_PATH) -c $< -o $@

# Правила компиляции для strategies
$(OBJ_DIR)/strategies/%.o: $(STRATEGIES_DIR)/%.cpp
	@echo "Compiling: $<"
	@$(CXX) $(CXXFLAGS) $(INCLUDE_PATH) -c $< -o $@

# Правило компиляции для main. cpp
$(OBJ_DIR)/main.o: $(MAIN_SOURCE)
	@echo "Compiling: $<"
	@$(CXX) $(CXXFLAGS) $(INCLUDE_PATH) -c $< -o $@

# Очистка сборки
clean:
	@echo "Cleaning up..."
	@rm -rf $(OBJ_DIR)
	@rm -rf $(BIN_DIR)
	@echo "Clean complete"

# Запуск программы
run: all
	@echo "Running program..."
	@./$(TARGET)

# Запуск отладочной версии
run-debug:  debug
	@echo "Running debug version..."
	@./$(TARGET_DEBUG)

# Запуск с valgrind (проверка памяти)
valgrind: debug
	@echo "Running with Valgrind (memory check)..."
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
	          --verbose ./$(TARGET_DEBUG) 2>&1 | tee valgrind_report.txt
	@echo "Report saved to valgrind_report.txt"

# Запуск с gdb (отладчик)
gdb: debug
	@echo "Running with GDB..."
	@gdb ./$(TARGET_DEBUG)

# Информация о сборке
info:
	@echo "===================================================="
	@echo "   Grade Management System - Build Information"
	@echo "===================================================="
	@echo "Compiler: $(CXX)"
	@echo "Flags: $(CXXFLAGS)"
	@echo "Include:  $(INCLUDE_PATH)"
	@echo "Target: $(TARGET)"
	@echo "Domain objects: $(DOMAIN_OBJECTS)"
	@echo "Services objects: $(SERVICES_OBJECTS)"
	@echo "Factories objects: $(FACTORIES_OBJECTS)"
	@echo "Repositories objects: $(REPOSITORIES_OBJECTS)"
	@echo "Strategies objects: $(STRATEGIES_OBJECTS)"
	@echo "===================================================="

# Переиндексация (удалить всё и пересобрать)
rebuild: clean all
	@echo "Full rebuild complete"

# Полная очистка (включая отчёты)
distclean: clean
	@echo "Deep cleaning..."
	@rm -f valgrind_report.txt
	@rm -f gmon.out
	@echo "Distclean complete"

# Просмотр справки
help:
	@echo "===================================================="
	@echo "   Grade Management System - Makefile Help"
	@echo "===================================================="
	@echo "Available targets:"
	@echo ""
	@echo "  make all           - Build the project (default)"
	@echo "  make debug         - Build with debug symbols"
	@echo "  make run           - Build and run the program"
	@echo "  make run-debug     - Build and run debug version"
	@echo "  make clean         - Remove object and binary files"
	@echo "  make distclean     - Deep clean (remove all generated files)"
	@echo "  make rebuild       - Clean and rebuild from scratch"
	@echo "  make valgrind      - Run with Valgrind (memory check)"
	@echo "  make gdb           - Run with GDB debugger"
	@echo "  make info          - Show build information"
	@echo "  make help          - Show this help message"
	@echo ""
	@echo "Examples:"
	@echo "  make              # Build release version"
	@echo "  make run          # Build and run"
	@echo "  make debug        # Build debug version"
	@echo "  make valgrind     # Check for memory leaks"
	@echo "===================================================="