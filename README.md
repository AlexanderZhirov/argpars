# Парсер аргументов

Обработка аргументов при запуске программы.


Объект типа `Hub` принимает первым аргументом вектор объектов типа `ConfigOption`, где аргументы:

1. Длинное имя аргумента
2. Короткое имя аргемнта
3. Наличие значения у аргумента: `NO` (НЕТ), `REQUIRED` (ОБЯЗАТЕЛЬНО), `OPTIONAL` (НЕОБЯЗАТЕЛЬНО)
4. Указатель на предварительную функцию-обработчик перед получением фактического значения(ий) аргумента

Вторым аргументом устанавливается значение тихого режима (по умолчанию `true`) для отображения системных ошибок при чтении аргументов.

- `readArguments` - чтение аргументов, где 3-ий аргумент функция на обработку ошибочных опций.
- `getOption` - получить объект опции
    - `getValues` - получить значение опции. С параметром `true` выполнить предварительную обработку функцией, переданной в качестве аргумента при создании объекта `Hub`

```cpp
#include <argpars.hpp>

void message()
{
    std::cout << "Неверный аргумент" << std::endl;
    exit(1);
}

typedef std::vector<std::string> arguments;

arguments print(const arguments &v)
{
    std::cout << v.front() << std::endl;
    return v;
}

int main(int argc, char *argv[])
{
    args::Hub hub({
        {"help", 'h', args::REQUIRED, print},
        {"name", 'n', args::OPTIONAL, print}
    }, false);

    hub.readArguments(argc, argv, message);
    arguments a = hub.getOption('h').getValues(true);
    arguments b = hub.getOption('n').getValues(true);

    return 0;
}
```

Запуск примера:

```sh
$ ./app --help="Hello, World" -n"Александр Жиров"
Hello, World
Александр Жиров
```
