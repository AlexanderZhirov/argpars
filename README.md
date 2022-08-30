# Парсер аргументов

```cpp
int main(int argc, char *argv[])
{
    Config cfg(error, false);
    cfg.addKey('h', "hello", Config::NO);
    cfg.addKey('m', "my", Config::OPTIONAL);
    cfg.addKey('w', "world", Config::REQUIRED);
    cfg.readArguments(argc, argv);

    if (cfg.checkKey('h'))
        std::cout << "h установлен" << std::endl;

    if (cfg.checkKey('m'))
        std::cout << "m установлен " << cfg.getValue('z') << std::endl;

    if (cfg.checkKey('w'))
        std::cout << "w установлен" << std::endl;

    return 0;
}
```