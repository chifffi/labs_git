# Лабораторная работа №2. Git Flow, Code Review

## Ход работы

### 1. Подготовка репозитория

1. Через проводник в репозитории была создана папка `labs` для хранения лабораторных работ по программированию. Внутри нее была создана папка `lab1`, в которой находился код невыполненной первой лабораторной работы.

2. Файл `.gitignore` показывает, какие файлы и папки не нужно отслеживать и добавлять в репозиторий. Он позволяет исключить из репозитория файлы сборки.

3. В папке `labs` был создан файл `.gitignore` с таким содержимым:
    ```bash
    build/
    *.exe
    ```

    *Пояснение:*
    + `build/` — игнорирует папку сборки со всеми объектными файлами

    + `*.exe` — игнорирует исполняемые файлы

4. Файл `.gitignore` был добавлен и закоммичен:
    ```bash
    git add .
    git commit -m "Добавление .gitignore для игнорирования папки с файлами сборки"
    git push origin main
    ```
5. Проверка работы `.gitignore` после компиляции программы в папке `labs/lab1` :
    ```bash
    git status

    On branch main
    nothing to commit, working tree clean
    ```
---

### 2. Защита веток

1. Защита веток — это механизм GitHub, который позволяет накладывать ограничения на определенные ветки для того, чтобы предотвратить случайные изменения.

2. Репозиторий был сделан публичным, так как для приватных репозиториев на бесплатном аккаунте защита веток не работает. В настройках репозитория было добавлено правило защиты для ветки main:
    + `Require a pull request before merging` - теперь все изменения могут попасть в основную ветку только через Pull Request

    + `Do not allow bypassing the above settings` - запрещает обход правил даже владельцам и администраторам репозитория

3. Чтобы проверить защиту, в файле `README.md` были внесены изменения, после чего совершен тестовый коммит и попытка отправить его напрямую в `main`:
    ```bash
    git add README.md
    git commit -m "Проверка защиты ветки номер 2"
    git push origin main

    remote: error: GH006: Protected branch update failed for refs/heads/main.
    remote:
    remote: - Changes must be made through a pull request.
    To github.com:chifffi/labs_git.git
    ! [remote rejected] main -> main (protected branch hook declined)
    error: failed to push some refs to 'github.com:chifffi/labs_git.git'
    ```
    *Пояснение:* прямой пуш в `main` запрещен, и даже владелец репозитория не может обойти это правило

    Тестовый коммит был удален с помощью команды:
    ```bash
    git reset --hard HEAD~1
    ```

4. В локальном репозитории была создана новая ветка `pr-test`, в которой в файле `README.md` были внесены дополнительные изменения. При попытке запушить изменения из тестовой ветки в удаленный репозиторий не возникло никаких проблем:
    ```bash
    git checkout -b pr-test
    git add README.md
    git commit -m "новое в README в ветке pr-test"
    git push -u origin pr-test
    ```
---

### 3. Запросы на слияние

1. На GitHub был создан Pull Request из ветки `pr-test` в `main`:
    ```bash
    Title: новое в README в ветке pr-test

    Description: No description provided.
    ```

2. Pull Request был принят и слит с основной веткой через интерфейс GitHub:

    + Нажата кнопка `Merge pull request`

    + Подтверждено действие кнопкой `Confirm merge`

3. После слияния локальная ветка `main` была обновлена:
    ```bash
    git checkout main
    git pull origin main
    ```
    *Пояснение:* Команда `git pull` скачала все изменения из удаленного репозитория и применила их к локальной ветке `main`. Теперь файл `README.md` содержит добавленную в ветке `pr-test` строку.
---


### 4. Code Review

1. В локальном репозитории была создана ветка prog-lab1 из актуальной версии main:
    ```bash
    git checkout -b prog-lab1
    ```
