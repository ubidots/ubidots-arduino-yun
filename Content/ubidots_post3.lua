token = arg[1]
data1 = arg[2]
var1 = arg[3]
data2 = arg[4]
var2 = arg[5]
data3 = arg[6]
var3 = arg[7]

URL = "http://things.ubidots.com/api/v1.6/collections/values"
data ='[{"variable":"' .. var1 .. '", "value":' .. data1 .. '},{"variable":"' .. var2 .. '", "value":' .. data2 .. '},{"variable":"' .. var3 .. '", "value":' .. data3 .. '}]'
print(data)

-- Library to read command output
local io = require "io"

-- Load the http module
local http = require "socket.http"
http.TIMEOUT = 1

-- loading ltn12 and json libraries from luci framework
local ltn12 = require "luci.ltn12"
local json = require "luci.json"

local response_body = {}

local response, code, response_headers = http.request{
    url = URL,
    method = "POST",
    headers = {
      ['X-Auth-Token'] = token,
      ['Content-Type'] = "application/json",
      ['Content-Length'] = string.len(data)
    },
    source = ltn12.source.string(data),
    sink = ltn12.sink.table(response_body)
}

print("Status:", response)
print("HTTP code:", code)
print("Response headers:")
if type(response_headers) == "table" then
  for k, v in pairs(response_headers) do
    print(k, ":", v)
  end
else
  -- Would be nil, if there is an error
  print("Not a table:", type(response_headers))
end
print("Response body:")
if type(response_body) == "table" then
  print(table.concat(response_body))
else
  -- Would be nil, if there is an error
  print("Not a table:", type(response_body))
end
