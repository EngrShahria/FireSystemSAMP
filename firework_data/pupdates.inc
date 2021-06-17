
new Float:pHP[MAX_PLAYERS];
new KillBurnTimer[MAX_PLAYERS];

stock BurnPlayer(playerid)
{
	if(GetPlayerSkin(playerid) == 277 || GetPlayerSkin(playerid) == 278 || GetPlayerSkin(playerid) == 279)
	 return 0;
	if(InsideFire[playerid] == 1)
	{
		GetPlayerHealth(playerid, pHP[playerid]);
		SetPlayerAttachedObject(playerid, FIRE_OBJECT_SLOT, 18688, 2, -1, 0, -1.9, 0, 0);
		KillTimer(PlayerBurningTime[playerid]);
		PlayerBurningTime[playerid] = SetTimerEx("TogglePlayerBurn", 1000, 1, "d", playerid);
	}
	if(InsideFire[playerid] == 0)
	{
		KillBurnTimer[playerid] = SetTimerEx("PBurnKill", 5000, 0, "d", playerid);
	}
	return 1;
}

forward PBurnKill(playerid);
public PBurnKill(playerid)
{
	if(InsideFire[playerid] == 0)
	{
		KillTimer(PlayerBurningTime[playerid]);
		KillTimer(KillBurnTimer[playerid]);
		RemovePlayerAttachedObject(playerid, FIRE_OBJECT_SLOT);
	}
	return 1;
}

forward TogglePlayerBurn(playerid);
public TogglePlayerBurn(playerid)
{
	new Float:pHP2;
	GetPlayerHealth(playerid, pHP2);
	if(pHP2 < pHP[playerid])
	{
		pHP[playerid] = pHP2;
	}
	pHP[playerid] -= 2.0;
	SetPlayerHealth(playerid, pHP[playerid]);
}

public OnPlayerUpdate(playerid)
{
	if(InsideFire[playerid] == 0)
	{
		if(IsNearFire(playerid, FIRE_RADIUS_FOOT))
		{
			DebugMessage(playerid, "You are inside of the fire-zone.");
			InsideFire[playerid] = 1;
			BurnPlayer(playerid);
		}
	}

	if(InsideFire[playerid] == 1)
	{
		if(!IsNearFire(playerid, FIRE_RADIUS_FOOT))
		{
			DebugMessage(playerid, "You are out of the fire-zone.");
			InsideFire[playerid] = 0;
			BurnPlayer(playerid);
		}
	}
	return 1;
}



public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(PRESSED(KEY_FIRE) && IsNearFire(playerid, FIRE_RADIUS_FOOT+5) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && HoldingExtinguisher(playerid))
   	{
        new Float:pox, Float:poy, Float:poz;
		GetPlayerPos(playerid, pox, poy, poz);
		new FKeyID = NearFireID(playerid);
		if(IsPlayerAimingAt(playerid, FireInfo[FKeyID][FPos_X], FireInfo[FKeyID][FPos_Y], FireInfo[FKeyID][FPos_Z], FIRE_RADIUS_FOOT+2))
		{
			ExtinguishFire[FKeyID] = SetTimerEx("PuttingOutFire", 500, true, "ii", FKeyID, 1);
			DebugMessage(playerid, "Pressing/Holding fire key");
		}
	}	

	if(RELEASED(KEY_FIRE) && IsNearFire(playerid, FIRE_RADIUS_FOOT+5) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && HoldingExtinguisher(playerid))
   	{
		new FKeyID = NearFireID(playerid); 
		KillTimer(ExtinguishFire[FKeyID]);
		DebugMessage(playerid, "Released fire key");
	}
	if(PRESSED(KEY_FIRE) && IsNearFire(playerid, FIRE_RADIUS_CAR+5) && InsideWaterCar(playerid))
   	{
        new Float:pox, Float:poy, Float:poz;
		GetPlayerPos(playerid, pox, poy, poz);
		new FKeyID = NearFireID(playerid); 
		if(IsPlayerAimingAt(playerid, FireInfo[FKeyID][FPos_X], FireInfo[FKeyID][FPos_Y], FireInfo[FKeyID][FPos_Z], FIRE_RADIUS_CAR))
		{
			ExtinguishFire[FKeyID] = SetTimerEx("PuttingOutFire", 500, true, "ii", FKeyID, 2);
		}
		DebugMessage(playerid, "Pressing/Holding vehicle fire key.");
	}
	if(RELEASED(KEY_FIRE) && IsNearFire(playerid, FIRE_RADIUS_CAR+6) && InsideWaterCar(playerid))
   	{
		new FKeyID = NearFireID(playerid); 
		KillTimer(ExtinguishFire[FKeyID]);
		DebugMessage(playerid, "Released vehicle fire key");
	}
	return 1;
}