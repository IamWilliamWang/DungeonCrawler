#ifndef MENUINTERFACE_H
#define MENUINTERFACE_H
#include <iostream>
#include <iomanip>
#include <limits>
#include "game.h"
#include "testingsettings.h"
#include "character.h"
#include "dungeon.h"
#include "basicdungeon.h"
#include "dungeonbuilder.h"

namespace core {

/**
 * @brief The MenuInterface class encapsulates all user interaction with the game.
 *
 * It maintains a basic event loop that:
 * 1) Displays the *current* menu
 * 2) Waits for user input
 * 3) Processes the user input
 *
 * Menus are implemented as pairs of functions:
 *   display...Menu()
 *   process...Selection(char selection)
 * The former displays the possible selections to the user, while the latter
 * processes the user input specific to that menu.
 *
 * There are already some helper functions implemented (or provided as skeletons)
 * for warning the user of invalid input, confirming a user's choice, pausing
 * until the user hits [Enter] on the keyboard.
 *
 * There are also a couple of implemented functions that should not be touched
 * as they are used for testing or in the core loop.
 *
 * NOTE: The base functionality has been implemented along with an example menu
 * transition. The remainder of the suggested skeleton functions will need to
 * be implemented (including return types and/or parameters) or replaced with
 * your own. You do not have to use the provided structure, although it may
 * simplify things for you if you do.
 */
class MenuInterface {
public:
  MenuInterface(std::ostream &display, std::istream &input);
  /**
   * @brief displayWelcome display an intial welcome message including the
   * student's name and game title.
   *
   * Note: set the author name and game title using the macro definitions in main.cpp
   *
   * @param author the name of the student
   * @param title the name of the game
   */
  void displayWelcome(const std::string &author, const std::string &title) const;

  /**
   * @brief run Executes the main event loop
   */
  void run();

private:
  /**
   * @brief The Menu enum identifies the menus the interface can display/process.
   */
  enum class Menu { Main, DungeonSelect, CharacterDetails, Action, Combat };

  std::ostream &_display; ///< the stream to pass all display output to
  std::istream &_input;   ///< the stream to read all input from
  Menu _currentMenu;      ///< keeps track of the current menu being displayed/processed

  /**
   * @brief displayMenu write the current menu to the display device
   */
  void displayMenu() const;

  /**
   * @brief processSelection process the selection for the current menu.
   * @param selection the single character selection.
   * @return true to continue the program, false to quit.
   */
  bool processSelection(char selection);

  /**
   * @brief getCharacterInput get a single character input from the input device
   * and clear the buffer until the next newline character.
   * @return the character input.
   */
  char getCharacterInput() const;

  /**
   * @brief getIntInput get a single integer from the input device and clear the
   * buffer until the next newline character. Will reprompt if retrieving an
   * integer fails.
   * @return the integer input
   */
  int getIntInput() const;

  /**
   * @brief warnSelectionInvalid Warns the user of an invalid menu selection
   * @param selection the character that was selected
   */
  void warnSelectionInvalid(char selection) const;

  /**
   * @brief setMenu switches the menu interface state to the specified menu.
   * @param newMenu the menu to be displayed
   */
  void setMenu(Menu newMenu);

  /**
   * @brief displayMainMenu write the main menu to the display device.
   */
  void displayMainMenu() const;

  /**
   * @brief processMainMenuSelection process the selection for the main menu.
   * @param selection the single character selection
   * @return true to continue the program, false to quit.
   */
  bool processMainMenu(char selection);

  /**
   * @brief playGame display and process the play game task.
   */
  void playGame();

  /**
   * @brief createCharacter display and process the create character task.
   */
  void createCharacter();

  /**
   * @brief dungeonTypeMenu display the select dungeon type task.
   */
  void dungeonTypeMenu() const;

  /**
   * @brief processDungeonType process the select dungeon type task.
   * @param selection the single character selection
   */
  void processDungeonType(char selection);

  /**
   * @brief switchToCharacterDetails If a Character is available, transition to the
   * character details menu, otherwise dislay an error and return to the previous menu.
   */
  void switchToCharacterMenu(Menu retMenuStatus = Menu::Main);

  /**
   * @brief quitGame displays the number of levels completed, if possible, before
   * prompting the user to confirm their intention to quit.
   */
  bool quitGame() const;

  /**
   * @brief characterDetails display the character details task.
   */
  void characterDetailsMenu() const;

  /**
   * @brief processCharacterDetails process the character details task.
   * @param selection the single character selection
   */
  void processCharacterDetails(char selection);

  /**
   * @brief displayWeaponDetails Output the detailed weapon info to the user
   */
  void displayWeaponDetails(std::string title = "", std::shared_ptr<weapons::Weapon> weapon = Game::instance()->player()->getWeapon());

  /**
   * @brief displayChamber 输出Chamber提示语
   */
  void displayChamber() const;

  /**
   * @brief actionMenu display main action task choices.
   */
  void actionMenu() const;

  /**
   * @brief processAction process the main action task.
   * @param selection the single character selection
   */
  void processAction(char selection);

  /**
   * @brief combatMenu display combat action task choices.
   */
  void combatMenu() const;

  /**
   * @brief processCombatAction process the combat action task.
   * @param selection the single character selection
   */
  void processCombatAction(char selection);

  /**
   * @brief doNavigate Navigates the player's character according to their input.
   */
  void doNavigate(char navigateDirection);

  /**
   * @brief doNavigateBack Navigates the player's character to where it comes.
   */
  void doNavigateBack();

  /**
   * @brief pickupWeapon Pick-up the weapon in the room, if any, and assign it
   * to the player. Prompts for user confirmation if the player already has an weapon.
   */
  void pickupWeapon();

  /**
   * @brief compareWeapons Display the player's current weapon and the weapon in the room if any.
   */
  void compareWeapons();

  /**
   * @brief doAttack Have the player perform the attack action
   */
  void doAttack();

  /**
   * @brief useSpecialAbility Have the player use its special ability/attack.
   */
  void useSpecialAbility();

  /**
   * @brief endGame Returns to the main menu, ending the current game/run through the dungeon.
   */
  void leaveDungeon(bool displayFailureMessage=true);

  /**
   * @brief confirm display and process the confirmation of an action.
   * @param confirmationPrompt the string to use as the prompt for confirmation
   * @return true if use confirms yes, false otherwise
   */
  bool confirm(const std::string &confirmationPrompt) const;

  /**
   * @brief toLower Make ch lowercase
   * @param ch
   * @return
   */
  char tolower(const char ch);

  // The functions below should not be modified.

  /**
   * @brief waitUntillNewline Helper function, pauses until the user hits [Enter]
   */
  void waitUntillNewline() const {
    _display << std::endl << "*Press any key to continue*" << std::endl;
#if not INPUT_SCRIPT
    _input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
#endif
  }

  /**
   * @brief echo Echoes the selection to the display. Used when running the input script.
   * @param selection the single character selection
   */
  template<class T>
  inline void echo(T selection) const {
#if INPUT_SCRIPT
    _display << selection << std::endl;
#else
    selection = selection; // just to eliminate the warning
#endif
  }

  struct _Centrew { int _width; }; ///< struct to hold the field width

  /**
   * @brief centre a basic stream manipulator type function that helps to centre a line of text
   * @param columns the number of columns
   * @param lineLength the number of characters in the line being centred
   * @return a _Setw struct to be used to configure the stream
   */
  inline _Centrew centre(unsigned int columns, unsigned int lineLength) const {
    if (lineLength > columns) return _Centrew{0};
    return _Centrew{static_cast<int>((columns - lineLength) / 2 + lineLength)};
  }

  /**
   * @brief operator << sets the field width of the stream based on the given centering specifier
   */
  inline friend std::ostream& operator<<(std::ostream &stream, const _Centrew &rhs) {
    return stream << std::setw(rhs._width);
  }
};

} // namespace core

#endif // MENUINTERFACE_H
