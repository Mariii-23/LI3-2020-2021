/**
 * @file config.h
 * @author Mariana Rodrigues, Matilde Bravo e Pedro Alves
 * @date 4 Maio 2021
 * @brief This Module is responsible to manipulated all information.
 */

#ifndef CONFIG_H
#define CONFIG_H
#include "model/state.h"

void read_config_to_state(STATE s, char *config_path);
#endif
