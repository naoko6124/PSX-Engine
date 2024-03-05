#pragma once

#include <psxpad.h>
#include <string.h>

#include <Engine/Input/spi.hpp>

static const char *const PAD_TYPEIDS[] = {
	"[UNKNOWN]",
	"MOUSE",
	"NEGCON",
	"IRQ10_GUN",
	"DIGITAL",
	"ANALOG_STICK",
	"GUNCON",
	"ANALOG",
	"MULTITAP",
	"[UNKNOWN]",
	"[UNKNOWN]",
	"[UNKNOWN]",
	"[UNKNOWN]",
	"[UNKNOWN]",
	"JOGCON",
	"CONFIG_MODE"};

enum Keys
{
	Up = 0x10,
	Right = 0x20,
	Down = 0x40,
	Left = 0x80,

	Select = 0x01,
	Start = 0x08,

	Triangle = 0x11,
	Circle = 0x21,
	Cross = 0x41,
	Square = 0x81,

	Test1 = 0x02,
	Test2 = 0x09
};

class Input
{
public:
	static void Init()
	{
		SPI_Init(&poll_cb);
	}

	static bool GetKey(Keys key)
	{
		switch (key)
		{
		case Keys::Up:
		case Keys::Right:
		case Keys::Down:
		case Keys::Left:
		case Keys::Select:
		case Keys::Start:
			return ((uint8_t)((0xFF - pad_buff[0][2]) & key) != 0);
			break;

		case Keys::Triangle:
		case Keys::Circle:
		case Keys::Cross:
		case Keys::Square:
		case Keys::Test1:
		case Keys::Test2:
			return ((uint8_t)((0xFF - pad_buff[0][3]) & (key - 0x01)) != 0);
			break;

		default:
			return false;
			break;
		}
		return false;
	}

private:
	static void poll_cb(uint32_t port, const volatile uint8_t *buff, size_t rx_len)
	{
		pad_buff_len[port] = rx_len;
		if (rx_len)
			memcpy((void *)pad_buff[port], (void *)buff, rx_len);

		PadResponse *pad = (PadResponse *)buff;

		if (
			rx_len &&
			((pad->prefix == 0x5a) || !(pad->prefix)) &&
			(pad->type == PAD_ID_DIGITAL))
		{
			if (pad_config_attempt[port] < 3)
			{
				send_pad_cmd(port, PAD_CMD_CONFIG_MODE, 0x01, 0x00, 0);
				send_pad_cmd(port, PAD_CMD_READ, 0x00, 0x00, &dualshock_init_cb);
			}
		}
		else
		{
			pad_config_attempt[port] = 0;
		}
	}

	static void dualshock_init_cb(uint32_t port, const volatile uint8_t *buff, size_t rx_len)
	{
		PadResponse *pad = (PadResponse *)buff;

		if (
			(rx_len < 2) ||
			(pad->prefix != 0x5a) ||
			(pad->type != PAD_ID_CONFIG_MODE))
		{
			pad_config_attempt[port]++;
			return;
		}

		send_pad_cmd(port, PAD_CMD_CONFIG_MODE, 0x01, 0x00, 0);
		send_pad_cmd(port, PAD_CMD_SET_ANALOG, 0x01, 0x02, 0);
		send_pad_cmd(port, PAD_CMD_INIT_PRESSURE, 0x00, 0x00, 0);
		send_pad_cmd(port, PAD_CMD_REQUEST_CONFIG, 0x00, 0x01, 0);
		send_pad_cmd(port, PAD_CMD_RESPONSE_CONFIG, 0xff, 0xff, 0);
		send_pad_cmd(port, PAD_CMD_CONFIG_MODE, 0x00, 0x00, 0);
	}

	static void send_pad_cmd(
		uint32_t port,
		PadCommand cmd,
		uint8_t arg1,
		uint8_t arg2,
		SPI_Callback callback)
	{
		SPI_Request *req = SPI_CreateRequest();

		req->len = 9;
		req->port = port;
		req->callback = callback;
		req->pad_req.addr = 0x01;
		req->pad_req.cmd = cmd;
		req->pad_req.tap_mode = 0x00;
		req->pad_req.motor_r = arg1;
		req->pad_req.motor_l = arg2;

		memset(
			req->pad_req.dummy,
			(cmd == PAD_CMD_REQUEST_CONFIG) ? 0xff : 0x00,
			4);
	}

public:
	static uint8_t pad_buff[2][34];
	static size_t pad_buff_len[2];
	static uint32_t pad_config_attempt[2];

};