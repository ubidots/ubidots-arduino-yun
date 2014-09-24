
data = arg[1]
token= arg[2]
DEVICEID = arg[3]


URL = " http://things.ubidots.com/api/v1.6/variables/"
DataURL = URL .. DEVICEID .. "/values"

API_token = "\"X-Auth-Token: " .. token .. "\""

value = "\'{\"value\":".. data .."}\'"

head1 = "\"Accept: application/json; indent=4\""
head2 = "\"Content-Type: application/json\""
os.execute("echo postman >> /tmp/logtext.txt")
CMD_UPDATE_SENSOR =  'curl -i --header '.. head1 .. ' --header ' .. head2 .. ' --header ' .. API_token .. ' -X POST -d ' .. value .. DataURL
os.execute("echo ".. CMD_UPDATE_SENSOR ..">> /tmp/logtext.txt")
os.execute(CMD_UPDATE_SENSOR)			--update sensor datapoint

--Se puede armar un string largo para enviarse al lua y el identificarlo