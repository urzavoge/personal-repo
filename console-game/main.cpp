#include "command.h"

int main() {
  setlocale(LC_ALL, "Russian");
  auto interface = new ConsoleInterface();
  Command app(interface);
  app.execute();
  delete interface;
  return 0;
}
