
//Callbacks, hooks and other stuff

//Data for Fire per ID.
enum FireData
{
	F_ID, 
	F_Used,
	Float:FPos_X,
	Float:FPos_Y, 
	Float:FPos_Z,
	Fire_Smoke[3],
	Fire_Location 
}
new FireInfo[MAX_FIRES][FireData];


//Getting free FireID
stock GetFireSlot()
{
	for(new i=0; i< MAX_FIRES; i++)
	{
	    if(FireInfo[i][F_Used] == 0) return i;
	}
	return MAX_FIRES-1;
}

//Getting used FireID
stock UsedFireSlot()
{
	for(new i=0; i< MAX_FIRES; i++)
	{
	    if(FireInfo[i][F_Used] == 1) return i;
	}
	return 1;
	
}

forward CreateBuildingFire(firetype, Float:x, Float:y, Float:z);
public CreateBuildingFire(firetype, Float:x, Float:y, Float:z)
{

	new fireslot = GetFireSlot();

	FireInfo[fireslot][F_Used] = 1;
	FireInfo[fireslot][FPos_X] = x;
	FireInfo[fireslot][FPos_Y] = y;
	FireInfo[fireslot][FPos_Z] = z - Z_Extinguish;
	printf("%d used", fireslot);
	FireMapIcon[fireslot] = CreateDynamicMapIcon(FireInfo[fireslot][FPos_X], FireInfo[fireslot][FPos_Y], FireInfo[fireslot][FPos_Z], 20, 0);
	if(firetype == Small_Fire_Type)
	{
		CreateExplosion(FireInfo[fireslot][FPos_X], FireInfo[fireslot][FPos_Y], FireInfo[fireslot][FPos_Z], 11, 3);
		FireBurnoutTimerID[fireslot] = SetTimerEx("RandomFireTimer", 1140000, 0, "d", fireslot);


		FireObject[fireslot][0] = CreateDynamicObject(18691, FireInfo[fireslot][FPos_X], FireInfo[fireslot][FPos_Y], FireInfo[fireslot][FPos_Z], 0.0, 0.0, 0.0);
		Fire_Health[fireslot] = 100;
	}
	if(firetype == Medium_Fire_Type)
	{
		CreateExplosion(FireInfo[fireslot][FPos_X], FireInfo[fireslot][FPos_Y], FireInfo[fireslot][FPos_Z], 10, 5);
		FireBurnoutTimerID[fireslot] = SetTimerEx("RandomFireTimer", 2100000, 0, "d", fireslot);

		FireObject[fireslot][0] = CreateDynamicObject(18691, FireInfo[fireslot][FPos_X], FireInfo[fireslot][FPos_Y], FireInfo[fireslot][FPos_Z], 0.0, 0.0, 0.0);
		FireObject[fireslot][1] = CreateDynamicObject(18691, FireInfo[fireslot][FPos_X]+random(3), FireInfo[fireslot][FPos_Y]+random(3), FireInfo[fireslot][FPos_Z]+random(2), 0.0, 0.0, 0.0);
		FireObject[fireslot][2] = CreateDynamicObject(18691, FireInfo[fireslot][FPos_X]+random(3), FireInfo[fireslot][FPos_Y]+random(3), FireInfo[fireslot][FPos_Z]+random(2), 0.0, 0.0, 0.0);
		Fire_Health[fireslot] = 300;
	}
	if(firetype == Huge_Fire_Type)
	{
		CreateExplosion(FireInfo[fireslot][FPos_X], FireInfo[fireslot][FPos_Y], FireInfo[fireslot][FPos_Z], 7, 8);
		FireBurnoutTimerID[fireslot] = SetTimerEx("RandomFireTimer", 3300000, 0, "d", fireslot);

		FireObject[fireslot][0] = CreateDynamicObject(18691, FireInfo[fireslot][FPos_X], FireInfo[fireslot][FPos_Y], FireInfo[fireslot][FPos_Z], 0.0, 0.0, 0.0);
		FireObject[fireslot][1] = CreateDynamicObject(18691, FireInfo[fireslot][FPos_X]+random(5), FireInfo[fireslot][FPos_Y]+random(5), FireInfo[fireslot][FPos_Z]+random(2), 0.0, 0.0, 0.0);
		FireObject[fireslot][2] = CreateDynamicObject(18691, FireInfo[fireslot][FPos_X]+random(5), FireInfo[fireslot][FPos_Y]+random(5), FireInfo[fireslot][FPos_Z]+random(2), 0.0, 0.0, 0.0);
		FireObject[fireslot][3] = CreateDynamicObject(18691, FireInfo[fireslot][FPos_X]+random(5), FireInfo[fireslot][FPos_Y]+random(5), FireInfo[fireslot][FPos_Z]+random(2), 0.0, 0.0, 0.0);
		FireObject[fireslot][4] = CreateDynamicObject(18691, FireInfo[fireslot][FPos_X]+random(5), FireInfo[fireslot][FPos_Y]+random(5), FireInfo[fireslot][FPos_Z]+random(2), 0.0, 0.0, 0.0);
		Fire_Health[fireslot] = 500;
	}

}
forward DestroyBuildingFire(FID);
public DestroyBuildingFire(FID)
{
	DestroyDynamicObject(FireObject[FID][0]);
	DestroyDynamicObject(FireObject[FID][1]);
	DestroyDynamicObject(FireObject[FID][2]);
	DestroyDynamicObject(FireObject[FID][3]);
	DestroyDynamicObject(FireObject[FID][4]);

	DestroyDynamicMapIcon(FireMapIcon[FID]);
	//reset firedata
	FireInfo[FID][F_Used]= 0;
	FireInfo[FID][FPos_X] = 0;
	FireInfo[FID][FPos_Y] = 0;
	FireInfo[FID][FPos_Z] = 0;
	Fire_Health[FID] = 0;
	KillTimer(ExtinguishFire[FID]);
	KillTimer(FireBurnoutTimerID[FID]);
}

//Detect nearby FireID which is being used.
stock NearFireID(playerid)
{

	for(new f; f < MAX_FIRES; f++)
	{
		if (IsPlayerInRangeOfPoint(playerid, 10, FireInfo[f][FPos_X],FireInfo[f][FPos_Y],FireInfo[f][FPos_Z]))
		{
			return f;
		}
	}
	return 0;
}

//Detect if the player near a Fire
stock IsNearFire(playerid, Float:distance)
{
	for(new f; f < MAX_FIRES; f++)
	{
		if (IsPlayerInRangeOfPoint(playerid, distance, FireInfo[f][FPos_X],FireInfo[f][FPos_Y],FireInfo[f][FPos_Z]))
		{
			return 1;
		}
	}
	return 0;
}
 

stock InsideWaterCar(playerid)
{
	if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 407 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 601)
		return 1;
		
	return 0;
}

stock HoldingExtinguisher(playerid)
{
	if(GetPlayerWeapon(playerid) == 42 && !IsPlayerInAnyVehicle(playerid)) 
		return 1; 

	return 0;
}

//Fire Health update while player tries to put of fire.
forward PuttingOutFire(fireid, type);
public PuttingOutFire(fireid, type)
{
	new FireOutHealth;
	new playerid;
	if(type == 1) //Type 1 is when the player is using a extinguisher 
	{
		if(IsNearFire(playerid, FIRE_RADIUS_FOOT+6))
		{
			if(Fire_Health[fireid] < FireOutHealth)
			{
				Fire_Health[fireid] = FireOutHealth;
			}
			Fire_Health[fireid] -= 1; 
		}
	}

	if(type == 2)//Type 2 is when the player is using Fire-Vehicle
	{
		if(IsNearFire(playerid, FIRE_RADIUS_CAR+6))
		{
			if(Fire_Health[fireid] < FireOutHealth)
			{
				Fire_Health[fireid] = FireOutHealth;
			}
			Fire_Health[fireid] -= 5;
		}

	}

	if(Fire_Health[fireid] < 5 ) //It will update fire health, it's need, so ID don't get bugged.
	{
		KillTimer(ExtinguishFire[fireid]);
		DestroyBuildingFire(fireid);	
	}

}




new Fire_Cache[MAX_PLAYERS] = { -1, ... };
new Fire_CacheTime[MAX_PLAYERS];

stock AimingTowardFire(playerid)
{
	if(gettime() - Fire_CacheTime[playerid] < 1)
  	{
  	    return Fire_Cache[playerid];
 	}
 	Fire_CacheTime[playerid] = gettime();

	new id = -1;
	new Float:dist = 99999.99;
	new Float:dist2;
	new Float:px, Float:py, Float:pz;
	new Float:x, Float:y, Float:z, Float:a;
	GetXYInFrontOfPlayer(playerid, x, y, z, a, 1);
	z -= Z_Extinguish;

	new Float:cx,Float:cy,Float:cz,Float:fx,Float:fy,Float:fz;
	GetPlayerCameraPos(playerid, cx, cy, cz);
	GetPlayerCameraFrontVector(playerid, fx, fy, fz);

	for(new i; i < MAX_PLAYERS; i++)
	{
	    if(IsPlayerConnected(i) && (InsideWaterCar(playerid) || HoldingExtinguisher(playerid) ) && InsideFire[playerid] == 1)
	    {
	        GetPlayerPos(i, px, py, pz);

	        dis2 = DistanceCameraTargetToLocation(cx, cy, cz, px, py, pz, fx, fy, fz);
 	
	        if(dist2 < dist)
	        {
				dist = dist2;
	    		id = i;

			}
		}
	}
	if(id != -1) return id-MAX_PLAYERS;

	for(new i; i < MAX_FIRES; i++)
	{
		if(FireInfo[i][Fire_Used])
		{
		    if(InsideWaterCar(playerid) || HoldingExtinguisher(playerid) )
		    {
				dis2 = DistanceCameraTargetToLocation(cx, cy, cz, Fire[i][Fire_X], Fire[i][Fire_Y], Fire[i][Fire_Z]+Z_DIFFERENCE, fx, fy, fz);

				if((IsPlayerInAnyVehicle(playerid) && dist2 < CAR_RADIUS && dist2 < dist) || (!IsPlayerInAnyVehicle(playerid) && ((dis2 < FIRE_RADIUS_FOOT && dis2 < dis))))
				{
				    dis = dis2;
				    id = i;
				}
			}
		}
	}
	if(id != -1)
	{
		if
		(
			(
				IsPlayerInAnyVehicle(playerid) && !IsPlayerInRangeOfPoint(playerid, 50, Fire[id][Fire_X], Fire[id][Fire_Y], Fire[id][Fire_Z])
			)
			||
			(
				!IsPlayerInAnyVehicle(playerid)  && !IsPlayerInRangeOfPoint(playerid, 5, Fire[id][Fire_X], Fire[id][Fire_Y], Fire[id][Fire_Z])
			)
		)
		else 
		{
		 id = -1; 
		}
	}
	Fire_Cache[playerid] = id;
	return id;
}

stock DebugMessage(playerid, string[128])
{
	new text[128];
	format(text, sizeof(text), "DEBUG: %s", string);
	if(IsPlayerAdmin(playerid))
	{
		SendClientMessage(playerid, -1, text);
	}
	return 0;
}