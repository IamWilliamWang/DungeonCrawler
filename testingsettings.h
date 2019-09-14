#ifndef TESTINGSETTINGS_H
#define TESTINGSETTINGS_H

/* Edit this file to enable and disable tests. */

// When switching modes, it is best to do a 'clean' or,
// equivalently, a 'rebuild'.
// You can do this by right-clicking on project folder
// and selecting 'clean' or 'rebuild' as desired.

// Set this to 1 to run the testing, 0 to run normal mode.
#define TESTING 1

// Set this to 1 to run the game using the input script
// In order to work, the provided input script relies on
// the generation of goblins as the only creature and
// either the potion or acid flask items as items.
#define INPUT_SCRIPT 0

// If this is 1, the output generated from the INPUT_SCRIPT
// will be stored directly in file rather than output to
// the console.
// Only has an effect of INPUT_SCRIPT is 1
#define OUTPUT_SCRIPT 0

#endif // TESTINGSETTINGS_H
