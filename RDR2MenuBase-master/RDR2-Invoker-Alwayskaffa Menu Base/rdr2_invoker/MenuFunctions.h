#pragma once
#pragma once

//#include "../rdr2_invoker/main/rdr2_main.hpp"
///#include "../features/esp/esp.hpp"

///////////////////////
//menu bools
int submenu = 1;
int submenuLevel;
int lastSubmenu[20];
int lastOption[20];
bool showCoords;
bool showInfos;
bool newTimerTick = true;
int maxTimerCount;
int currentOption;
int optionCount;
bool optionPress = false;
int selectedPlayer;
bool test = false;

float titlex = 0.745f;
float titlebox = 0.845f;
float menutext = 0.745f;
float backx = 0.845f;
bool centerd = false;
int width = 30;


int titleTextRed = 255;
int titleTextGreen = 255;
int titleTextBlue = 255;
int titleTextOpacity = 255;
/////////////////////////////
int menutextcolor[4] = { titleTextRed, titleTextGreen, titleTextBlue, titleTextOpacity };
int titleTextFont = 7;
int titleRectRed = 20;
int titleRectGreen = 20;
int titleRectBlue = 20;
int titleRectOpacity = 255;//
/////////////////////////
int backgroundRed = 15;
int backgroundGreen = 15;
int backgroundBlue = 15;
int backgroundOpacity = 220;
////////////////////////////////
int optionsRed = 255;
int optionsGreen = 255;
int optionsBlue = 255;
int optionsOpacity = 255;
int optionsFont = 6;
/////////////////////////////
int scrollerRed = 220;
int scrollerGreen = 220;
int scrollerBlue = 220;
int scrollerOpacity = 190;
/////////////////////////////
int highlightRed = 49;
int highlightGreen = 65;
int highlightBlue = 185;
int highlightOpacity = 255;
//////////////////////////////
int indicatorRed = 255;//
int indicatorGreen = 44;//
int indicatorBlue = 55;
int indicatorOpacity = 255;
///////////////////////////////




#pragma region Option Helpers
/*
void drawNotification(char* msg)
{

	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(msg);
	UI::_DRAW_NOTIFICATION(2000, 1);
}
*/

void drawText(const char* text, int font, float x, float y, float scalex, float scaley, int r, int b, int g, int a, bool center)
{
	rendering::c_renderer::get()->draw_text(x, y, 24.0f, text, r, g, b, a);


}

void drawTitleText(const char* text, int font, float x, float y, float scalex, float scaley, int r, int b, int g, int a, bool center)
{
	rendering::c_renderer::get()->draw_text(x, y, 96.0f, text, r, g, b, a);
}


void changeSubmenu(int newSubmenu)
{
	lastSubmenu[submenuLevel] = submenu;
	lastOption[submenuLevel] = currentOption;
	currentOption = 1;
	submenu = newSubmenu;
	submenuLevel++;
}
void SetupTimer(int tickTime)
{
	if (newTimerTick) {
		//maxTimerCount = GAMEPLAY::GET_GAME_TIMER() + tickTime;
		newTimerTick = false;
	}
}
bool IsTimerReady()
{
	//return GAMEPLAY::GET_GAME_TIMER() > maxTimerCount;
}
void ResetTimer()
{
	newTimerTick = true;
}


//////////////////////////////////
/*
void DRAW_TEXTURE(string Streamedtexture, string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
{
	if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED((char*)Streamedtexture.c_str()))
	{
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT((char*)Streamedtexture.c_str(), false);
	}
	else
	{
		GRAPHICS::DRAW_SPRITE((char*)Streamedtexture.c_str(), (char*)textureName.c_str(), x, y, width, height, rotation, r, g, b, a);
	}
}
*/


void addTitle(const char* title)
{

	
	drawTitleText(title, titleTextFont, titlex, 0.09f, 0.75f, 0.75f, titleTextRed, titleTextGreen, titleTextBlue, titleTextOpacity, true);
	GRAPHICS::DRAW_RECT(titlebox, 0.1175f, 0.23f, 0.085f, indicatorRed, indicatorGreen, indicatorBlue, 255, 0, 0);
	//DRAW_TEXTURE("CommonMenu", "interaction_bgd", titlebox, 0.1175f, 0.23f, 0.085f, 180, indicatorRed, indicatorGreen, indicatorBlue, 255);//gradient blue rect
}

void addOption(const char* option)
{
	optionCount++;
	if (currentOption <= 16 && optionCount <= 16)
		drawText(option, optionsFont, menutext, (optionCount * 0.035f + 0.130f), 0.5f, 0.5f, optionsRed, optionsGreen, optionsBlue, optionsOpacity, centerd);

	else if ((optionCount > (currentOption - 16)) && optionCount <= currentOption)
		drawText(option, optionsFont, menutext, ((optionCount - (currentOption - 16)) * 0.035f + 0.130f), 0.5f, 0.5f, optionsRed, optionsGreen, optionsBlue, optionsOpacity, centerd);
}

bool rightPress = false;
bool leftPress = false;
void addIntOption(char* option, int* var, int min, int max)
{
	char buf[100];
	_snprintf(buf, sizeof(buf), "%s < %i >", option, *var);
	addOption(buf);
	if (currentOption == optionCount)
	{
		if (rightPress)
		{
			if (*var >= max)
				*var = min;
			else
				*var = *var + 1;
			rightPress = false;
		}
		else if (leftPress)
		{
			if (*var <= min)
				*var = max;
			else
				*var = *var - 1;
			leftPress = false;
		}
	}
}

bool rightPress1 = false;
bool leftPress1 = false;
void addArrayOption(char* test, int* var, int min, int max)
{//var = pointer to array
	addOption(test);
	if (currentOption == optionCount)
	{
		if (rightPress1)
		{
			if (*var >= max)
				*var = min;
			else
				*var = *var + 1;
			rightPress1 = false;
		}
		else if (leftPress1)
		{
			if (*var <= min)
				*var = max;
			else
				*var = *var - 1;
			leftPress1 = false;
		}
	}
}

bool rightPress2 = false;
bool leftPress2 = false;
void addFloatOption(const char* option, float* var, int min, int max)
{
	char buf[100];
	_snprintf(buf, sizeof(buf), "%s < %f >", option, *var);
	addOption(buf);
	if (currentOption == optionCount)
	{
		if (rightPress2)
		{
			if (*var >= max)
				*var = min;
			else
				*var = *var + 0.01f;
			rightPress = false;
		}
		else if (leftPress2)
		{
			if (*var <= min)
				*var = max;
			else
				*var = *var - 0.01f;
			leftPress = false;
		}
	}
}

int getOptionint()
{
	return currentOption;
}


void addSubmenuOption(const char* option, int newSubmenu)
{
	addOption(option);
	if (currentOption == optionCount && optionPress)
		changeSubmenu(newSubmenu);
}

int getOption()
{
	if (optionPress)
	{
		return currentOption;
	}
	else return 0;
}

bool getKeyPressed(int key) {
	return (GetAsyncKeyState(key) & 0xFFFF) == 0x8001;
}

char* SoundToPlay;
char* SoundSetToPlay;
bool PlaySounds;

/*
void PlaySoundz(char* SoundName, char* SoundSetName)
{
	AUDIO::PLAY_SOUND_FRONTEND(-1, SoundName, SoundSetName, 1);
}
*/

int DelayCounter = GetTickCount();
bool firstopenmenu = false;
bool PressedButton;
void monitorButtons()
{
	//if (GetTickCount() - DelayCounter > 150)
	//{
	if (submenu == 0)
	{
		if ((GetAsyncKeyState(VK_NUMPAD7) & 0x8000) && submenu == 0) //||// (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_SCRIPT_LB) && CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_SCRIPT_PAD_DOWN)) && submenu == 0)
		{
			DelayCounter = GetTickCount();
			submenu = 1;
			submenuLevel = 0;
			currentOption = 1;
			//SoundToPlay = "FLIGHT_SCHOOL_LESSON_PASSED";
			///SoundSetToPlay = "HUD_AWARDS";
			///PlaySounds = true;
			PressedButton = true;
		}
		ResetTimer();
	}
	else {

		if ((GetAsyncKeyState(VK_NUMPAD9) & 0x8000) && submenu != 0) //|| CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_CANCEL) && submenu != 0)//exit
		{
			DelayCounter = GetTickCount();
			if (submenu == 1)
			{
				submenu = 0;
				PressedButton = true;
			}
			else {
				submenu = lastSubmenu[submenuLevel - 1];
				currentOption = lastOption[submenuLevel - 1];
				submenuLevel--;
				PressedButton = true;
			}
			//SoundToPlay = "BACK";
			//SoundSetToPlay = "HUD_FRONTEND_DEFAULT_SOUNDSET";
			//PlaySounds = true;
		}
		else if ((GetAsyncKeyState(VK_NUMPAD5) & 0x8000) && submenu != 0) //||CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_ACCEPT) && submenu != 0)//option select
		{
			DelayCounter = GetTickCount();
			optionPress = true;
			//SoundToPlay = "SELECT";
			//SoundSetToPlay = "HUD_FRONTEND_DEFAULT_SOUNDSET";
			//PlaySounds = true;
			PressedButton = true;
		}
		else if ((GetAsyncKeyState(VK_NUMPAD8) & 0x8000) && submenu != 0) ///||// CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_UP) && submenu != 0)//up
		{
			DelayCounter = GetTickCount();

			currentOption--;
			currentOption = currentOption < 1 ? optionCount : currentOption;
			//SoundToPlay = "NAV_UP_DOWN";
			//SoundSetToPlay = "HUD_FRONTEND_DEFAULT_SOUNDSET";
			//PlaySounds = true;
			PressedButton = true;
		}
		else if ((GetAsyncKeyState(VK_NUMPAD2) & 0x8000) && submenu != 0) //|| //CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_DOWN) && submenu != 0)//down
		{
			DelayCounter = GetTickCount();
			currentOption++;
			currentOption = currentOption > optionCount ? 1 : currentOption;
			//SoundToPlay = "NAV_UP_DOWN";
			//SoundSetToPlay = "HUD_FRONTEND_DEFAULT_SOUNDSET";
			//PlaySounds = true;
			PressedButton = true;
		}
		else if ((GetAsyncKeyState(VK_NUMPAD4) & 0x8000) && submenu != 0)//|| //CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_CELLPHONE_LEFT))//down
		{
			leftPress = true;
			//SoundToPlay = "NAV_UP_DOWN";
			//SoundSetToPlay = "HUD_FRONTEND_DEFAULT_SOUNDSET";
			//PlaySounds = true;
			PressedButton = true;
		}
		else if ((GetAsyncKeyState(VK_NUMPAD6) & 0x8000) && submenu != 0)//|| //CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_CELLPHONE_RIGHT))//down
		{
			rightPress = true;
			//SoundToPlay = "NAV_UP_DOWN";
			///SoundSetToPlay = "HUD_FRONTEND_DEFAULT_SOUNDSET";
			//PlaySounds = true;
			PressedButton = true;
		}
	}
}
void normalMenuActions()
{
	/*
	UI::HIDE_HELP_TEXT_THIS_FRAME();
	CAM::SET_CINEMATIC_BUTTON_ACTIVE(0);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(10);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(6);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(7);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(9);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(8);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_NEXT_CAMERA, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_PHONE, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_VEH_CIN_CAM, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_SELECT_CHARACTER_FRANKLIN, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_SELECT_CHARACTER_MICHAEL, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_SELECT_CHARACTER_TREVOR, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_SELECT_CHARACTER_MULTIPLAYER, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_CHARACTER_WHEEL, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_LIGHT, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_HEAVY, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_ALTERNATE, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MULTIPLAYER_INFO, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MAP_POI, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_PHONE, true);
	*/

	if (optionCount > 16)
	{
		GRAPHICS::DRAW_RECT(backx, (((16 * 0.035f) / 2) + 0.159f), 0.23f, (16 * 0.035f), backgroundRed, backgroundGreen, backgroundBlue, backgroundOpacity, 0, 0); //Background
		if (currentOption > 16)
		{
			GRAPHICS::DRAW_RECT(backx, ((16 * 0.035f) + 0.1415f), 0.23f, 0.035f, scrollerRed, scrollerGreen, scrollerBlue, scrollerOpacity, 0, 0); //Scroller

			GRAPHICS::DRAW_RECT(backx, 0.156f, 0.23f, 0.005f, indicatorRed, indicatorGreen, indicatorBlue, indicatorOpacity, 0, 0); //Up Indicator
		}
		else
		{
			GRAPHICS::DRAW_RECT(backx, ((currentOption * 0.035f) + 0.1415f), 0.23f, 0.035f, scrollerRed, scrollerGreen, scrollerBlue, scrollerOpacity, 0, 0); //Scroller

			GRAPHICS::DRAW_RECT(backx, 0.156f, 0.23f, 0.005f, indicatorRed, indicatorGreen, indicatorBlue, indicatorOpacity, 0, 0); //Up Indicator
		}
		if (currentOption != optionCount)
		{
			GRAPHICS::DRAW_RECT(backx, 0.721f, 0.23f, 0.005f, indicatorRed, indicatorGreen, indicatorBlue, indicatorOpacity, 0, 0); //Down Indicator
		}
	}
	else
	{
		GRAPHICS::DRAW_RECT(backx, (((optionCount * 0.035f) / 2) + 0.159f), 0.23f, (optionCount * 0.035f), backgroundRed, backgroundGreen, backgroundBlue, backgroundOpacity, 0, 0); //Background

		GRAPHICS::DRAW_RECT(backx, ((currentOption * 0.035f) + 0.1415f), 0.23f, 0.035f, scrollerRed, scrollerGreen, scrollerBlue, scrollerOpacity, 0, 0); //Scroller
	}

}

void addBoolOption(char* option, bool b00l, char* text, bool meg = false)
{
	if (meg)
	{
		///drawNotification(text);
	}
	char buf[30];
	if (b00l)
	{
		_snprintf(buf, sizeof(buf), "%s ~b~ON", option);
		addOption(buf);
	}
	else
	{
		_snprintf(buf, sizeof(buf), "%s ~r~OFF", option);
		addOption(buf);
	}
}

void addNotifyOption(char* option, char* notification)
{
	addOption(option);
	if (currentOption == optionCount && optionPress)
	{
		///drawNotification(notification);
	}
}


char* StringToChar(std::string string)
{
	return _strdup(string.c_str());
}

void MenuRun()
{
	monitorButtons();
	optionPress = false;
}


int Messages = 0;
bool SpawnedPedHasGodmode[20];
