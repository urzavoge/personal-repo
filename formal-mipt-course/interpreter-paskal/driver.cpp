#include "driver.hh"
#include "parser.hh"



Driver::Driver() :
    trace_parsing(false),
    trace_scanning(false),
    location_debug(false),
    scanner(*this),
    parser(scanner, *this) {
    program = std::make_shared<Program>();
}


bool Driver::parse(const std::string& f) {
    file = f;
    // initialize location positions
    location.initialize(&file);
    scan_begin();
    parser.set_debug_level(trace_parsing);
    parser();
    program->execute_program();
    scan_end();
    return true;
}

void Driver::scan_begin() {
    scanner.set_debug(trace_scanning);
  if (file.empty () || file == "-") {
  } else {
    stream.open(file);

    scanner.yyrestart(&stream);
  }
}

void Driver::scan_end()
{
    stream.close();
}
