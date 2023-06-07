# Использование образа Ubuntu
FROM ubuntu

# Добавление информации об авторе в качестве метки
LABEL author="Babikov Matvey"

# Установка модулей для компиляции Qt
ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt-get update
RUN apt-get install qt5-default -y
RUN apt-get install qtbase5-dev -y
RUN apt-get install qt5-qmake
RUN apt-get install build-essential -y

# Копирование файлов проекта в контейнер
COPY . /babikov_221-353

# Установка рабочей директории
WORKDIR /babikov_221-353

# Компиляция проекта
RUN qmake
RUN make

CMD ["./hallServer"]
