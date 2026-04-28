# Лабораторная работа №6. Простые CI-CD пайплайны

## Ход работы

## 1. Базовые хуки в Git на стороне клиента

### 1.1 Таблица хуков Git: операция, хук, что делает и когда, может ли прервать

| Операция Git | Хук | Когда срабатывает | Что делает | Может ли прервать операцию |
|--------------|-----|-------------------|------------|---------------------------|
| **git commit** | **pre-commit** | Перед созданием коммита, после git add | Проверяет код, файлы, которые попадут в коммит (например, ищет токены, пароли) | Да |
| **git commit** | **prepare-commit-msg** | Перед открытием редактора сообщения коммита | Редактирует шаблон сообщения коммита | Нет |
| **git commit** | **commit-msg** | После ввода сообщения коммита, перед фиксацией | Проверяет сообщение коммита (длина, формат, наличие номера задачи) | Да |
| **git commit** | **post-commit** | После успешного создания коммита | Уведомления, логирование, автоформатирование | Нет |
| **git push** | **pre-push** | Перед отправкой данных на удалённый репозиторий | Проверяет коммиты перед отправкой | Да |
| **git merge** | **post-merge** | После успешного выполнения слияния | Пересборка проекта, уведомления | Нет |

### 1.2 Хук pre-commit – проверка кода на запрещённые слова

#### 1. В папке .git/hooks был создан файл **pre-commit** с кодом:
```bash
#!/bin/bash
echo "Проверка запрещённых слов"

if git diff --cached | grep -E "SECRET|TOKEN|PASSWORD"; then #Ищет в файлах слова SECRET, TOKEN, PASSWORD
    echo "ОШИБКА: Найдено запрещённое слово"
    exit 1 #Нашёл, коммит отменяется
fi

echo "Проверка прошла успешно"
exit 0 #Не нашёл, коммит проходит
```
#### 2. После этого в терминале VS Code была выполнена команда для того, чтобы файл стал исполняемым:
```bash
chmod +x .git/hooks/pre-commit
```
#### 3.  Проверка работы хука:

Был создан тестовый файл с запрещённым словом:

```bash
echo "my SECRET password" > test.txt
git add test.txt
git commit -m "test commit"
```
Вывод терминала:

```bash
Проверка запрещённых слов
my SECRET password
ОШИБКА: Найдено запрещённое слово
```
*Результат:* коммит не создался – хук сработал и прервал операцию

### 1.3 Хук commit-msg – проверка длины сообщения коммита

#### 1. В папке .git/hooks был создан файл **commit-msg** с кодом:
```bash
#!/bin/bash
echo "Проверка длины сообщения коммита"

MSG=$(cat "$1") #Читаем сообщение коммита из временного файла и сохраняем в переменную MSG

if [ ${#MSG} -lt 5 ]; then #Проверяем, меньше ли длина сообщения 5 символов
    echo "ОШИБКА: Сообщение слишком короткое (нужно минимум 5 символов)"
    exit 1 #< 5, коммит отменяется
fi

echo "Проверка прошла успешно"
exit 0 #Длина >= 5, коммит проходит
```
#### 2. После этого в терминале VS Code была выполнена команда для того, чтобы файл стал исполняемым:
```bash
chmod +x .git/hooks/commit-msg
```
#### 3.  Проверка работы хука:

Была совершена попытка создать коммит с сообщением длиной меньше 5:

```bash
git commit --allow-empty -m "ab"
```
Вывод терминала:

```bash
Проверка длины сообщения коммита
ОШИБКА: Сообщение слишком короткое (нужно минимум 5 символов)
```
*Результат:* коммит не создался – хук сработал и прервал операцию

---

## 2. Хуки Git на стороне сервера

#### 1. Для эмуляции удалённого сервера была создана **bare-копия репозитория**:

```bash
cd ~
mkdir server_repo.git
cd server_repo.git
git init --bare
```

#### 2. В основном репозитории был добавлен **remote local-server**:

```bash
cd /mnt/c/Users/difil/git_labs
git remote add local-server /mnt/c/Users/difil/server_repo.git
```

#### 3. Для автоматической конвертации отчёта из Markdown в HTML была установлена утилита **pandoc**:

```bash
sudo apt install pandoc -y
pandoc --version
pandoc 3.1.3
```

#### 4. В папке hooks серверной копии создан файл **post-receive**:

```bash
cd /mnt/c/Users/difil/server_repo.git/hooks
nano post-receive
```

Содержимое файла:

```bash
#!/bin/bash
echo "Генерация HTML из Markdown"

WORK_DIR=/tmp/server_worktree
BRANCH="lab6-report"

mkdir -p $WORK_DIR
git --work-tree=$WORK_DIR --git-dir=/mnt/c/Users/difil/server_repo.git checkout $BRANCH -f

if [ -f "$WORK_DIR/reports/lab6.md" ]; then
    /usr/bin/pandoc "$WORK_DIR/reports/lab6.md" -o "$WORK_DIR/reports/lab6.html"
    echo "HTML создан: $WORK_DIR/reports/lab6.html"
else
    echo "Файл reports/lab6.md не найден в ветке $BRANCH"
fi
```

#### 5. После этого была выполнена команда для того, чтобы файл стал исполняемым:
 
 ```bash
 chmod +x /mnt/c/Users/difil/server_repo.git/hooks/post-receive
 ```

#### 6. Проверка работы хука
 В основном репозитории был создан файл **reports/lab6.md**, после чего было соверено добавление в Git и отправка на сервер:
 
 ```bash
 git add reports/lab6.md
 git commit -m "add lab6.md in reports"
 git push local-server lab6-report
 ```
 Вывод терминала:
 ```bash
 remote:  Генерация HTML из Markdown 
 remote: Already on 'lab6-report'
 remote:  HTML создан: /tmp/server_worktree/reports/lab6.html
 To /mnt/c/Users/difil/server_repo.git
    201562d..3e0747c  lab6-report -> lab6-report
 ```

#### 6. Открытие HTML в браузере
 HTML-файл доступен по адресу:

 ```bash
 \\wsl$\Ubuntu\tmp\server_worktree\reports\lab6.html
 ```
#### 7. Проверка обновления HTML при изменении отчёта
 При последующем изменении lab6.md и новом push хук автоматически пересоздаёт HTML.