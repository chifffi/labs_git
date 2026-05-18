# Список объектных файлов - результат компиляции
OBJECTS = build/mystring.o build/matrix.o build/workerdb.o build/notification.o \
          build/notification_queue.o build/notification_priority_queue.o \
          build/boolarray.o build/basefile.o

# основная программа
build/lab3.out: $(OBJECTS) src/lab3.cpp
	g++ -g -o build/lab3.out src/lab3.cpp $(OBJECTS)

# запуск основной программы
run: build/lab3.out
	./build/lab3.out

# проверка утечки памяти
build/leaks.out: src/lab3.cpp src/mystring.cpp src/matrix.cpp src/workerdb.cpp \
                 src/notification.cpp src/notification_queue.cpp \
                 src/notification_priority_queue.cpp src/boolarray.cpp src/basefile.cpp
	g++ -g -fsanitize=address -o build/leaks.out src/lab3.cpp \
		src/mystring.cpp src/matrix.cpp src/workerdb.cpp \
		src/notification.cpp src/notification_queue.cpp \
		src/notification_priority_queue.cpp src/boolarray.cpp src/basefile.cpp

# запуск проверки утечек
leaks: build/leaks.out
	./build/leaks.out

# Компиляция о. файлов
build/mystring.o: src/mystring.cpp src/mystring.hpp
	g++ -g -c -o build/mystring.o src/mystring.cpp

build/matrix.o: src/matrix.cpp src/matrix.hpp
	g++ -g -c -o build/matrix.o src/matrix.cpp

build/workerdb.o: src/workerdb.cpp src/workerdb.hpp src/mystring.hpp
	g++ -g -c -o build/workerdb.o src/workerdb.cpp

build/notification.o: src/notification.cpp src/notification.hpp src/mystring.hpp
	g++ -g -c -o build/notification.o src/notification.cpp

build/notification_queue.o: src/notification_queue.cpp src/notification_queue.hpp src/notification.hpp
	g++ -g -c -o build/notification_queue.o src/notification_queue.cpp

build/notification_priority_queue.o: src/notification_priority_queue.cpp src/notification_priority_queue.hpp src/notification.hpp
	g++ -g -c -o build/notification_priority_queue.o src/notification_priority_queue.cpp

build/boolarray.o: src/boolarray.cpp src/boolarray.hpp
	g++ -g -c -o build/boolarray.o src/boolarray.cpp

build/basefile.o: src/basefile.cpp src/basefile.hpp src/ifile.hpp
	g++ -g -c -o build/basefile.o src/basefile.cpp


# очистка выходных файлов
clean:
	-rm -f build/*.o build/*.out

# цель по умолчанию
all: build/lab3.out

# очистка и пересборка
rebuild: clean all

# компиляция и запуск
go: all run

.PHONY: run leaks clean rebuild go all