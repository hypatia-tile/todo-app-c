# Changelog - Modular Refactoring

## [1.1.0] - 2025-06-29

### Added
- **New UI Module** (`src/ui.c`, `include/ui.h`)
  - `ui_init()` - Initialize ncurses interface
  - `ui_cleanup()` - Cleanup ncurses interface
  - `ui_clear()` - Clear screen
  - `ui_getch()` - Get character input
  - `ui_print()` - Print formatted text
  - `ui_get_string()` - Get string input
  - `ui_wait_for_key()` - Wait for key press

- **New Menu Module** (`src/menu.c`, `include/menu.h`)
  - `menu_show()` - Display main menu
  - `menu_handle_view()` - Handle task viewing
  - `menu_handle_add()` - Handle task addition
  - `menu_handle_delete()` - Handle task deletion

- **Work Summary Documentation**
  - `work-summary/refactoring-summary.md` - Comprehensive refactoring documentation
  - `work-summary/changelog.md` - This changelog

### Changed
- **Main Function** (`src/main.c`)
  - Removed all direct ncurses calls
  - Removed inline menu handling functions
  - Simplified to focus on application flow
  - Reduced code size from ~80 lines to ~30 lines

- **Task Module** (`src/task.c`)
  - Updated to use UI abstraction layer
  - Replaced `printw()` calls with `ui_print()`

- **Build System** (`Makefile`)
  - Added new source files to build process
  - Updated SRC variable to include ui.c and menu.c

### Removed
- Inline menu functions from `main.c`:
  - `show_menu()`
  - `handle_view()`
  - `handle_add()`
  - `handle_delete()`
- Direct ncurses calls from `main.c`
- Architecture documentation from `docs/` (moved to work-summary)

### Technical Improvements
- **Separation of Concerns**: Each module now has a single responsibility
- **Loose Coupling**: Modules depend on interfaces, not implementations
- **High Cohesion**: Related functionality grouped together
- **Better Encapsulation**: Internal details hidden behind clean interfaces
- **Enhanced Maintainability**: Easier to modify, extend, and debug

### Dependencies
- Added proper header dependencies between modules
- Maintained external dependency on ncurses library
- Created clear dependency hierarchy with no circular dependencies

### File Structure Changes
```
Before:
src/
├── main.c (monolithic)
└── task.c

After:
src/
├── main.c (simplified)
├── task.c (updated)
├── ui.c (new)
└── menu.c (new)

include/
├── todo.h (existing)
├── ui.h (new)
└── menu.h (new)
```

## Compatibility
- All existing functionality preserved
- File format remains the same (tasks.txt)
- User interface behavior unchanged
- Build process updated but compatible with existing environment
