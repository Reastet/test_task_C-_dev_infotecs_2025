# Readme
library-библиотека логгирования
first_exec-первая программа
second_exec-вторая программа

К сожалению, по техническим причинам, тесты не удалось реализовать, большая часть второй программы так же отсутствует

В части кода присутствуют явные архитектурные недостатки, например, наличие участков кода, которые можно явно вынести в отдельные функции, кроме того, отсутствуют комментарии по некоторым участкам кода, однако, в связи с малым размером функции, было решено часть комментариев опустить

Так же отсутствует большое количество проверок для безопасной инициализации, например, отсутсвует проверка валидности значений, передаваемых в тело функций, сделано это было для экономии времени

В first_exec было решено убрать динамическую подгрузку, хотя, реализовать это через #ifdef не составит больших трудностей

Стоит отметить, что в first_exec некоторые строки кода закомментированы, однако, они работают. Данные строки кода нужны для проверки корректности работы программы. Кроме того, в данной реализации, отправка сообщений выполнялась единым буффером, что, в целом, не совсем удобно, при реализации реальной программы и следует отправлять по сети не все сообщение разом, а по очереди: сообщение, важность, время, чтобы упростить работу сервера

Для сборки каждой программы/библиотеки следует:
1) Перейти в папку с проектом
2) Выполнить:
   mkdir build
   cd build
   cmake ..
   make
Исходники появятся в папках lib и bin
