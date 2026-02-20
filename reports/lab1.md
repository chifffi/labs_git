Лабораторная работа №1. Базовая работа с git

Ход работы:

1. Установка и настройка
	1.1 Приложение git было скачано с оффициального сайта https://git-scm.com/

	1.2 Проверка версии была сделана с помощью команды git --version: 
	$ git version 2.53.0.windows.1

	1.3 Имя и адрес были указаны с помощью git config:
	$ git config --global user.name "Dasha"
	$ git config --global user.email difilatova070907@gmail.com

	1.4 Вывод справки $ git --heip
	usage: git [-v | --version] [-h | --help] [-C <path>] [-c <name>=<value>]
           [--exec-path[=<path>]] [--html-path] [--man-path] [--info-path]
           [-p | --paginate | -P | --no-pager] [--no-replace-objects] [--no-lazy-fetch]
           [--no-optional-locks] [--no-advice] [--bare] [--git-dir=<path>]
           [--work-tree=<path>] [--namespace=<name>] [--config-env=<name>=<envvar>]
           <command> [<args>]

	These are common Git commands used in various situations:

	start a working area (see also: git help tutorial)
	   clone      Clone a repository into a new directory
	   init       Create an empty Git repository or reinitialize an existing one

	work on the current change (see also: git help everyday)
	   add        Add file contents to the index
	   mv         Move or rename a file, a directory, or a symlink
	   restore    Restore working tree files
	   rm         Remove files from the working tree and from the index

	examine the history and state (see also: git help revisions)
	   bisect     Use binary search to find the commit that introduced a bug
	   diff       Show changes between commits, commit and working tree, etc
	   grep       Print lines matching a pattern
	   log        Show commit logs
	   show       Show various types of objects
	   status     Show the working tree status

	grow, mark and tweak your common history
	   backfill   Download missing objects in a partial clone
	   branch     List, create, or delete branches
	   commit     Record changes to the repository
	   merge      Join two or more development histories together
	   rebase     Reapply commits on top of another base tip
	   reset      Set `HEAD` or the index to a known state
	   switch     Switch branches
	   tag        Create, list, delete or verify tags

	collaborate (see also: git help workflows)
	   fetch      Download objects and refs from another repository
	   pull       Fetch from and integrate with another repository or a local branch
	   push       Update remote refs along with associated objects

	'git help -a' and 'git help -g' list available subcommands and some
	concept guides. See 'git help <command>' or 'git help <concept>'
	to read about a specific subcommand or concept.
	See 'git help git' for an overview of the system.


2. Начало работы с новым проектом
	2.1 С помощью команды mkdir в текущей рабочей директории /c/Users/difil/ была создана папка git_labs:
	mkdir git_labs

	2.2 Через проводник были созданы файл README.md, каталог reports и файл reports/lab1.md

	2.3 С помощью команды cd был совершен переход в папку git_labs:
	$ cd git_labs

	2.4 С помощью команды git init папка git_labs стала репозиторием, появилась подпапка .git, в которой хранится всё, что нужно git для работы: 
	$ git init 

	2.5 В файл README.md были записаны информация о дисциплине и обо мне

	2.6 С помощью команды git add были добавлены изменения в индекс (staging area) для будущего коммита:
	$ git add README.md

	2.7 С помощью команды git commit был создан коммит с файлами README.md и reports/lab1.md:
	$ git commit  
	после этого открылся WIM, где было вписано название коммита "Initial commit"

3. Отслеживание состояния кода
	3.1.1 Команда git status показывает, на какой ветке сейчас находится человек и какие файлы были изменены, добавлены или удалены в текущем репозитории:
	$ git status
	On branch master - находимся на ветке master
	nothing to commit, working tree clean - сообщение о том, что коммиты не требуются, так как все сохранено

	3.1.2 Команда git diff даёт возможность увидеть все изменения, проверить их на ошибки и удостовериться, что в коммит включён только необходимый код
	$ git diff
	diff --git a/README.md b/README.md
	index 08339ad..af4a8a2 100644
	--- a/README.md
	+++ b/README.md
	@@ -1,5 +1,6 @@
	+##Лабораторные работы по Современным технологиям разработки ПО
	+
	+Студент: Филатова Дарья, группа 5130201/50302

	 Тут располагаются работы по дисциплине "Современные технологии разработки ПО"

	3.2 В файл reports/lab1.md были внесены заметки по этапам работы

	3.3 Были выполнены команды git status и git diff: 
	1) $ git status
		On branch main
		Changes not staged for commit:
		  (use "git add <file>..." to update what will be committed)
		  (use "git restore <file>..." to discard changes in working directory)
		        modified:   reports/lab1.md

		no changes added to commit (use "git add" and/or "git commit -a")
		Вывод команды предупреждает о том, что изменения в файле reports/lab1.md не подготовлены к коммиту, необходимо выполнить команду $git add

	2) $ git diff
		diff --git a/README.md b/README.md
		index 08339ad..af4a8a2 100644
		--- a/README.md
		+++ b/README.md
		@@ -1,5 +1,6 @@
		+##Лабораторные работы по Современным технологиям разработки ПО
		+
		+Студент: Филатова Дарья, группа 5130201/50302

		 Тут располагаются работы по дисциплине "Современные технологии разработки ПО"

		diff --git a/reports/lab1.md b/reports/lab1.md
		index c4299ea..8d7bdce 100644
		--- a/reports/lab1.md
		+++ b/reports/lab1.md
		@@ -1,13 +1,74 @@
		-Лабораторная работа 1
		+Лабораторная работа №1. Базовая работа с git

		 Ход работы:

		-1. Установка программы
		-2. Проверка версии git --version
		-3. Вывод справки git --heip
		-4. делаю лабу
		+1. Установка и настройка
		+       1.1 Приложение git было скачано с оффициального сайта https://git-scm.com/

		-Создание папки и репозитория
		-mkdir
		-cd
		-git init
		Вывод команды показывает, какие строки были изменены в обоих файлах

	3.4 С помощью команды $ git add . были внесены изменения в файлах в индекс без создания коммита. Вывод команды $ git status показывает, что все файлы готовы к коммиту
	$ git add .
	difil@ MINGW64 ~/git_labs (main)
	$ git status
	On branch main
	Changes to be committed:
	  (use "git restore --staged <file>..." to unstage)
	        modified:   README.md
	        modified:   reports/lab1.md

	3.5 После того, как в файл README.md были внесены изменения, была выполнена команда git diff README.md, которая показала удаленную и дбавленную строки: 
	$ git diff README.md
	diff --git a/README.md b/README.md
	index a12790b..2bcd455 100644
	--- a/README.md
	+++ b/README.md
	@@ -3,5 +3,4 @@
	 Студент: Филатова Дарья, группа 5130201/50302

	 Тут располагаются работы по дисциплине "Современные технологии разработки ПО"
	-
	-щовщывщрв
	\ No newline at end of file
	+активно делаю лабораторную
	\ No newline at end of file

	3.6 С помощью команды git add были зафиксированы изменения в файле reports/lab1.md:
	$ git add reports/lab1.md. 
	С помощью команды git commit был создан коммит с изменениями файла reports/lab1.md:
	$ git commit reports/lab1.md -m "Заполнение отчета по лабораторной работе 1"

4. Откат изменений
	4.1 С помощью команды git restore получилось сделать откат изменений в файле README.md: несохраненные изменения пропали

	4.2 После удаления файла reports/lab1.md была выполнена команда git status, которая показала, что файл не готов к коммиту, так как был удален:
	$ git status
	On branch main
	Changes not staged for commit:
	  (use "git add/rm <file>..." to update what will be committed)
	  (use "git restore <file>..." to discard changes in working directory)
	        deleted:    reports/lab1.md

	4.3 С помощью команды git restore файл reports/lab1.md был восстановлен:
	reports/lab1.md

5. Ветвление версий
	5.1 С помощью команды git branch можно создавать, просматривать, переименовывать и удалять ветки:
	$ git branch
	* main

	5.2 Была создана новая ветка lab1, с помощью команды git checkout мы переключились на нее:
	$ git branch 
	$ git checkout lab1

	5.3 В отчет был внесен протокол последних этапов работы, далее был сделан коммит в ветке lab1:
	$ git add .
	$ git commit -m "Коммит в ветке lab1"

	5.4 Переключившись на ветку main, файл отчета вернулся к состоянию, которое было до создания коммита в ветке lab1: изменения, закоммиченные в ветке lab1, не видны в исходной ветке

	5.5 Файл README.md был изменен, но не закоммичен. При попытке переключиться на ветку lab1 возникла ошибка: нельзя переключиться на другую ветку, не сохранив изменения на текущей
	$ git checkout lab1
	error: Your local changes to the following files would be overwritten by checkout:
	        README.md
	Please commit your changes or stash them before you switch branches.
	Aborting

6. Слияние веток, конфликты
	6.1 С помощью команды git merge lab1 произошло слияние ветки main с lab1:
	$ git merge lab1

	6.2 в ветке main был изменен заголовок файла README.md, далее был сделан коммит

	6.3 После переключения на ветку lab1, в файл отчета была добавлена новая часть, изменен заголовок файла README.md и добавлена информация в конце 

	6.4 Изменения были закоммичены. При попытке слить ветку lab1 с веткой main, произошел конфликт: один и тот же заголовок в двух ветках выглядит по разному, git не может выбрать правильный вариант:
	$ git merge main
	Auto-merging README.md
	CONFLICT (content): Merge conflict in README.md
	Automatic merge failed; fix conflicts and then commit the result.

	6.5 Содержимое файла README.md:
	<<<<<<< HEAD
	####Лабораторные работы по Современным технологиям программирования
	Выполнила: Филатова Дарья 5130201/50302 

	Тут располагаются работы по дисциплине "Современные технологии разработки ПО"



	Здесь будет информация о следующих лабораторных
	=======
	Лабораторные работы по Современным технологиям разработки ПО

	Студент: Филатова Дарья, группа 5130201/50302 

	Тут располагаются работы по дисциплине "Современные технологии разработки ПО"

	1. Лабораторная работа №1. Базовая работа с git
	>>>>>>> main

	Чтобы разрешить конфликт, необходимо самим принять решение, удалить ненужный вариант и потом сделать коммит:
	difil@ MINGW64 ~/git_labs (lab1|MERGING)
	$ git add .

	difil@ MINGW64 ~/git_labs (lab1|MERGING)
	$ git commit -m "Разрешение конфликта при слиянии"
	[lab1 e7b35dd] Разрешение конфликта при слиянии

	difil@ MINGW64 ~/git_labs (lab1)
	$ git merge main

	6.6 Ветка lab1 была удалена с помощью команды git branch -d lab1
	$ git branch -d lab1
	Deleted branch lab1 (was f8332cf).

7. Работа с удаленным репозиторием
	7.1 Был создан аккаунт на Github 

	7.2 С помощью команды ssh-keygen был сконфигурирован SSH ключ

	7.3 Был создан приватный репозиторий

	7.4 С помощью коанды git remote add этот репозиторий был добавлен в качестве удаленного для  локального репозитория:
	$ git remote add origin git@github.com:chifffi/labs_git.git  

	7.5 С помощью команды git push были отправлены данные из локального репозитория в удаленный: 
	$ git push -u origin main

8. Синхронизация с удаленным репозиторием
	8.1 С поомщью комнады mkdir была создана новая папка temp:
	$ cd ../
	$ cd temp/

	8.2 c помощью команды git clone было произведено клонирование удаленного репозитория в папку temp:
	$ git clone git@github.com:chifffi/labs_git.git

	8.3 Во временном репозитории была добавлена информация о лабораторной работе, после чего изменения были закоммичены