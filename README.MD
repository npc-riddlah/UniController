RU:
Проект по созданию минимально рабочего, готового к относительно простому и быстрому программированию контроллера для автоматизации или мониторинга чего-либо на базе STM32. Полезно при быстром прототипировании или создании простых контроллеров "На коленке".
Построен на базе HAL и с использованием стороннего драйвера контроллера ILI9341 (Casual Way).

Какие фичи уже готовы:
- Библиотека для рисования графики
    - Отрисовка и программирование страниц
        - Меню
        - Таблица данных
    - Статусбары
    - Памятка по вводу
- Управление
    - Не очень классный обработчик ввода 
        - Различные режимы ввода

Что ещё предстоит (Список будет расширяться):
- Библиотека для рисования графики
    - Вынести либу в отдельный проект (Сейчас вшит прямо в main.c! Это совсем не круто!)
    - Отрисовка графиков
    - Отрисовка битмапов
    - Поддержка кириллицы для ILI9341
- Управление
    - Переписать обработчик ввода на прерывания
    - Репозиторий
    - Добавить схемы подключения
- Платы
    - Доделать SMD версию с дисплеем и пример mod-pcb-mini.
____

EN:
Creating minimal, ready to fast programming automating\monitoring\both controller. Builded with HAL and ILI9341 driver (Casual Way).

Which features ready:
> GUI Draw Lib
> > Page-Drawing
> > > Menus
> > > Data Tables
> > Statusbars
> > Input helpers
> Input
> > Not so good input worker
> > Input modes

TODO Features:
> GUI Draw Lib
> > Bring the GUI lib out from this project (THESE RIGHT IN THE CRACKIGN MAIN.C!!! It's bad!)
> > Charts drawing
> > Bitmaps drawing
> > Cyrillyc ILI9341 Fonts
> Input
> > Rewrite input worker using interrupts.
> Repo
> > Add schemes
> Boards
> > Completing of SMD Version with Display and mod-pcb-mini example.