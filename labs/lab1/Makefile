OBJECTS = build/rect.o build/barrel.o build/matrix.o build/mystring.o build/textwrapper.o
build/debug.out: $(OBJECTS) src/lab1.cpp
	g++ -g -o build/debug.out src/lab1.cpp $(OBJECTS)

debug: build/debug.out #отладчик
	gdb build/debug.out

build/rect.o: src/rect.cpp src/rect.hpp
	g++ -g -c -o build/rect.o src/rect.cpp

build/barrel.o: src/barrel.cpp src/barrel.hpp
	g++ -g -c -o build/barrel.o src/barrel.cpp

build/matrix.o: src/matrix.cpp src/matrix.hpp
	g++ -g -c -o build/matrix.o src/matrix.cpp

build/mystring.o: src/mystring.cpp src/mystring.hpp
	g++ -g -c -o build/mystring.o src/mystring.cpp

build/textwrapper.o: src/textwrapper.cpp src/textwrapper.hpp src/mystring.hpp
	g++ -g -c -o build/textwrapper.o src/textwrapper.cpp


build/leaks.out: src/lab1.cpp src/rect.cpp src/barrel.cpp src/matrix.cpp src/mystring.cpp src/textwrapper.cpp
	g++ -g -fsanitize=address -o build/leaks.out src/lab1.cpp src/rect.cpp src/barrel.cpp src/matrix.cpp src/mystring.cpp src/textwrapper.cpp

leaks: build/leaks.out input.txt #проверка утечки
	./build/leaks.out < input.txt


build/test_rect_basic_methods.out: tests/test_rect_basic_methods.cpp src/rect.cpp src/rect.hpp
	g++ -g -o build/test_rect_basic_methods.out tests/test_rect_basic_methods.cpp src/rect.cpp

build/test_rect_properties.out: tests/test_rect_properties.cpp src/rect.cpp src/rect.hpp
	g++ -g -o build/test_rect_properties.out tests/test_rect_properties.cpp src/rect.cpp

build/test_rect_operations.out: tests/test_rect_operations.cpp src/rect.cpp src/rect.hpp
	g++ -g -o build/test_rect_operations.out tests/test_rect_operations.cpp src/rect.cpp

build/test_bounding_rect.out: tests/test_bounding_rect.cpp src/rect.cpp src/rect.hpp
	g++ -g -o build/test_bounding_rect.out tests/test_bounding_rect.cpp src/rect.cpp


test: build/test_rect_basic_methods.out build/test_rect_properties.out build/test_rect_operations.out build/test_bounding_rect.out
	@echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	@echo "                    Запуск тестов"
	@echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	@echo ""
	

	@./build/test_rect_basic_methods.out
	@echo ""
	

	@echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	@./build/test_rect_properties.out
	@echo ""
	
	@echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	@./build/test_rect_operations.out
	@echo ""
	
	@echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	@./build/test_bounding_rect.out
	@echo ""
	
	@echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	@echo "              Итог: все тесты пройдены успешно"
	@echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
#echo — выводит текст
#@ — скрывает саму команду, показывает только результат

.PHONY: clean
clean:
	-rm -f build/*.o build/*.out
#.PHONY: clean	значит что clean — это не файл, а просто название цели
#- перед rm	если файлов нет, не ругаться
#-f в rm не спрашивать подтверждения, удалять без вопросов