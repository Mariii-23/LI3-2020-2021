#include "commands.h"
#include "model/state.h"
#include "controller/exec.h"

Variable print(Variable *args) {
  print_var(*args);
  return void_var();
}
