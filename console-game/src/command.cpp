#include "../command.h"

void Command::play(string&& path_save, string&& path_info) {
  ofstream file(path_save);
  file.close();
  Game game(interface);
  try {
    game.start_game();
    game.play();
    game.end_game();
  } catch (end_process&) {
    ofstream info(path_info);
    info << "READY_TO_LOAD" << std::endl;
    info << static_cast<long long>(game.level_) << std::endl;
    info << static_cast<long long>(game.user->get_exp()) << std::endl;
    info << game.user->get_name();
    info.close();
  }
  interface->print_exit_game();
}

void Command::read() {
  interface->print_info();
}

void Command::show(string&& path) {
  interface->show(std::move(path));
}

void Command::load(string&& path) {
  try {
    Game game(interface);
    game.download();
    interface->print_good_load();
    try {
      game.play();
      game.end_game();
    } catch (end_process &) {
      ofstream info(path);
      info << "READY_TO_LOAD" << std::endl;
      info << static_cast<long long>(game.level_) << std::endl;
      info << static_cast<long long>(game.user->get_exp()) << std::endl;
      info << game.user->get_name();
      info.close();
    }
    interface->print_exit_game();
  } catch (wrong_data&) {
    interface->print_bad_load();
  }
}

void Command::god_mode(string&& path_save, string&& path_info) {
  ofstream save(path_save);
  save.close();
  ofstream info(path_info);
  info << "READY_TO_LOAD" << std::endl;
  interface->print_god_mode();
  info << (interface->get_int()) << std::endl;
  interface->print_god_mode();
  info << (interface->get_int()) << std::endl;
  interface->print_get_name();
  info << (interface->get_int()) << std::endl;
  info.close();
}

void Command::execute() {
  interface->print_start_process();
  try {
    while (true) {
      interface->print_head_command();

      Commands_menu comm = interface->get_command_menu();
      if (comm == Commands_menu::PLAY) {
        play();
      } else if (comm == Commands_menu::SHOW) {
        show();
      } else if (comm == Commands_menu::LOAD) {
        load();
      } else if (comm == Commands_menu::READ) {
        read();
      } else if (comm == Commands_menu::ENTER_GOD_MODE) {
        god_mode();
        load();
      }
    }
  } catch (end_process&) {
    interface->print_end_process();
  }
}