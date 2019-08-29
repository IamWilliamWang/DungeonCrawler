#include "menuinterface.h"
#include <iostream>
#include <string>

#include "testingsettings.h"

#define AUTHOR "<your name>"
#define TITLE "<your game name>"

#if INPUT_SCRIPT
#define SCRIPT_PATH "../assignment1-dungeon_crawler/input_script.txt"
#define OUT_FILE_PATH "../assignment1-dungeon_crawler/output_gen.txt"
#endif

/* ------------------------------------------------------------------------------
 * NOTE: DO NOT edit this file other than providing your name and game title to the
 * `AUTHOR` and `TITLE` macros, respectively.
 * Enable testing mode and set options in the testingsettings.h file.
 * It may be necessary to change the path to the input script, depending on your
 * configuration: see SCRIPT_PATH macro definition above.
 * -----------------------------------------------------------------------------*/

/**
 * @mainpage
 *
 * There are three forms of the main function in this file so that it can run in
 * three modes: normal, input script, and testing. This is done using conditional
 * compilation and is configured through `testingsettings.h`.
 *
 * In normal mode, the MenuInterface will be run and attached to standard in and
 * standard out.
 *
 * In input script mode, the Menu Interface will be run and attached to a file
 * for input and (optionally) a file for output. This will be used as a quick test
 * of the general functionality of your implementation. You can use it yourself
 * to test as you go to ensure that your implementation conforms to the expected
 * commands.
 *
 * In testing mode, a simple unit testing suite will be executed. A small example
 * has been provided, but you are encouraged to implement tests as you go to
 * ensure the parts of your implementation are working. This saves time as it makes
 * it easier to track down errors for "submodules" this way, rather than having to
 * test everything through the menu-driven interface constantly.
 */

using core::MenuInterface;

#if not TESTING

#if not INPUT_SCRIPT

/**
 * @brief main Simple main function that runs the MenuInterface until quit.
 * @return exit code, 0 is success
 */
int main()
{
  MenuInterface m{std::cout, std::cin};

  m.displayWelcome(AUTHOR, TITLE);
  m.run();

  return 0;
}

#else
#include <fstream>
#include <QDir>

/**
 * @brief main Simple main function runs game using the input script.
 * @return
 */
int main()
{
  // Using QDir to provide sensible error useful error message
  // if the script file cannot be found.
  QDir path{SCRIPT_PATH};
  std::fstream in{path.absolutePath().toStdString()};
  if (in.fail()) {
    std::cout << "Unable to find file: " << path.absolutePath().toStdString() << std::endl
              << "Current path: " << QDir::currentPath().toStdString() << std::endl;
    return 1;
  }

#if OUTPUT_SCRIPT
  QDir outPath{OUT_FILE_PATH};
  std::ofstream out{outPath.absolutePath().toStdString()};
  if (out.fail()) {
    std::cout << "Unable to open out file: " << outPath.absolutePath().toStdString() << std::endl
              << "Current path: " << QDir::currentPath().toStdString() << std::endl;
    return 1;
  }
#else
  std::ostream& out = std::cout;
#endif

  MenuInterface m{out, in};

  m.displayWelcome(AUTHOR, TITLE);
  m.run();

  return 0;
}

#endif

#else

#include "testing.h"

/**
 * @brief main run testing code.
 * @return
 */
int main() {
  Testing test{};
  std::cout << "Running tests ..." << std::endl;
  test.runTests(); // Modify which tests are run in the implementation of runTests()
  test.printTestResults(std::cout);
  return 0;
}

#endif
