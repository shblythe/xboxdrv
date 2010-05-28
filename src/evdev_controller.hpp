/*
**  Xbox360 USB Gamepad Userspace Driver
**  Copyright (C) 2010 Ingo Ruhnke <grumbel@gmx.de>
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef HEADER_XBOXDRV_EVDEV_CONTROLLER_HPP
#define HEADER_XBOXDRV_EVDEV_CONTROLLER_HPP

#include <linux/input.h>
#include <string>
#include <map>
#include <vector>

#include "xboxmsg.hpp"
#include "xbox_generic_controller.hpp"

class EvdevController : public XboxGenericController
{
private:
  int m_fd;
  std::string m_name;

  typedef std::map<int, XboxAxis> AbsMap;
  AbsMap m_absmap;

  typedef std::map<int, XboxButton> KeyMap;
  KeyMap m_keymap;

  std::vector<struct input_absinfo> m_absinfo;

public:
  EvdevController(const std::string& filename, 
                  const std::map<int, XboxAxis>&   AbsMap,
                  const std::map<int, XboxButton>& KeyMap);

  void set_rumble(uint8_t left, uint8_t right);
  void set_led(uint8_t status);

  /** @param timeout   timeout in msec, 0 means forever */
  bool read(XboxGenericMsg& msg, bool verbose, int timeout);

private:
  bool apply(XboxGenericMsg& msg, const struct input_event& ev);

private:
  EvdevController(const EvdevController&);
  EvdevController& operator=(const EvdevController&);
};

#endif

/* EOF */
