#include "rdr2_main.hpp"
#include "../features/esp/esp.hpp"
#include "../Main.h"
#include "../MenuFunctions.h"
//#include "script.h"
//#include "keyboard.h"


#include <string>
#include <ctime>
//#include "Pattern.h"
#include <Psapi.h>

///#include "script.h"
//#include "keyboard.h"


#include <string>
#include <ctime>
///#include "Pattern.h"
#include <Psapi.h>
using namespace std;

#pragma warning(disable : 4244 4305) // double <-> float conversions

using namespace std;
#include "../MenuFunctions.h"

char* model;
HANDLE mainFiber;
DWORD wakeAt;


#include "rdr2_main.hpp"
#include "../features/esp/esp.hpp"
#pragma comment(lib, "winmm.lib")



static HANDLE main_fiber;
static DWORD time_to_wake_up;

void wait_for(DWORD ms) {
	time_to_wake_up = timeGetTime() + ms;
	SwitchToFiber(main_fiber);
}

void Main()
{
	addTitle("BGG Base");
	addSubmenuOption("Self Options", 2);
	addSubmenuOption("Players List", 3);
	addSubmenuOption("Vehicle Spawner", 5);
	addSubmenuOption("Credits", 7);

	normalMenuActions();
}



void Credits()
{

	addTitle("Credits");
	addOption("BiG_GHOST_GaMeR");
	addOption("2much4u");
	addOption("Lachie4145");
	addOption("Device9999 for fixing TEXT!");
	addOption("Device9999 for main base");
	addOption("Alwayskaffa for copy n pasting");

	normalMenuActions();


}



void Selfmenu()
{
	addTitle("Self Options");
	addOption("Herpes");

	normalMenuActions();
}


void PlayersList()
{
	addTitle("Players List");

	for (int i = 0; i < 30; i++)
	{
		addOption(PLAYER::GET_PLAYER_NAME(i));
	}
	if (optionPress && PLAYER::IS_PLAYER_PLAYING(currentOption - 1))
	{
		selectedPlayer = currentOption - 1;
		changeSubmenu(4);
	}
	normalMenuActions();
}



int SelectedClient;
void TeleportToClient(int Client)
{
	Vector3 Coords = ENTITY::GET_ENTITY_COORDS(Client, 1, 0);
	if (PED::IS_PED_SITTING_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID()))
		ENTITY::SET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), Coords.x, Coords.y, Coords.z, 1, 0, 0, 1);
	else
		ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), Coords.x, Coords.y, Coords.z, 1, 0, 0, 1);
}

void OnlinePlayerMods()
{
	addTitle(PLAYER::GET_PLAYER_NAME(selectedPlayer));
	addOption("Teleport To Player");

	if (getOption() == 1)
	{
		TeleportToClient(PLAYER::GET_PLAYER_PED(selectedPlayer));
		STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
	}

	normalMenuActions();
}

void VehSpawner()
{
	addTitle("Vehicle Spawner");
	addOption("PC Vehicles");

	if (getOption() == 1)
	{
		changeSubmenu(6);
	}

	normalMenuActions();
}

Vector3 obje;
Vector3 fff;


void Hook()
{
	optionCount = 0;



	if (submenu == 1)
	{
		Main();
	}
	else if (submenu == 2)
	{
		Selfmenu();
	}
	else if (submenu == 3)
	{
		PlayersList();
	}
	else if (submenu == 4)
	{
		OnlinePlayerMods();
	}
	else if (submenu == 5)
	{
		VehSpawner();
	}
	else if (submenu == 6)
	{
		bool bigdick = true;//PCCars();
	}
	else if (submenu == 7)
	{
		Credits();
	}


	optionPress = false;
	//wait_for(0);

}

void PreMonitorButtons()
{
	if (PressedButton == true)
	{
		wait_for(150);
		PressedButton = false;
	}
	monitorButtons();
	//wait_for(150);
}

void __stdcall fiber_thread(LPVOID params) {
	srand(GetTickCount());
	while (true) {

		PreMonitorButtons();
		//MenuControls();		
		wait_for(0);
	}
}


void on_tick() {
	if (!main_fiber)
		main_fiber = ConvertThreadToFiber(nullptr);

	if (time_to_wake_up > timeGetTime())
		return;

	static HANDLE fiber_handle = nullptr;
	if (fiber_handle) {
		SwitchToFiber(fiber_handle);
	}
	else {
		fiber_handle = CreateFiber(NULL, fiber_thread, nullptr);
	}
}



namespace hooks
{
	namespace globals
	{
		RECT resolution;
		uintptr_t base_address;
	}

	namespace original
	{
		is_dlc_present_fn o_is_dlc_present;
	}


	int __fastcall is_dlc_present_hook(__int64 a1, DWORD dlcHash) {

		on_tick();
		Hook();
		//features::c_esp().draw_players();


		return original::o_is_dlc_present(a1, dlcHash);
	}

	void initialize() {

		if (AllocConsole()) {
			freopen("CONIN$", "r", stdin);
			freopen("CONOUT$", "w", stdout);
			freopen("CONOUT$", "w", stderr);
		}
		printf("Cheat loaded!\n\n");
		globals::base_address = uintptr_t(GetModuleHandleA(0));
		auto hwnd_ = FindWindowA(0, "Red Dead Redemption 2");
		GetWindowRect(hwnd_, &globals::resolution);

		auto status = MH_Initialize();
		printf("init_status : %s\n", std::string(MH_StatusToString(status)).c_str());

		auto is_dlc_present = memory::find_signature(0, "\xE8\x45\x9C\x01\x00\x48\x8B", "xxxxxxx") - 0x1002; // DOES_CAM_EXIST
		printf("is_dlc_present: %I64X\n", is_dlc_present);

		status = MH_CreateHook((PVOID)is_dlc_present, is_dlc_present_hook, reinterpret_cast<void**>(&original::o_is_dlc_present));
		printf("create_status : %s\n", std::string(MH_StatusToString(status)).c_str());

		status = MH_EnableHook((PVOID)is_dlc_present);
		printf("enable_status : %s\n\n", std::string(MH_StatusToString(status)).c_str());

	}
}

