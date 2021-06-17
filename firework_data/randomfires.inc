new Float:RandomFireLocations[][4] = {

 //{X, Y, Z}|

{ 2229.0417,  -1721.8126,  13.1648 }, 
{ 2104.5578,  -1806.4731,  13.4187 }, 
{ 1554.3217,  -1675.6348,  15.4618 }, 
{ 1481.1184,  -1771.4932,  17.8664 },
{ 1941.8283,  -1772.9768,  14.3718 },
{ 2033.7408,  -1402.9357,  16.7153 },
{ 1173.7427,  -1323.5532,  13.7983 }, 
{ 1309.6440,  -1367.6197,  12.8191 },
{ 1367.5247,  -1280.3741,  13.4494 },
{ 1460.7166,  -1011.5853,  25.5572 }, 
{ 1836.2395,  -1682.3510,  12.7284 }, 
{ 1219.1232,  -1811.5850,  15.5281 }, 
{ 935.9383,  -1385.5076,  12.8860 }, 
{ 1038.1492,  -1340.4718,  13.0002 }, 
{ 1003.9698,  -898.4241,  42.4910 }, 
{ 1199.0413,  -918.3212,  42.6527 },
{ 2420.7453,  -1509.0039,  23.6245 }, 
{ 2232.7424,  -1333.6989,  23.5098 }, 
{ 2232.4335,  -1159.4355,  24.7508 },
{ 1567.6300,  -1894.7127,  12.8331 }, 
{ 1447.816, -2289.690, 13.622 },
{ 2307.164, -1642.985, 14.652 },
{ 862.530, -1252.124, 14.892 }, 
{ 2782.219, -1814.517, 11.745 }, 
{ 2371.641, -2134.402, 27.260 }, 
{ 2397.253, -1898.087, 13.622 }, 
{ 1413.382, -1699.106, 13.612 }, 
{ 1337.640, -1090.549, 26.729 }, 
{ 1173.541, -1307.865, 14.071 },
{ 1518.149, -1451.034, 13.800 },
{ 1351.162, -1756.498, 13.497 }, 
{ 2852.2368, -1357.7797, 11.0625 }, 
{ 813.6826, -1456.7595, 14.2284 },
{ 1831.93494, -1842.95215, 16.3203 }  
};

new RandomFireLocNames[][] = {
	"Front of Gym, Ganton",
	"The Well Stacked Pizza, Idlewood",
	"Los Santos Police Department, Pershing Square",
	"City Hall, Pershing Square",
	"Gas Station, Idlewood",
	"Country General Hospital",
	"All Saints Hospital, Market, Jefferson",
	"All Saints, Market",
	"Big Ammunation, DownTown",
	"Bank, Inter 45",
	"Alhambra, Idlewood",
	"Conference building area ",
	"Cluckin' Bell, All Saints",
	"Jim's Sticky Ring, All Saints",
	"Gas Station, Mulholland",
	"Burger Shot, Mulholland",
	"Cluckin' Bell, East-LS",
	"Church, Jefferson",
	"Motel, Jefferson",
	"Metropolitan ave building, ",
	"Terminal Entrance, Los Santos Airport",
	"Ten Green Bottles, Ganton",
	"Stage A, Movie Area, Rodeo",
	"Stadium, Ganton",
	"Storage area, Willow field",
	"Cluckin' Bell, Willow field",
	"Offices, Pershing Square",
	"Front of house, Downtown",
	"Garage of All Saints Hospital, Market",
	"Residential Obey Hangout, Downtown",
	"24/7 shop, Pershing Square",
	"Building, Santa Monica ",
	"House, Marina",
	"24/7 shop, Little Maxico"
};
	

forward RandomFire();
public RandomFire()
{
	new RandType = Random(3), 
		RandLoc = Random(34),
		string[128];
	new  
		Float:RFire_X = RandomFireLocations[RandLoc][0],
		Float:RFire_Y = RandomFireLocations[RandLoc][1],
		Float:RFire_Z = RandomFireLocations[RandLoc][2];

	CreateBuildingFire(RandType, RFire_X, RFire_Y, RFire_Z);
	format(string, sizeof(string), "FIRE ALARM: Please be careful around the %s", RandomFireLocNames[RandLoc]);
	SendClientMessageToAll(-1, string);
	return 1;	
}

CMD:startrf(playerid, params[])
{
	if(!IsPlayerAdmin(playerid)) return 1;
	RandomFire();
	return 1;
}

//Random fire burnout timer
forward RandomFireTimer(id);
public RandomFireTimer(id)
{
	if(FireInfo[id][F_Used] == 1)
	{
		if(Fire_Health[id] <= 1)
		{
			DestroyBuildingFire(id);
			SendClientMessageToAll(-1, "Fire burned itself out!");
		}
	}
	return 1;
}

