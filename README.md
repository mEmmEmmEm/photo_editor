# PhotoEditor

Простой консольный фоторедактор на C++ с использованием библиотеки **stb_image**. Позволяет применять базовые фильтры к изображениям: инвертирование цветов, градации серого, яркость, контраст, поворот, зеркалирование.

## Зависимости

- C++17
- [stb_image.h / stb_image_write.h](https://github.com/nothings/stb) (включены в проект)
- CMake ≥ 3.10

## Сборка

git clone https://github.com/your_username/photo_editor.git
cd photo_editor
mkdir build
cd build
cmake ..
cmake --build . 

## Использование

./PhotoEditor input.jpg output.jpg filter:param=value,filter2:param2=value2,...

## Примеры

### Инвертировать цвета
./PhotoEditor input.jpg output.jpg invert

### Перевести в ч/б
./PhotoEditor input.jpg output.jpg grayscale

### Повысить яркость на 50
./PhotoEditor input.jpg output.jpg brightness:value=50

### Уменьшить контраст
./PhotoEditor input.jpg output.jpg contrast:value=0.8

### Повернуть изображение на 90 градусов
./PhotoEditor input.jpg output.jpg rotate:angle=90

### Отразить изображение по вертикали
./PhotoEditor input.jpg output.jpg flip:direction=vertical

### Применить несколько фильтров
./PhotoEditor input.jpg output.jpg grayscale brightness:value=30 rotate:angle=180

## Поддерживаемые фильтры

Ниже перечислены фильтры, которые можно применять к изображению, а также их параметры и описание:

| Фильтр        | Параметры                            | Описание                                                           |
|---------------|---------------------------------------|--------------------------------------------------------------------|
| `invert`      | —                                     | Инвертирует цвета изображения (негатив)                           |
| `grayscale`   | —                                     | Преобразует изображение в оттенки серого                          |
| `brightness`  | `value=int` (от -255 до 255)          | Увеличивает или уменьшает яркость изображения                     |
| `contrast`    | `value=float` (например, 1.2 или 0.8) | Регулирует контрастность (значения >1 усиливают контраст)         |
| `rotate`      | `angle=90`, `180`, `270`              | Поворачивает изображение на указанный угол                        |
| `flip`        | `direction=horizontal` или `vertical`| Отражает изображение по горизонтали или вертикали                |

Все фильтры можно комбинировать. Порядок применения влияет на результат.
