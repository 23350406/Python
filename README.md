# Для запуска на ОС linux

Для того, чтобы запустить данный проект необходимо скопировать его к себе локально при помощи git clone и код через ssh.

## Способы запуска проекта.
### 1. Доисторический

Для этого способа необходимо выполнить следующие действия:

1.1 Открыть скопированный каталог с файлами при помощи vsCode на unix системе. 

### ***Для срабатывания следующих команд необходимо перейти в каталог, который содержит в себе CMakeLists.txt!!!***

1.2 Открыть вкладку "terminal" в vsCode и прописать там следующие команды:
+ cmake CMakeLists.txt
+ make
+ ./Python

1.3 Радуемся запущенному проекту.

<br>
<br>

### 2. Для разработчиков

Для этого способа необходимо выполнить следующие действия:

2.1 Открыть vsCode и установить туда расширение Makefile Tools.

2.2 После установки данного расширения справа в нижнем углу начнут появляться всплывающие окна с предложением настройки проекта через Maketools. Необходимо везде прокликать yes.

2.3 Открыть крайний каталог с названием Python через vsCode, появится значок для простого запуска и жучок для debug. Кликаем кнопки по мере надобности.

2.4 *Мы больше не дети терминала!!*
