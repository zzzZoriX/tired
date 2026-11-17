[RU](#ru) | [ENG](#eng)

---

# Tired

<a id="ru"></a>

# RU

**Tired** — кроссплатформенная консольная утилита для управления процессами операционной системы.

## О проекте

Tired — инструмент для работы с процессами, предоставляющий возможность сохранять информацию о запущенных процессах и восстанавливать её при необходимости.

Проект разрабатывается на C++ с использованием системных возможностей Windows и Linux.

### Возможности

- Захват всех активных процессов.
- Восстановление всех процессов, активных на момент последнего сохранения.
- Автоматическое сохранение.
- Игнорирование выбранных файлов при захвате процессов.
- (В будущем) Удобный графический интерфейс (GUI).

### Команды

| Команда | Описание |
|---|---|
| `grab` | Получение и сохранение информации о процессах. |
| `restore` | Восстановление сохранённых данных. |
| `auto-grab` | Запуск автоматического сохранения процессов. |
| `auto-grab-time` | Настройка интервала автоматического сохранения. |
| `add-to-ignore` | Добавление файлов в специальный список игнорирования. Файлы из этого списка больше не учитываются командой `grab`. |
| `remove-from-ignore` | Удаление файлов из списка игнорирования, после чего команда `grab` снова сможет учитывать их. |
| `help` | Вывод справки. |
| `quit` | Завершение работы приложения. |

### Технологии

- **CMake** — система сборки.
- **C++20** — использование современных возможностей языка, включая `std::jthread` и `std::stop_token`.

### Платформы

- Windows
- Linux

### Автор

**zorix**

---

<a id="eng"></a>

# ENG

**Tired** is a cross-platform command-line utility for managing operating system processes.

## About

Tired is a tool for working with processes, providing the ability to save information about running processes and restore them when needed.

The project is developed in C++ using platform-specific capabilities of Windows and Linux.

### Features

- Capture all active processes.
- Restore all processes that were active at the time of the last save.
- Automatic process saving.
- Ignore selected files during process capture.
- (In the future) User-friendly graphical interface (GUI).

### Commands

| Command | Description |
|---|---|
| `grab` | Retrieves and saves process information. |
| `restore` | Restores previously saved data. |
| `auto-grab` | Starts automatic process saving. |
| `auto-grab-time` | Configures the automatic saving interval. |
| `add-to-ignore` | Adds files to a dedicated ignore list. Files in this list will no longer be considered by the `grab` command. |
| `remove-from-ignore` | Removes files from the ignore list, allowing the `grab` command to consider them again. |
| `help` | Displays application help. |
| `quit` | Exits the application. |

### Technologies

- **CMake** — build system.
- **C++20** — modern C++ language features, including `std::jthread` and `std::stop_token`.

### Platforms

- Windows
- Linux

### Author

**zorix**

---

<p align="center">
  <b>Tired</b> — Process Management Utility
</p>