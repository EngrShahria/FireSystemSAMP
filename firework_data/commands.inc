CMD:createfire(playerid, params[])
{
	if(!IsPlayerAdmin(playerid)) return 1;

	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	CreateBuildingFire(Huge_Fire_Type, x, y, z);
	return 1;
}

CMD:locatefire(playerid, params[])
{
	if(!IsPlayerAdmin(playerid)) return 1;
	new string[128];
	new fid = NearFireID(playerid);

	format(string, sizeof(string), "You are near of %d", fid);
	SendClientMessage(playerid, -1, string);

	return 1;
}

CMD:destroyfire(playerid, params[])
{
	if(!IsPlayerAdmin(playerid)) return 1;
	new string[128];
	new fid = NearFireID(playerid);
	format(string, sizeof(string), "You are near of %d and destroyed", fid);
	DestroyBuildingFire(fid);
	SendClientMessage(playerid, -1, string);

	return 1;
}

CMD:firehealth(playerid, params[])
{
	if(!IsPlayerAdmin(playerid)) return 1;
	new string[128];
	new fid = NearFireID(playerid);
	format(string, sizeof(string), "Fire health is now %d", Fire_Health[fid]);
	SendClientMessage(playerid, -1, string);
	return 1;
}