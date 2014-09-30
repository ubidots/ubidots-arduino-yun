
data1 = arg[1]
token= arg[2]
DEVICEID1 = arg[3]
data2 = arg[4]
DEVICEID2 = arg[5]
data3 = arg[6]
DEVICEID3 = arg[7]

URL = " http://things.ubidots.com/api"
DataURL = URL ..  "/v1.6/collections/values"

API_token = "\"X-Auth-Token: " .. token .. "\""


values = "\'[{\"variable\":\"".. DEVICEID1 .."\", \"value\":".. data1 .."}, {\"variable\": \"".. DEVICEID2 .."\", \"value\":".. data2 .."}, {\"variable\":\"".. DEVICEID3 .."\", \"value\":".. data3 .."}]\'"                    

head1 = "\"Accept: application/json; indent=4\""
head2 = "\"Content-Type: application/json\""
os.execute("echo postman >> /tmp/logtext.txt")
CMD_UPDATE_SENSOR =  'curl -i --header '.. head1 .. ' --header ' .. head2 .. ' --header ' .. API_token .. ' -X POST -d ' .. values .. DataURL
os.execute("echo ".. CMD_UPDATE_SENSOR ..">> /tmp/logtext.txt")
os.execute(CMD_UPDATE_SENSOR)			--update sensor datapoint

--Se puede armar un string largo para enviarse al lua y el identificarlo

