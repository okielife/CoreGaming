
# Platform Directory

Responsibilities of src/platform:
- SDL init / shutdown
- Window creation
- Event polling
- Keyboard/controller input
- Audio device management
- File IO paths (asset root, save dir)

No other directory should have \#include SDL stuff

#defgroup Platform