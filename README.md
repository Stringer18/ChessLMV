## The game "Chess"


OS Windows 10

MCVS 2010 v.10.0.30319.1

Libs:

	SDL2-2.0.10
	SDL2_ttf-2.0.15
	SDL2_image-2.0.5

Build Win32


## En:

Control -  mouse only.

Implemented:

	1. Game for 2 players.
	2. Move of figures.
	3. Displaying tips, including for illegal moves, check to the king, etc.
	4. Implemented rules:
		4.1. Automatic end with a draw (stalemate) after repeating a position on the board 3 times.
		4.2. Automatic end with a draw (stalemate) in case of 50 moves without attack figures and without moving pawns.
		4.3. Invalid moves are processed but not executed.
		4.4. In the case of substituting your king for a check by the result of the move, drawing is not performed, the move is calculated and the figures return to their original position.
		4.5. En passant ("Taking on the pass").
		4.6. Pawn promotion on the 8th line.
		4.7. Castles (long and short).
	5. Implemented features:
		5.1. Launching a new batch at any time.
		5.2. Draw ends by agreement.
		5.3. The player's capitulation.
		5.4. Lock the board while selecting a menu item.
		5.5. Log output to a file and to the console (for online monitoring).
		5.6. Error handling and correct termination in case of technical impossibility to continue the game.
	6. The configuration of the game settings is stored in the file ".\Resources\ChessLMV.ini". The following keys can be changed:
		6.1. "iHideConsole" (section "gameWindow") == 0 after starting the console remains visible, == 1 the console is hiding. Default == 1.
		6.2. "iMaxMovesToDram" (section "rules") number of moves (white + black) for stalemate ch.4.2. Default == 100 (50+50).
		6.3. "iMaxRepeats" (section "rules") number of repetitions of the situation for stalemate ch.4.1. Default == 3.
		6.4. "isdlDefaultColorR" (=0), "isdlDefaultColorG" (=0), "isdlDefaultColorB" (=0), "isdlDefaultColorA" (=255) section "font" - font color and transparency. Valid values 0-255.
		Warning: In this release, the values read from the configuration file are not validated. Setting incorrect values may cause the program to malfunction.

Not implemented (due to limited time for project implementation):

	1. Automatic completion with mate. (see Solutions ch.1.)
	2. Automatic completion of a draw (stalemate) in the case when the player's king is not in check, but there is not a single legal move. (see Solutions ch.2.)
	3. The eternal shah. (see Solutions ch.3.)
	4. A stalemate when there are not enough figures left on the board to checkmate. (see Solutions ch.3.)
	5. Play against the computer. (see Notes ch.1.)

Solutions:

	1. In the event of a checkmate, the player will not be able to make a single move (see Implemented ch.4.4 and ch.3.) And he will only have to capitulate (see Implemented ch.5.3.).
	2. If the player's king is not in check, but there is not a single legal move, end the game manually - draw (see Implemented in clause 5.2.).
	3. In a situation where there is a perpetual check or there are not enough figures to checkmate, the game can automatically end by fulfilling one of the conditions of realized stalemates (see Implemented ch.4.1. and ch.4.2.) or by agreement of the players (see Implemented ch.5.2.).

Notes:

	1. There was not enough time to create a game mode against the computer. I hope to write it in the future. Article on the topic: https://habr.com/ru/company/skillbox/blog/437524/
	
Used materials from sources:

	Rules of the game:
	https://www.chess.com/ru/kak-igrat-v-shakhmaty
	http://megachess.net/School_textbook_lesson1
	
	Figures images:
	http://blog.kislenko.net/show.php?id=1860
	
	Font:
	https://www.fonts-online.ru/font/Old-Standard-TT-Italic


## Ru:

Управление - только мышь.

Реализовано:

	1. Игра для 2х человек.
	2. Хода фигур.
	3. Вывод подсказок, в том числе при недопустимых ходах, угрозе королю и т.д.
	4. Реализованы правила:
		4.1. Автоматическое завершение ничьёй (пат) после 3х кратного повторения позиции на доске.
		4.2. Автоматическое завершение ничьёй (пат) в случае 50 ходов без взятия фигур и без движения пешек.
		4.3. Недопустимые хода обрабатываются, но не выполняются.
		4.4. В случае подставления своего короля под шах по результату хода - отрисовка не выполняется, ход просчитывается и фигуры возвращаются на исходную позицию.
		4.5. Взятие на проходе.
		4.6. Превращение пешки на 8й линии.
		4.7. Рокировки (длинная и короткая).
	5. Реализованы возможности:
		5.1. Запуск новой партии в любой момент времени.
		5.2. Завершение ничьёй по договорённости.
		5.3. Сдача игрока.
		5.4. Блокировка доски во время выбора пункта меню.
		5.5. Вывод лога в файл и в консоль (для оперативного мониторинга).
		5.6. Обработка ошибок и корректное завершение в случае технической невозможности продолжения игры.
	6. Конфигурация настроек игры хранится в файле ".\Resources\ChessLMV.ini". Допустимо изменение следующих ключей:
		6.1. "iHideConsole" (секция "gameWindow") == 0 после старта консоль остаётся видимой, == 1 консоль прячется. По умолчанию == 1.
		6.2. "iMaxMovesToDram" (секция "rules") количество ходов (белых + чёрных) для пата п.4.2. По умолчанию == 100 (50+50).
		6.3. "iMaxRepeats" (секция "rules") количество повторов ситуации для пата п.4.1. По умолчанию == 3.
		6.4. "isdlDefaultColorR" (=0), "isdlDefaultColorG" (=0), "isdlDefaultColorB" (=0), "isdlDefaultColorA" (=255) секции "font" - цвет шрифта и его прозрачность. Допустимые значение 0-255.
		Предупреждение: В данной версии значения, считанные из файла конфигурации не проверяются на допустимость. Установка не корректных значений может привести к неработоспособности программы.

Не реализовано (в связи с ограниченным временем на реализацию проекта):

	1. Автоматическое завершение матом. (см. Решения п.1.)
	2. Автоматическое завершение ничьёй (пат) в случае когда король игрока не под шахом, но нет ни одного допустимого хода. (см. Решения п.2.)
	3. Вечный шах. (см. Решения п.3.)
	4. Пат, когда на доске осталось недостаточно фигур, чтобы поставить мат. (см. Решения п.3.)
	5. Игра против компьютера. (см. Примечания п.1.)

Решения ситуаций:

	1. В случае наступления мата, игрок не сможет сделать ни один ход (см. Реализовано п.4.4. и п.3.) и ему останется только сдаться (см. Реализовано п.5.3.).
	2. В случае когда король игрока не под шахом, но нет ни одного допустимого хода, завершите игру вручную - ничья (см. Реализовано п.5.2.).
	3. В ситуации, когда возникает вечный шах или недостаточно фигур для мата, партия может автоматически завершиться выполнив одно из условий реализованных патов (см. Реализовано п.4.1. и п.4.2.) или по договорённости игроков (см. Реализовано п.5.2.).

Примечания:

	1. На создание режима игры против компьютера не хватило времени. Рассчитываю в дальнейшем его написать. Статья на тему: https://habr.com/ru/company/skillbox/blog/437524/

Использованы материалы из источников:

	Правила игры:
	https://www.chess.com/ru/kak-igrat-v-shakhmaty
	http://megachess.net/School_textbook_lesson1
	
	Изображения фигур:
	http://blog.kislenko.net/show.php?id=1860
	
	Шрифт:
	https://www.fonts-online.ru/font/Old-Standard-TT-Italic
