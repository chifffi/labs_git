# Список объектных файлов - результат компиляции основных классов
OBJECTS = build/point.o build/circle.o build/list.o

# Тесты
# Каждый тест — отдельный исполняемый файл
build/test_empty.out: tests/test_empty.cpp $(OBJECTS)
	g++ -g -I./src -o build/test_empty.out tests/test_empty.cpp $(OBJECTS)

build/test_add.out: tests/test_add.cpp $(OBJECTS)
	g++ -g -I./src -o build/test_add.out tests/test_add.cpp $(OBJECTS)

build/test_remove.out: tests/test_remove.cpp $(OBJECTS)
	g++ -g -I./src -o build/test_remove.out tests/test_remove.cpp $(OBJECTS)

build/test_index.out: tests/test_index.cpp $(OBJECTS)
	g++ -g -I./src -o build/test_index.out tests/test_index.cpp $(OBJECTS)

build/test_sort.out: tests/test_sort.cpp $(OBJECTS)
	g++ -g -I./src -o build/test_sort.out tests/test_sort.cpp $(OBJECTS)

build/test_copy.out: tests/test_copy.cpp $(OBJECTS)
	g++ -g -I./src -o build/test_copy.out tests/test_copy.cpp $(OBJECTS)

build/test_file.out: tests/test_file.cpp $(OBJECTS)
	g++ -g -I./src -o build/test_file.out tests/test_file.cpp $(OBJECTS)

build/test_clear.out: tests/test_clear.cpp $(OBJECTS)
	g++ -g -I./src -o build/test_clear.out tests/test_clear.cpp $(OBJECTS)

build/test_contains.out: tests/test_contains.cpp $(OBJECTS)
	g++ -g -I./src -o build/test_contains.out tests/test_contains.cpp $(OBJECTS)

# Запуск тестов
test: build/test_empty.out build/test_add.out build/test_remove.out \
      build/test_index.out build/test_sort.out build/test_copy.out \
      build/test_file.out build/test_clear.out build/test_contains.out
	@echo "-----------------------------------------"
	@echo "            Запуск тестов"
	@echo "-----------------------------------------"
	@echo ""
	@echo " Тест 1: Пустой список "
	@./build/test_empty.out
	@echo ""
	@echo " Тест 2: Добавление элементов "
	@./build/test_add.out
	@echo ""
	@echo " Тест 3: Удаление элементов "
	@./build/test_remove.out
	@echo ""
	@echo " Тест 4: Оператор индексирования "
	@./build/test_index.out
	@echo ""
	@echo " Тест 5: Сортировка "
	@./build/test_sort.out
	@echo ""
	@echo " Тест 6: Копирование и присваивание "
	@./build/test_copy.out
	@echo ""
	@echo " Тест 7: Файловый ввод/вывод "
	@./build/test_file.out
	@echo ""
	@echo " Тест 8: Очистка списка "
	@./build/test_clear.out
	@echo ""
	@echo " Тест 9: Поиск элемента "
	@./build/test_contains.out
	@echo ""
	@echo "-----------------------------------------"
	@echo "       Запуск тестов закончен"
	@echo "-----------------------------------------"

# Проверка утечек памяти
build/test_empty_leaks.out: tests/test_empty.cpp $(OBJECTS)
	g++ -g -fsanitize=address -I./src -o build/test_empty_leaks.out tests/test_empty.cpp $(OBJECTS)

build/test_add_leaks.out: tests/test_add.cpp $(OBJECTS)
	g++ -g -fsanitize=address -I./src -o build/test_add_leaks.out tests/test_add.cpp $(OBJECTS)

build/test_remove_leaks.out: tests/test_remove.cpp $(OBJECTS)
	g++ -g -fsanitize=address -I./src -o build/test_remove_leaks.out tests/test_remove.cpp $(OBJECTS)

build/test_index_leaks.out: tests/test_index.cpp $(OBJECTS)
	g++ -g -fsanitize=address -I./src -o build/test_index_leaks.out tests/test_index.cpp $(OBJECTS)

build/test_sort_leaks.out: tests/test_sort.cpp $(OBJECTS)
	g++ -g -fsanitize=address -I./src -o build/test_sort_leaks.out tests/test_sort.cpp $(OBJECTS)

build/test_copy_leaks.out: tests/test_copy.cpp $(OBJECTS)
	g++ -g -fsanitize=address -I./src -o build/test_copy_leaks.out tests/test_copy.cpp $(OBJECTS)

build/test_file_leaks.out: tests/test_file.cpp $(OBJECTS)
	g++ -g -fsanitize=address -I./src -o build/test_file_leaks.out tests/test_file.cpp $(OBJECTS)

build/test_clear_leaks.out: tests/test_clear.cpp $(OBJECTS)
	g++ -g -fsanitize=address -I./src -o build/test_clear_leaks.out tests/test_clear.cpp $(OBJECTS)

build/test_contains_leaks.out: tests/test_contains.cpp $(OBJECTS)
	g++ -g -fsanitize=address -I./src -o build/test_contains_leaks.out tests/test_contains.cpp $(OBJECTS)

# запуск проверки утечек
leaks-test: build/test_empty_leaks.out build/test_add_leaks.out \
            build/test_remove_leaks.out build/test_index_leaks.out \
            build/test_sort_leaks.out build/test_copy_leaks.out \
            build/test_file_leaks.out build/test_clear_leaks.out \
            build/test_contains_leaks.out
	@echo "========================================"
	@echo "     Проверка утечек памяти в тестах"
	@echo "========================================"
	@echo ""
	@echo " Тест 1: Пустой список "
	@./build/test_empty_leaks.out
	@echo ""
	@echo " Тест 2: Добавление элементов "
	@./build/test_add_leaks.out
	@echo ""
	@echo " Тест 3: Удаление элементов "
	@./build/test_remove_leaks.out
	@echo ""
	@echo " Тест 4: Оператор индексирования "
	@./build/test_index_leaks.out
	@echo ""
	@echo " Тест 5: Сортировка "
	@./build/test_sort_leaks.out
	@echo ""
	@echo " Тест 6: Копирование и присваивание "
	@./build/test_copy_leaks.out
	@echo ""
	@echo " Тест 7: Файловый ввод/вывод "
	@./build/test_file_leaks.out
	@echo ""
	@echo " Тест 8: Очистка списка "
	@./build/test_clear_leaks.out
	@echo ""
	@echo " Тест 9: Поиск элемента "
	@./build/test_contains_leaks.out
	@echo ""
	@echo "-----------------------------------------"
	@echo "     Проверка утечек завершена"
	@echo "-----------------------------------------"

# Компиляция объектных файлов
build/point.o: src/point.cpp src/point.hpp
	g++ -g -c -o build/point.o src/point.cpp

build/circle.o: src/circle.cpp src/circle.hpp src/point.hpp
	g++ -g -c -o build/circle.o src/circle.cpp

build/list.o: src/list.cpp src/list.hpp src/circle.hpp
	g++ -g -c -o build/list.o src/list.cpp

# очистка 
clean:
	-rm -f build/*.o build/*.out
	-rm -f test_circles.txt

# цель по умолчанию
all: test

.PHONY: test leaks-test clean clean-all all