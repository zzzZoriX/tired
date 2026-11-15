[ru](#ru) | [eng](#eng)

---

# Tired

<a id="ru"></a>

# RU

**Tired** — кроссплатформенная консольная утилита для управления процессами операционной системы.

## О проекте

Tired — инструмент для работы с процессами, предоставляющий возможность сохранять информацию о запущенных процессах и восстанавливать её при необходимости.

Проект разрабатывается на C++ с использованием системных возможностей Windows и Linux.

### Возможности

- Захватывать все активные процессы
- Востанавливать все активные на момент последнего сохранения процессы
- Автосохранение
- (В будущем) Удобные GUI

### Команды

| Команда | Описание |
|---|---|
| `grab` | Получение и сохранение информации о процессах. |
| `restore` | Восстановление сохранённых данных. |
| `auto-grab` | Запуск автоматического сохранения процессов. |
| `auto-grab-time` | Настройка интервала автоматического сохранения. |
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

Tired is a tool for working with processes, providing the ability to save information about running processes and restore it when needed.

The project is developed in C++ using platform-specific capabilities of Windows and Linux.

### Features

- Capture all active processes
- Restore all processes that were active at the time of the last save
- Autosave
- (In the future) User-friendly GUI

### Commands

| Command | Description |
|---|---|
| `grab` | Retrieves and saves process information. |
| `restore` | Restores previously saved data. |
| `auto-grab` | Starts automatic process saving. |
| `auto-grab-time` | Configures the automatic saving interval. |
| `help` | Displays application help. |
| `quit` | Exits the application. |

### Technologies

- **CMake** — build system.
- **C++20** — modern language features

### Platforms

- Windows
- Linux

### Author

**zorix**

---

<p align="center">
  <b>Tired</b> — Process Management Utility
</p>