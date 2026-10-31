# D09T06. Многофайловые проекты, символы и строки

Учебный проект школы 21 (School 21 / Ecole 42), посвящённый многофайловым проектам, сборке через `Makefile`, статическим и динамическим библиотекам, а также собственной реализации функций из `<string.h>`.

## Стек и требования

- Язык: **C** (стандарт **C11**)
- Компилятор: **gcc**
- Флаги сборки: `-Wall -Wextra -Werror`
- Стиль кода: **Google C++ Style Guide**
- Глобальные переменные запрещены
- Обязательная очистка всей выделенной памяти
- Запрещено использовать `<string.h>` и другие библиотеки для операций со строками — реализация своя
- Разрешённые стандартные библиотеки: `<stdio.h>`, `<stdlib.h>`, плюс `<math.h>` в модулях статистики и решений
- Вывод чисел с плавающей точкой — **2 знака после запятой** (если в задании не указано иное)
- Вывод программ не должен заканчиваться переводом строки, если это не предусмотрено форматом
- Скомпилированные файлы (`build/`, объектные файлы, `*.a`, `*.so`) в репозиторий **не попадают**

## Структура репозитория

```text
src/
├── data_libs/
│   ├── data_io.c
│   ├── data_io.h
│   ├── data_stat.c
│   └── data_stat.h
├── data_module/
│   ├── data_module_entry.c
│   ├── data_process.c
│   └── data_process.h
├── main_executable_module/
│   ├── main_executable_module.c
│   └── Makefile
├── s21_string/
│   ├── Makefile
│   ├── s21_string.c
│   ├── s21_string.h
│   └── s21_string_test.c
└── yet_another_decision_module/
    ├── decision.c
    ├── decision.h
    └── yet_another_decision_module_entry.c
```

Все программы используют общий Makefile-контекст: собираемые бинарники складываются в `build/` в корне репозитория, туда же — библиотеки `*.a` и `*.so` (в репозиторий не коммитятся).

## Модули

### `data_libs/` — общие функции ввода-вывода и статистики

Библиотека-фундамент для остальных модулей. Разделена на два блока:

**`data_io.c` / `data_io.h`** — ввод и вывод массива `double`:

- `void input(double *data, int n)` — читает `n` чисел с плавающей точкой из `stdin`;
- `void output(const double *data, int n)` — печатает `n` чисел с точностью 2 знака, разделяя пробелами.

**`data_stat.c` / `data_stat.h`** — статистика массива `double`:

- `double max(const double *data, int n)` — максимум;
- `double min(const double *data, int n)` — минимум;
- `double mean(const double *data, int n)` — математическое ожидание;
- `double variance(const double *data, int n)` — дисперсия;
- `void sort(double *data, int n)` — пузырьковая сортировка по возрастанию.

### `data_module/` — Quest 1. Модуль нормализации

Принимает длину `n` и массив `double`, нормализует его в диапазон `[0, 1]` по min-max:

```text
data[i] = (data[i] - min) / (max - min)
```

Если `max - min < EPS` (1e-6), выводит `ERROR`. Иначе — нормализованный массив через `output`.

- **Вход:** `n`, затем `n` чисел
- **Выход:** нормализованный массив через пробел (2 знака после запятой) или `ERROR`
- **Библиотеки:** `<stdio.h>`, `<stdlib.h>`, `<math.h>`

| Вход                  | Выход                       |
|-----------------------|-----------------------------|
| `5`<br/>`1 2 3 4 5`   | `0.00 0.25 0.50 0.75 1.00` |

```bash
gcc -Wall -Wextra -Werror -std=c11 src/data_module/data_module_entry.c \
    src/data_module/data_process.c \
    src/data_libs/data_io.c src/data_libs/data_stat.c \
    -Isrc/data_libs -Isrc/data_module -o data_module -lm
printf "5\n1 2 3 4 5\n" | ./data_module
# 0.00 0.25 0.50 0.75 1.00
```

### `yet_another_decision_module/` — Quest 2. Модуль принятия решения

Принимает массив `double` и выводит `YES` или `NO`.

`make_decision(data, n)` возвращает `1` (YES), если одновременно:

- данные подчиняются правилу трёх сигм: `min ≥ mean - 3σ` и `max ≤ mean + 3σ`;
- среднее значение не меньше обратного золотого сечения: `mean ≥ 0.618`.

Иначе — `0` (NO).

- **Вход:** `n`, затем `n` чисел
- **Выход:** `YES` или `NO`
- **Библиотеки:** `<stdio.h>`, `<stdlib.h>`, `<math.h>`

| Вход                | Выход |
|---------------------|-------|
| `4`<br/>`1 2 3 4`   | `YES` |

```bash
gcc -Wall -Wextra -Werror -std=c11 src/yet_another_decision_module/yet_another_decision_module_entry.c \
    src/yet_another_decision_module/decision.c \
    src/data_libs/data_io.c src/data_libs/data_stat.c \
    -Isrc/data_libs -Isrc/yet_another_decision_module -o decision_module -lm
printf "4\n1 2 3 4\n" | ./decision_module
# YES
```

### `main_executable_module/` — Quest 3. Итоговый исполняемый модуль + Makefile

Объединяет всё вместе: загружает массив, принимает решение по правилу трёх сигм и золотого сечения, нормализует, сортирует и выводит результат по шагам.

Формат вывода:

```text
LOAD DATA...
RAW DATA:
    <числа>
NORMALIZED DATA:
    <числа>
SORTED NORMALIZED DATA:
    <числа>
FINAL DECISION:
    YES|NO
```

`Makefile` в этой директории реализует стандартные цели и цели из бонусных квестов:

| Цель | Что делает |
|------|-----------|
| `all` (по умолчанию) | Собирает `build/Quest_3` |
| `clean` | Удаляет артефакты сборки |
| `rebuild` | `clean` + `all` |
| `build_with_static` (Quest 4) | Собирает `build/Quest_4` со статической библиотекой `data_stat.a` |
| `build_with_dynamic` (Quest 5) | Собирает `build/Quest_5` с динамической библиотекой `data_process.so` |

```bash
cd src/main_executable_module
make            # → ../../build/Quest_3
make rebuild
make clean
```

Использование:

```bash
../../build/Quest_3
```

> Уточните актуальный набор целей в вашем `Makefile` — в README описаны цели, которые требует задание.

### `s21_string/` — Quest 6–7. Собственная библиотека строк

Минимальная реализация части `<string.h>`, без подключения самой `<string.h>`.

**`s21_string.h` / `s21_string.c`** — реализованные функции:

- `size_t s21_strlen(const char *str)` — длина строки (безопасно обрабатывает `NULL`, возвращает `0`);
- `int s21_strcmp(const char *s1, const char *s2)` — лексикографическое сравнение (возвращает `<0`, `0`, `>0`; безопасно обрабатывает `NULL`).

**`s21_string_test.c`** — модульные тесты:

- `s21_strcmp_test` — 15 тестов: нормальные, краевые, `NULL`, `"\0..."`, разная длина, разные регистры — выводит вход, результат и `SUCCESS`/`FAIL`.
- `s21_strlen_test` — оставлен заглушкой, требует заполнения (см. раздел «Текущее состояние»).

`Makefile` в `s21_string/` содержит цели для сборки тестов (например, `strlen_tests`, `strcmp_tests`). Бинарники складываются в `build/` в корне репозитория.

```bash
cd src/s21_string
make strcmp_tests        # → ../../build/Quest_7
../../build/Quest_7
```

## Сборка: общие принципы

- Все `Makefile` лежат в своих директориях и используют **относительные пути** — рассчитаны на запуск из своей директории (`cd src/<module> && make`).
- Скомпилированные файлы и артефакты сборки **не коммитятся** — в `.gitignore`:
  ```gitignore
  build/
  *.o
  *.a
  *.so
  *.out
  a.out
  *:Zone.Identifier
  ```
- Внутри программ пути к заголовкам подключаются через `-I`, чтобы компилятор находил `data_io.h`, `data_stat.h`, `decision.h` из соседних модулей.

## Текущее состояние проекта

**Реализовано полностью:**

- Quest 1 — `data_module` (нормализация массива);
- Quest 2 — `yet_another_decision_module` (`make_decision` с правилом трёх сигм и золотым сечением);
- Quest 3 — `main_executable_module` + `Makefile` со стандартными целями;
- `data_libs` — общие `data_io` и `data_stat`;
- `s21_strlen` и `s21_strcmp` в `s21_string`, тест `s21_strcmp_test` (15 кейсов) — работоспособен.

**Не реализовано / требует доработки:**

- `s21_strcpy`, `s21_strcat`, `s21_strchr`, `s21_strstr` (Quest 8–11);
- расширенное тестирование всех функций (Quest 12) и `text_processor` (Quest 13) — не реализованы;
- бонусные цели `build_with_static`, `build_with_dynamic` в Makefile `main_executable_module` — присутствуют по заданию; если вы их не добавляли, соответствующие строки в разделе про Makefile не актуальны.

Эти пункты помечены, чтобы README честно отражал состояние репозитория. По мере реализации разделы можно дополнять.

## Проверка на утечки памяти

По условию задания все программы должны освобождать выделенную память. Рекомендуется прогонять через `valgrind`:

```bash
valgrind --leak-check=full --error-exitcode=1 ../../build/Quest_3 < test.txt
```

Установка (Ubuntu/Debian):

```bash
sudo apt update && sudo apt install -y valgrind
```

## Примечания

- Проект выполнен в рамках учебной программы школы 21 (D09T06).
- Многофайловый проект: каждый модуль — своя директория со своими `.c` и `.h`, сборка через `Makefile`.
- В репозитории намеренно отсутствуют объектные и исполняемые файлы, а также `*.a` и `*.so` — только исходный код и `Makefile`.
- Реализация строковых функций полностью независима от `<string.h>`.
- Числа с плавающей точкой выводятся с точностью 2 знака после запятой, если не задано иное.

## Автор

**monabeef**