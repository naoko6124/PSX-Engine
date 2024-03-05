#include <Engine/Input/Input.hpp>

uint8_t Input::pad_buff[2][34];
size_t Input::pad_buff_len[2];
uint32_t Input::pad_config_attempt[2] = {0, 0};