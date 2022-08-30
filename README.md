# Парсер аргументов

```cpp
int main(int argc, char *argv[])
{
    ArgPars cfg(error, false);
    cfg.addKey('h', "hello", ArgPars::NO);
    cfg.addKey('m', "my", ArgPars::OPTIONAL);
    cfg.addKey('w', "world", ArgPars::REQUIRED);
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