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
	
	8.3 Во временном репозитории была добавлена информация о лабораторной работе, после чего изменения были закоммичены:
	$ git add .
	$ git commit -m "сохранение во временной папке"
	
	8.4 Изменения были отправлены в удаленный репозиторий с помощью команды git push:
	$ git push -u origin main

	8.5 Вернувшись в первый локальный репозиторий, с помощью команды git fetch был совершен запрос обновлений из удаленного репозитория:
	$ cd git_labs
	$ git fetch
	remote: Enumerating objects: 7, done.
	remote: Counting objects: 100% (7/7), done.
	remote: Compressing objects: 100% (2/2), done.
	remote: Total 4 (delta 1), reused 4 (delta 1), pack-reused 0 (from 0)
	Unpacking objects: 100% (4/4), 641 bytes | 14.00 KiB/s, done.
	From github.com:chifffi/labs_git
	   97e285a..df6d26a  main       -> origin/main 

	8.6 Содержимое репозитория было синхронизировано командой git pull

9. История изменений
	commit 2496179d66ade9555acd2a349406b7dbe06dc304 (HEAD -> main)
	Merge: fa1c6bb df6d26a
	Author: Dasha <difilatova070907@gmail.com>
	Date:   Fri Feb 20 17:08:00 2026 +0300

	    синхронизация содержимого

	commit df6d26a66419a37d454c04b5266ca48a7d659df5 (origin/main, origin/HEAD)
	Author: Dasha <difilatova070907@gmail.com>
	Date:   Fri Feb 20 16:55:09 2026 +0300

	    сохранение во временной папке

	commit fa1c6bbc1ff41ab99c89283cc43d0cac7877e089
	Author: Dasha <difilatova070907@gmail.com>
	Date:   Fri Feb 20 16:48:10 2026 +0300

	    .

	commit 97e285a4e2cc7fba21f65fbe7bff2e506435b7fe (origin/2-branch)
	Author: chifffi <difilatova070907@gmail.com>
	Date:   Fri Feb 20 16:12:30 2026 +0300

	:...skipping...
	commit 2496179d66ade9555acd2a349406b7dbe06dc304 (HEAD -> main)
	Merge: fa1c6bb df6d26a
	Author: Dasha <difilatova070907@gmail.com>
	Date:   Fri Feb 20 17:08:00 2026 +0300

	    синхронизация содержимого

	commit df6d26a66419a37d454c04b5266ca48a7d659df5 (origin/main, origin/HEAD)
	Author: Dasha <difilatova070907@gmail.com>
	Date:   Fri Feb 20 16:55:09 2026 +0300

	    сохранение во временной папке

	commit fa1c6bbc1ff41ab99c89283cc43d0cac7877e089
	Author: Dasha <difilatova070907@gmail.com>
	Date:   Fri Feb 20 16:48:10 2026 +0300

	    .

	commit 97e285a4e2cc7fba21f65fbe7bff2e506435b7fe (origin/2-branch)
	Author: chifffi <difilatova070907@gmail.com>
	Date:   Fri Feb 20 16:12:30 2026 +0300

	    Внесение изменений с удаленного репозитория

	commit 18ec48a2c4fc19b8a9288452fc420c29a4976a4a
	Author: Dasha <difilatova070907@gmail.com>
	Date:   Thu Feb 19 19:19:42 2026 +0300

	    Работа с удаленным репозиторием

	commit f8332cfaa37366af45eafecb4621d1a995965cbd
	Author: Dasha <difilatova070907@gmail.com>
	Date:   Thu Feb 19 19:01:38 2026 +0300

	    Сохранение

	commit e7b35dd016ea63b32057eb048897bf3ecf065365
	Merge: 7fde33f 32d3ab4
	Author: Dasha <difilatova070907@gmail.com>
	Date:   Thu Feb 19 18:56:53 2026 +0300

	    Разрешение конфликта при слиянии

	commit 7fde33f7014822548b971628056ada2cd5c60ef1
	Author: Dasha <difilatova070907@gmail.com>
	Date:   Thu Feb 19 18:44:27 2026 +0300

	    Изменения в lab1 ветке

	commit 32d3ab4272440cb78b92601d3b90f5eeaf72afd4
	Author: Dasha <difilatova070907@gmail.com>
	Date:   Thu Feb 19 18:42:32 2026 +0300

	    В файл README изменен заголовок

	commit f406a6082ea7fa8900335ccda664c4b30b87a82a
	Author: Dasha <difilatova070907@gmail.com>
	Date:   Thu Feb 19 18:40:04 2026 +0300

	    В файл README добавлена информация о 1 лабораторной работе

	commit f1004f6f29f2d22121d963754b29db13ea9e9d0d
	Merge: 17f8286 caae380
	Author: Dasha <difilatova070907@gmail.com>
	Date:   Thu Feb 19 18:34:18 2026 +0300

	    Исправление конфликта

	commit 17f828661f02ab0c07e541eeaa84e12d59edb8e1
	Author: Dasha <difilatova070907@gmail.com>
	Date:   Thu Feb 19 18:31:09 2026 +0300

	    Добавление информации в отчет

	commit caae380b29fe377674ded0f8e5069af906b7a392
	Author: Dasha <difilatova070907@gmail.com>
	Date:   Thu Feb 19 17:57:48 2026 +0300

	    Коммит в ветке lab1

	commit 1b13ba9e20e037d96aeea4568e1e7e65b078d7ba
	Author: Dasha <difilatova070907@gmail.com>
	Date:   Thu Feb 19 17:55:47 2026 +0300

	    Перед переходом на другую ветку

	commit 19305fa74eb1b64dc7f2d0c5d5a4ee09716936ef
	Author: Dasha <difilatova070907@gmail.com>
	Date:   Thu Feb 19 00:14:58 2026 +0300

	    Внесение протокола последних этапов работы

	commit 6b2aa2ab10b7f467af8811c5183c8da3a4a43167
	Author: Dasha <difilatova070907@gmail.com>
	Date:   Wed Feb 18 23:55:33 2026 +0300

	    Перед удалением файла

	commit 65ba72f026db1807f6d53780748c27ba53e55704
	Author: Dasha <difilatova070907@gmail.com>
	Date:   Wed Feb 18 23:49:52 2026 +0300

	    Заполнение отчета по лабораторной работе 1

	commit ccad2ad9312db946793fe53216d5b20766561def
	Merge: fd0fe45 78ee034
	Author: Dasha <difilatova070907@gmail.com>
	Date:   Thu Feb 12 14:56:39 2026 +0300

	    итог после конфликта

	commit fd0fe4543b1837208d70ff65ff038c4d1d9d36c2
	Author: Dasha <difilatova070907@gmail.com>
	Date:   Thu Feb 12 14:46:12 2026 +0300

	    пепе

	commit 78ee0345151f62f5bfd6b20fa65858248540a070
	Author: Dasha <difilatova070907@gmail.com>
	Date:   Thu Feb 12 14:44:23 2026 +0300

	    долго но качественно

	commit adcb2bc1c7ac3bcdb57e17702573ae9a97bc0ce1
	Merge: 008351e 02e3877
	Author: Dasha <difilatova070907@gmail.com>
	Date:   Thu Feb 12 14:35:39 2026 +0300

	    Merge branch 'lab1'

	commit 008351e2eb74832d7187526096351730a1510d0b
	Author: Dasha <difilatova070907@gmail.com>
	Date:   Thu Feb 12 14:34:08 2026 +0300

	    Суть файла

	commit 02e38775f133ae9a4d7d3dca816cf62c1c73d344
	Author: Dasha <difilatova070907@gmail.com>
	Date:   Thu Feb 12 14:31:47 2026 +0300

	    Создание папки и репозитория

	commit d5213f3eff3b042bb6ec1f00dc56f900cafa1d73
	Author: Dasha <difilatova070907@gmail.com>
	Date:   Thu Feb 12 14:20:21 2026 +0300

	    продолжение лабораторной

	commit 08d3ca310e9c9c8cf3e42ae42ae9bba64af03d67
	Author: Dasha <difilatova070907@gmail.com>
	Date:   Wed Feb 11 22:42:17 2026 +0300

	    point 3

	commit a5ad0653fbc9571893b4c2230c00b067f6f9a100
	Author: Dasha <difilatova070907@gmail.com>
	Date:   Wed Feb 11 22:15:54 2026 +0300

	    Добавление номера группы и описание хода работы

	commit 96388376bf2f99bd08ededd258ef2aac2cdb40df
	Author: Dasha <difilatova070907@gmail.com>
	Date:   Wed Feb 11 21:55:24 2026 +0300

	    initial commit
