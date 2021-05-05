#ifndef CONFIG_H
#define CONFIG_H
typedef struct config *Config;
Config read_config(char *path_to_config);
void free_config(Config config);
#endif

