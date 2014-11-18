token= arg[1]
DEVICEID = arg[2]

URL = "http://things.ubidots.com/api/v1.6/variables/" .. DEVICEID .."/values?page_size=1"
-- Library to read command output
local io = require "io"

-- Load the http module
local http = require "socket.http"

-- loading ltn12 and json libraries from luci framework
local ltn12 = require "luci.ltn12"
local json = require "luci.json"

local response_body = {}
local response, code, response_headers = http.request{
    url=URL,
    method = "GET",
    headers = {
      ['X-Auth-Token'] = token
    },
    redirect = true,
    sink = ltn12.sink.file(io.stdout)
}
