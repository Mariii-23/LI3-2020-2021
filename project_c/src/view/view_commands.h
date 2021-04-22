#ifndef VCOMMANDS_H
#define VCOMMANDS_H

#include "model/state.h"

// Comandos utilizados no programa
Variable print(Variable* args);
Variable quit(Variable* args);
Variable help(Variable* args);
Variable cmd_from_csv(Variable* args);
Variable show(Variable* args);

#endif
