# kernel

![](https://img.shields.io/github/languages/code-size/CIS-osdev/kernel) ![](https://img.shields.io/github/license/CIS-osdev/kernel)

[![C/C++ CI](https://github.com/CIS-osdev/kernel/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/CIS-osdev/kernel/actions/workflows/c-cpp.yml)
[![pages-build-deployment](https://github.com/CIS-osdev/kernel/actions/workflows/pages/pages-build-deployment/badge.svg)](https://github.com/CIS-osdev/kernel/actions/workflows/pages/pages-build-deployment)
[![CodeQL Advanced](https://github.com/0Nera/cis-kernel/actions/workflows/codeql.yml/badge.svg)](https://github.com/0Nera/cis-kernel/actions/workflows/codeql.yml)

[![Telegram](https://img.shields.io/badge/Telegram-2CA5E0?style=for-the-badge&logo=telegram&logoColor=white)](https://t.me/russian_os/10921)

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)

![Stars](https://img.shields.io/github/stars/CIS-osdev/kernel.svg)
![Forks](https://img.shields.io/github/forks/CIS-osdev/kernel.svg)
![watchers](https://img.shields.io/github/watchers/CIS-osdev/kernel.svg)
![followers](https://img.shields.io/github/followers/CIS-osdev.svg?style=social&label=Follow&maxAge=2592000)

![issues](https://img.shields.io/github/issues/CIS-osdev/kernel.svg)
![issues-closed](https://img.shields.io/github/issues-closed/CIS-osdev/kernel.svg)
![issues-pr](https://img.shields.io/github/issues-pr/CIS-osdev/kernel.svg)
![issues-pr-closed](https://img.shields.io/github/issues-pr-closed/CIS-osdev/kernel.svg)

Users: 0

---

Это проект анархичной операционной системы

## Сборка и запуск

1. Установите необходимые инструменты:
```bash
sudo apt install gcc build-essential grub2-common grub-pc xorriso qemu-system-x86 xorriso mtools clang-format cpio
```

2. Соберите проект:
```bash
make
```

3. Запустите в QEMU:
```bash
make run
```

## Структура проекта

- `boot/`: Конфигурация GRUB.
- `docs/`: Документация и инструкции.
- `kernel/`: Основной код ядра.
- `initrd/`: Файлы виртуального диска.
- `scripts/`: Скрипты для сборки и запуска.

## XD

![starchart](https://starchart.cc/CIS-osdev/kernel.svg)
