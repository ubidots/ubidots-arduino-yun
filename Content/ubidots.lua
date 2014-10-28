API_Key = arg[1]
URL = "http://things.ubidots.com/api/v1.6/auth/token"
-- Library to read command output
local io = require "io"

-- Load the http module
local http = require "socket.http"

-- loading ltn12 and json libraries from luci framework
local ltn12 = require "luci.ltn12"
local json = require "luci.json"
local response, code, response_headers = http.request{
    url=URL,
    method = "POST",
    headers = {
      ['X-Ubidots-ApiKey'] = API_Key
    },
    redirect = true,
    sink = ltn12.sink.file(io.stdout)
}
