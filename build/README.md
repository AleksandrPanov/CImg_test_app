0) Разархивировать картинку в папке bin.


1) Выполните в командной строке команду: cmake -G "Visual Studio 15 2017 Win64" ../


Либо команду: cmake -G "Visual Studio 14 2015 Win64" ../


2) В выходном каталоге проекта main (ПКМ-свойства-общие) установите значение:


$(ProjectDir)/../bin


В рабочем каталоге проекта main (ПКМ-свойства-отладка) установите значение:


$(ProjectDir)/../bin


3) Назначить автозагружаемым проектом main
