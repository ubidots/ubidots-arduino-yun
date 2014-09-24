
token= arg[1]
DEVICEID = arg[2]


DataURL = " http://things.ubidots.com/api/v1.6/variables/" .. DEVICEID 

API_token = "\"X-Auth-Token: " .. token .. "\""


head1 = "\"Accept: application/json; indent=4\""
os.execute("echo GetMan >> /tmp/logtext.txt")
CMD_UPDATE_SENSOR =  'curl -i --header '.. head1 .. ' --header ' .. API_token .. ' -X GET ' .. DataURL
os.execute("echo ".. CMD_UPDATE_SENSOR ..">> /tmp/logtext.txt")
os.execute(CMD_UPDATE_SENSOR)			--update sensor datapoint

--Se puede armar un string largo para enviarse al lua y el identificarlo