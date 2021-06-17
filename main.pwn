#include <a_samp>
#include <streamer>
#include <foreach>
#include <sscanf2>
#include <ZCMD>
#include <YSI\y_timers>
//varribles

#define MAX_FIRES 5 //Max fire to be excutedF_Used highly
#define FIRE_AREA 1.2 //Get too close to burn yourself.
#define FIRE_RADIUS_FOOT 5.0		// radius in which you can extinguish the fire by foot
#define FIRE_RADIUS_CAR 15.0			// radius in which you can extinguish the fire by firetruck/SWAT Van
#define Z_Extinguish 2.5			// height which is used for technical accurancy of extinguishing. Please do not change
#define FIRE_OBJECT_SLOT 1			// the slot used with SetPlayerAttachedObject and RemovePlayerAttachedObject

new 
	FireObject[MAX_FIRES][5],
	Fire_Health[MAX_FIRES],
	FireMapIcon[MAX_FIRES]
	;
//Timers
new
	PlayerBurningTime[MAX_PLAYERS],
	ExtinguishFire[MAX_FIRES],
	FireBurnoutTimerID[MAX_FIRES];

new InsideFire[MAX_PLAYERS];

#define Huge_Fire_Type 1
#define Medium_Fire_Type 2
#define Small_Fire_Type 3

#include "firework_data/special_callbacks.inc" 
#include "firework_data/main_data.inc" //Everything about the system
#include "firework_data/pupdates.inc" //All effects to player only

OnFilterScriptInit()
{
	printf("Starting the fire system script");
	return 1;
}

OnFilterScriptExit()
{
	printf("Closing the fire system script");

	return 1;
}

public OnPlayerConnect(playerid)
{
	KillTimer(PlayerBurningTime[playerid]);
	KillTimer(KillBurnTimer[playerid]);
	return 1;
}


#include "firework_data/commands.inc"
#include "firework_data/randomfires.inc"