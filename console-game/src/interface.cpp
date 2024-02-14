#include "../interface.h"

void save(string& word, string&& path = "save.txt") {
    ofstream file(path, std::ios::app);
    file << word << std::endl;
    file.close();
}

void default_print(string&& message) {
    for (auto& x : message) {
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
        std::cout << x;
        std::cout.flush();
    }
}

Commands_menu ConsoleInterface::get_command_menu() {
  string word;
  cin >> word;
  if (word == "/exit") {
    throw end_process();
  } else if (word == "/play") {
      return Commands_menu::PLAY;
  } else if (word == "/read") {
      return Commands_menu::READ;
  } else if (word == "/load") {
      return Commands_menu::LOAD;
  } else if (word == "/show") {
      return Commands_menu::SHOW;
  } else if (word == "/enter_god_mode") {
      return Commands_menu::ENTER_GOD_MODE;
  } else {
      default_print("Некорректные данные\n");
      return get_command_menu();
  }
}

Commands_act ConsoleInterface::get_command_act() {
    string word;
    cin >> word;
    if (word == "talk") {
        save(word);
        return Commands_act::TALK;
    } else if (word == "run") {
        save(word);
        return Commands_act::RUN;
    } else if (word == "/exit") {
        throw end_process();
    } else {
        default_print("Некорректные данные\n");
        return get_command_act();
    }
}

Side ConsoleInterface::get_command_room() {
    string word;
    cin >> word;
    if (word == "left") {
        save(word);
        return Side::LEFT;
    } else if (word == "right") {
        save(word);
        return Side::RIGHT;
    } else if (word == "top") {
        save(word);
        return Side::TOP;
    } else if (word == "bottom") {
        save(word);
        return Side::BOTTOM;
    } else if (word == "/exit") {
        throw end_process();
    } else {
        default_print("Некорректные данные\n");
        return get_command_room();
    }
}

Commands_fight ConsoleInterface::get_command_fight() {
    string word;
    cin >> word;
    if (word == "fight") {
        save(word);
        return Commands_fight::FIGHT;
    } else if (word == "run") {
        save(word);
        return Commands_fight::RUN;
    } else if (word == "use") {
        save(word);
        return Commands_fight::USE;
    } else if (word == "/exit") {
        throw end_process();
    } else {
        default_print("Некорректные данные\n");
        return get_command_fight();
    }
}

Commands_quest ConsoleInterface::get_command_quest() {
    string word;
    cin >> word;
    if (word == "accept") {
        save(word);
        return Commands_quest::ACCEPT;
    } else if (word == "reject") {
        save(word);
        return Commands_quest::REJECT;
    } else if (word == "/exit") {
        throw end_process();
    } else {
        default_print("Некорректные данные\n");
        return get_command_quest();
    }
}

string ConsoleInterface::get_string() {
    string word;
    cin >> word;
    if (word == "/exit") {
        throw end_process();
    }
    save(word);
    return word;
}

int ConsoleInterface::get_int() {
    string word;
    cin >> word;
    if (word == "/exit") {
        throw end_process();
    }
    try {
        int res = std::stoi(word);
        return res;
    } catch (std::invalid_argument&) {
        default_print("Некорректные данные\n");
        return get_int();
    }
}

void ConsoleInterface::print_info() {
    string message = "/Это текстовая игра, о путешествии в пещерах!\n"
                     "/Вам предстоит ходить по лабиринту подземелий и сражаться с противниками!\n"
                     "/В ходе вашего путешествия, вы будете получать опыт!\n"
                     "/Чтобы пройти игру, надо набрать необходимое количество опыта\n"
                     "/Если вы умрете - потеряете весь накопленный опыт!\n"
                     "/Для ввода команд в меню, перед сообщением нужно поставить символ '/' !\n"
                     "/Команды во время игры нужно писать без символа '/' !\n"
                     "/Есть особая команда - /exit - используйте ее, чтобы досрочно выйти из режима игры,\n"
                     "/или чтобы завершить программу в режиме меню!\n"
                     "/Когда вы выходите из режима игры до ее завершения,\n"
                     "/ваш прогресс сохраняется и вы можете ее загрузить!\n";
    default_print(std::move(message));
}

void ConsoleInterface::print_head_command() {
    string message = "/Выберете действие!\n"
                     "/ --Играть -- Показать последнюю игру --\n"
                     "/ -- Загрузить последнюю игру -- Прочитать правила --\n"
                     "/(/play  --  /show  --  /load  --  /read)\n";
    default_print(std::move(message));
}

void ConsoleInterface::print_exit_game() {
    string message = "/Вы вышли из режима игры!\n";
    default_print(std::move(message));
}

void ConsoleInterface::print_good_load() {
    string message = "/Игра успешно загружена!\n";
    default_print(std::move(message));
}

void ConsoleInterface::print_bad_load() {
    string message = "/Не удалось загрузить последнюю игру!\n"
                     "/Ее нет, или последняя игра уже пройдена!\n";
    default_print(std::move(message));
}

void ConsoleInterface::print_god_mode() {
    string message = "/Введите параметр:\n";
    default_print(std::move(message));
}

void ConsoleInterface::print_start_process() {
    string message = "/Вы запустили игру!\n";
    default_print(std::move(message));
}

void ConsoleInterface::print_end_process() {
    string message = "/Вы вышли из игры!\n"
                     "/До свидания!\n";
    default_print(std::move(message));
}

void ConsoleInterface::print_start_game1() {
    string message = "Вы начинаете путешествие в странных пещерах!\n"
                     "Для начала создадим вашего героя!\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_start_game2() {
    string message = "Теперь вы можете начинать свое путешествие!\n"
                     "||-----------------------------||\n"
                     "Вы попали в новую комнату!\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_end_game(int exp) {
    string message = "Там вы видите дверь, ведущую из этого лабиринта!\n"
                     "||-----------------------------||\n"
                     "Вы закончили игру с " + to_string(exp) + " опыта!\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_base_iteration() {
    string message = "Вы видите кого-то впереди, но не можете разглядеть кто это!\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_get_name() {
    string message = "Введите имя вашего героя:\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_get_room() {
    string message = "Введите, в какую комнату собираетесь пройти:\n"
                     "(left, right, top или bottom)\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_new_room(Side side) {
    string message = "Вы прошли в ";
    if (side == Side::RIGHT) message += "правую";
    if (side == Side::LEFT) message += "левую";
    if (side == Side::TOP) message += "верхнюю";
    if (side == Side::BOTTOM) message += "нижнюю";
    message += " комнату!\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_get_item_base() {
    string message = "Вы уже собирались идти дальше, как вдруг заметили,\n"
                     "что гоблин что-то сжимает в руках!!\n"
                     "Вы раздвигаете его безжизненные руки, и видите странный артефакт!\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_get_item_run() {
    string message = "Пока гоблин насмехался над вашим страхом, он случайно выронил странный артефакт,\n"
                     "который отлетел в вашу сторону!\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_get_sword() {
    string message = "Поднимая этот меч, вы видите как он слегка горит красным светом!\n"
                     "Используйте его в одной из следующих драк!\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_get_stick() {
    string message = "Беря в руки этот старый посох, покрытый инеем,\n"
                     "вы чувствуете холод по всему телу!\n"
                     "Используйте его в одной из следующих драк!\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_death() {
    string message = "Вы умерли! Игра начинается заново!\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_win(string name, int exp) {
    string message = "Вам удалось победить вашего соперника!\n"
                     "Гоблин " + name + " мертв!\n"
                     "Вы получили " + to_string(exp) + " опыта!\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_draw() {
    string message = "Вам не удалось победить, но и вас не удалось убить!\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_use_sword() {
    string message = "Вы достаете свой меч, и в ваших руках он начинает гореть красным пламенем!\n"
                     "Вы получите небольшой бонус к вашему опыту на время драки!\n"
                     "Теперь начинаете сражение!\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_use_stick_true(int exp) {
    string message = "Вы достаете ваш посох и чувствуете, как холод пронизывает комнату!\n"
                     "Сегодня удача на вашей стороне!\n"
                     "Гоблин настолько испугался холода, что убежал от драки!\n"
                     "Вы получили " + to_string(exp) + " опыта!\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_use_stick_false() {
    string message = "Вы достаете ваш посох и чувствуете, как холод пронизывает комнату!\n"
                     "Упс! Этот посох оказался обычной палкой!\n"
                     "Придется сражаться как обычно!\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_use_quest(int exp) {
    string message = "Вы сражаетесь не только для победы!\n"
                     "Вы хотите также доказать визирю, что достаточно сильны!\n"
                     "Поэтому перед сражением вы теряете " +
                        to_string(exp) + " опыта!\n"
                     "Теперь начинаете сражение!\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_pass_quest(int exp) {
    string message = "Так как вы победили гоблина,\n"
                     "Вы получаете опыт, обещанный визирем!\n"
                     "Вы получили " + to_string(exp) + " опыта!\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_boss_1() {
    string message = "~~  Хо - хо - хо! ~~\n"
                     "~~ Дальше тебе не пройти, если ты недостаточно умен! ~~\n"
                     "~~ Буль - буль - буль! ~~\n"
                     "~~ Для начала ответь мне, какое у тебя имя? ~~\n"
                     "~~ Буль - буль - буль! ~~\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_boss_2() {
    string message = "~~ Мда... Хоть это ты знаешь! ~~\n"
                     "~~ Теперь - буль - скажи мне, сколько опыта ты успел набрать?  ~~\n"
                     "~~ Ах да! Хо - хо - хо! ~~\n"
                     "~~ Ты же не можешь этого знать! ~~\n"
                     "~~ Властелин этих подземелий - буль -не дал тебе такую возможность! ~~\n"
                     "~~ Хмм - ну ты точно сможешь это подсчитать, если я скажу тебе, ~~\n"
                     "~~ сколько - буль -опыта у тебя было сначала! ~~\n"
                     "~~ Пять - хо - хо! ~~\n"
                     "~~ Ты пришел в эти пещеры таким слабым! ~~\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_boss_3() {
    string message = "~~ О! Правильный ответ! ~~\n"
                     "~~ Ого! А ты - буль - неплохо тут устроился! ~~\n"
                     "~~ Все - хо - хо - ответь мне на последний вопрос! ~~\n"
                     "~~ Как твои дела вообще? Живой или как? ~~\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_boss_weak(int exp) {
    string message = "~~ О! Правильный ответ! ~~\n"
                     "~~ Мда... Ты все еще слишком слаб, чтоб отсюда выбраться! ~~\n"
                     "~~ Оставлю тебя здесь... смотреть дальше как ты мучаешься ~~\n"
                     "Водяной достаточно насладился издевательствами над вами!\n"
                     "Вы получили " + to_string(exp) + " опыта!\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_boss_strong(int exp) {
    string message = "~~ Ну что - жу - буль - буль! ~~\n"
                     "~~ Похоже дела у тебя идут отлично! ~~\n"
                     "~~ Хо - хо! Наверное мне лучше оставить тебя в покое! ~~\n"
                     "Водяной достаточно насладился издевательствами над вами!\n"
                     "Вы получили " + to_string(exp) + " опыта!\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_boss_wrong_1() {
    string message = "~~  Хо - хо - хо! ~~\n"
                     "~~  Неправильный ответ! ~~\n"
                     "~~ Буль - буль - буль! ~~\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_boss_wrong_2() {
    string message = "~~ Хо - хо - хо! ~~\n"
                     "~~ Насколько же ты слабый в - буль - математике! ~~\n"
                     "~~ Старайся лучше! ~~\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_boss_wrong_3() {
    string message = "~~ Буль - буль - буль! ~~\n"
                     "~~ Боюсь что здесь может быть только один правильный ответ! ~~\n"
                     "~~ Воспользуйся логикой! ~~\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_fight() {
    string message = "(fight -- чтобы подраться; run -- чтобы убежать; use -- чтобы\n"
                     "использовать ваше особое оружие и подраться!)\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_fight_use() {
    string message = "(fight -- чтобы подраться; run -- чтобы убежать!)";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_run() {
    string message = "Вы бежите от драки!\n"
                     "Вы потеряли 3 опыта!\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_choice() {
    string message = "Выберете действие:\n"
                     "(talk -- чтобы поговорить с ним; run -- чтобы идти дальше)\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_goblin(std::string &name, int dam) {
    string message = "Вы встречаете гоблина!\n"
                     "Он злобно смотрит в вашу сторону, а потом говорит:\n"
                     "<< Моё имя " + name + ", и я убью тебя, а потом заберу твое золото! >>\n"
                     "<< Ведь я могу нанести тебе " + to_string(dam) +  " урона! >>\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_citizen(std::string &name, int exp) {
    string message = "Вам встретился дружелюбный житель подземелий!\n"
                     "Его имя " + name + "!\n"
                     "Он говорит вам:\n"
                     "$$ Приветствую вас! Наверное тяжело здесь находиться, давайте я вам помогу! $$\n"
                     "Он хочет поделится с вами своим опытом!\n"
                     "Вы получили " + to_string(exp) + " опыта\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_prisoner(std::string &name, int dam, int exp) {
    string message = "Вам встретился заблудившийся путешественник!\n"
                     "Уже никто не помнит как его зовут!\n"
                     "Он говорит вам:\n"
                     ":( Прошу помогите! Дайте воды... :(\n"
                     ":( А... У вас тоже ее нет! Тогда исполните мою последнюю просьбу... :(\n"
                     "Он просит вас отомстить его обидчику!\n"
                     "Вы получите " + to_string(exp) + " опыта, как только убьете гоблина, стоящего рядом!\n"
                     "Его имя " + name + " !\n"
                     "Он может нанести вам " + to_string(dam) +  " урона!\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_boss() {
    string message = "О нет!!!\n"
                     "Вы встретили огромного водяного!\n"
                     "Как вообще в этих пещерах оказался водяной?\n"
                     "Он не выглядит агрессивным, но насмехается над\n"
                     "вашими жалкими попытками выбраться из подземелий!\n"
                     "Он говорит, что сегодня у него хорошее настроение и\n"
                     "он хочет поиграть с вами!\n"
                     "Чтобы победить его вам надо правильно отвечать на его вопросы!\n"
                     "На этот раз убежать от драки не выйдет...\n"
                     "Водяной подползает к вам и говорит:\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_vizier(std::string &name) {
    string message = "Вам встретился визирь!\n"
                     "Её имя " + name + "!\n"
                     "Она говорит вам:\n"
                     "** Приветствую вас, путник! Не хотите ли вы пройти мое испытание? **\n"
                     "Вы получите особый артефакт!\n"
                     "Как только вы победите любого гоблина, вы получите бонус к опыту!\n"
                     "Но на время драки с ним, вы станете немного слабее!\n"
                     "(accept -- принять испытание; reject -- отклонить!)\n";
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::print_field(std::string map) {
    string message = "Вот путь из комнат, по которому вы двигались в подземелье:\n";
    message += map + '\n';
    save(message);
    default_print(std::move(message));
}

void ConsoleInterface::show(string&& path) {
    string message;
    ifstream file(path);
    while (!file.eof()) {
        getline(file, message);
        cout << '/' + message << std::endl;
    }
    file.close();
}