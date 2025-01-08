# kernel

Это проект анархичной операционной системы

## Сборка и запуск

1. Установите необходимые инструменты:
```bash
sudo apt install gcc build-essential grub2-common qemu
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
- `kernel/`: Основной код ядра.
- `scripts/`: Скрипты для сборки и запуска.
