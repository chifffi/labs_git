# Список объектных файлов - результат компиляций
OBJECTS = build/mystring.o build/basefile.o build/base32file.o build/rlefile.o build/base32file2.o build/rlefile2.o

# основная программа
build/lab2.out: $(OBJECTS) src/lab2.cpp
	g++ -g -o build/lab2.out src/lab2.cpp $(OBJECTS)

# запуск основной прграммы
run: build/lab2.out
	./build/lab2.out

# проверка утечки памяти
build/leaks.out: src/lab2.cpp src/mystring.cpp src/basefile.cpp src/base32file.cpp src/rlefile.cpp src/base32file2.cpp src/rlefile2.cpp
	g++ -g -fsanitize=address -o build/leaks.out src/lab2.cpp src/mystring.cpp src/basefile.cpp src/base32file.cpp src/rlefile.cpp src/base32file2.cpp src/rlefile2.cpp

# запуск проверки утечек
leaks: build/leaks.out
	./build/leaks.out
# тесты
# Каждый тест — отдельный исполняемый файл
build/test_basefile.out: tests/test_basefile.cpp $(OBJECTS)
	g++ -g -o build/test_basefile.out tests/test_basefile.cpp $(OBJECTS)

build/test_base32file.out: tests/test_base32file.cpp $(OBJECTS)
	g++ -g -o build/test_base32file.out tests/test_base32file.cpp $(OBJECTS)

build/test_rlefile.out: tests/test_rlefile.cpp $(OBJECTS)
	g++ -g -o build/test_rlefile.out tests/test_rlefile.cpp $(OBJECTS)

build/test_base32file2.out: tests/test_base32file2.cpp $(OBJECTS)
	g++ -g -o build/test_base32file2.out tests/test_base32file2.cpp $(OBJECTS)

build/test_rlefile2.out: tests/test_rlefile2.cpp $(OBJECTS)
	g++ -g -o build/test_rlefile2.out tests/test_rlefile2.cpp $(OBJECTS)


build/test_composition.out: tests/test_composition.cpp $(OBJECTS)
	g++ -g -o build/test_composition.out tests/test_composition.cpp $(OBJECTS)

# запуск тестов
test: build/test_basefile.out build/test_base32file.out build/test_rlefile.out \
      build/test_base32file2.out build/test_rlefile2.out build/test_composition.out
	@echo "========================================"
	@echo "          ЗАПУСК ТЕСТОВ"
	@echo "========================================"
	@echo ""
	@echo "--- Тест BaseFile ---"
	@./build/test_basefile.out
	@echo ""
	@echo "--- Тест Base32File ---"
	@./build/test_base32file.out
	@echo ""
	@echo "--- Тест RleFile ---"
	@./build/test_rlefile.out
	@echo ""
	@echo "--- Тест Base32File2 (композиция) ---"
	@./build/test_base32file2.out
	@echo ""
	@echo "--- Тест RleFile2 (композиция) ---"
	@./build/test_rlefile2.out
	@echo ""
	@echo "--- Тест композиции RleFile2+Base32File2 ---"
	@./build/test_composition.out
	@echo ""
	@echo "========================================"
	@echo "           ПРОВЕРКА ТЕСТОВ ЗАКОНЧЕНА"
	@echo "========================================"

# компиляция о. файлов
build/mystring.o: src/mystring.cpp src/mystring.hpp
	g++ -g -c -o build/mystring.o src/mystring.cpp

build/basefile.o: src/basefile.cpp src/basefile.hpp src/ifile.hpp
	g++ -g -c -o build/basefile.o src/basefile.cpp

build/base32file.o: src/base32file.cpp src/base32file.hpp src/basefile.hpp
	g++ -g -c -o build/base32file.o src/base32file.cpp

build/rlefile.o: src/rlefile.cpp src/rlefile.hpp src/basefile.hpp
	g++ -g -c -o build/rlefile.o src/rlefile.cpp

build/base32file2.o: src/base32file2.cpp src/base32file2.hpp src/ifile.hpp
	g++ -g -c -o build/base32file2.o src/base32file2.cpp

build/rlefile2.o: src/rlefile2.cpp src/rlefile2.hpp src/ifile.hpp
	g++ -g -c -o build/rlefile2.o src/rlefile2.cpp


.PHONY: test run clean clean-data clean-all  all

# очистка выходных объектных 
clean:
	-rm -f build/*.o build/*.out

# очистка тестовых данных
clean-data:
	-rm -f data/*

# полная очистка
clean-all: clean clean-data

# цель по умолчанию
all: build/lab2.out
