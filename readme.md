# astra-test-task

## Общее задание
Установить Astra Linux 2.12 на виртуалку.
Обновиться до последней версии.
Установить из нашего репозитория QtCreator и пакет qtbase5-examples.
Открыть проект examples/widgets/itemviews/dirview
Сделать стартовой директорией домашнюю директорию текущего пользователя. То есть того пользователя что запускает утилиту.
Отображать файлы, папки, в том числе и скрытые.
Добавить QLineEdit виджет, который использовать для фильтрации по именам файлов и папок.

## Задание по Qt
Взять за основу проект examples/widgets/itemviews/dirview
Сделать стартовой директорией домашнюю директорию текущего пользователя. То есть того пользователя что запускает утилиту.
Отображать файлы, папки, в том числе и скрытые.
Добавить QLineEdit виджет, который использовать для фильтрации по именам файлов и папок.


## Решение

- Для отображения использовался _QTreeView_. 
- Для отображения файлов, папок в том числе скрытых к _QFileSystemModel_ были применены фильтры: _QDir::Dirs | QDir::Hidden | QDir::Files | QDir::NoDotAndDotDot_
- Для фильтрации использовался _QSortFilterProxyModel_; синтаксис - _QRegExp::RegExp_; чувстивительность фильтра к регистру может выбрать пользователь
- Для расположения виджетов использовался _QGridLayout_
- Для установки домашней директории в качестве стартовой директории использовался метод _setRootIndex(rootIndex)_ экземпляра класса _QTreeView_, где в качестве rootIndex передается домашняя директория текущего пользователя - _QDir::cleanPath(QDir::home().path())_

P.s. возможно можно было обойтись обычной фильтрацией имен с помощью метода _setNameFilters(QStringList() << text)_ экземпляра класса _QFileSystemModel_

Стартовое окно
![N|Solid](https://raw.githubusercontent.com/mozgolom112/astra-test-task/main/screenshots/pict_1.png)

Пример фильтрации
![N|Solid](https://raw.githubusercontent.com/mozgolom112/astra-test-task/main/screenshots/pict_2.png)

Пример фильтрации с регистром
![N|Solid](https://raw.githubusercontent.com/mozgolom112/astra-test-task/main/screenshots/pict_3.png)

Пример фильтрации вложенных файлов
![N|Solid](https://raw.githubusercontent.com/mozgolom112/astra-test-task/main/screenshots/pict_5.png)