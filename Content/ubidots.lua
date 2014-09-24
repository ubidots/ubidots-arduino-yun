--[[

    Yeelink - Lua Script to set sensor data to Yeelink server

    Copyright (C) 2013 edwin chen <edwin@dragino.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

]]--

API_Key = arg[1]
URL = " http://things.ubidots.com/api/v1.6/auth/token"

API_String = "\"X-Ubidots-ApiKey: " .. API_Key .. "\""
DataURL = URL

os.execute("echo start >> /tmp/logtext.txt")
CMD_UPDATE_SENSOR =  'curl -v -XPOST -H ' ..  API_String .. DataURL
os.execute("echo ".. CMD_UPDATE_SENSOR ..">> /tmp/logtext.txt")
os.execute(CMD_UPDATE_SENSOR)           --update sensor datapoint