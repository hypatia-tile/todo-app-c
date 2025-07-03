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

## [1.2.0] - 2025-06-29 (SQLite Implementation)

### Added
- **Database Module** (`src/database.c`, `include/database.h`)
  - `db_init()` - Initialize SQLite database and create schema
  - `db_cleanup()` - Close database connection properly
  - `db_load_tasks()` - Load tasks from SQLite database
  - `db_save_tasks()` - Save tasks with transaction support
  - `db_add_task()` - Add individual task to database
  - `db_delete_task_by_index()` - Delete task by position
  - `db_get_task_count()` - Get total number of tasks

- **Migration Support**
  - `migrate.sh` - Script to migrate from tasks.txt to SQLite
  - Automatic database creation on first run
  - Backup creation during migration

- **Database Schema**
  ```sql
  CREATE TABLE tasks (
      id INTEGER PRIMARY KEY AUTOINCREMENT,
      text TEXT NOT NULL,
      created_at DATETIME DEFAULT CURRENT_TIMESTAMP
  );
  ```

### Changed
- **Storage Backend**
  - Replaced file I/O with SQLite database operations
  - Maintained existing API compatibility
  - Enhanced error handling and reporting

- **Task Module** (`src/task.c`)
  - Updated `load_tasks()` to use `db_load_tasks()`
  - Updated `save_tasks()` to use `db_save_tasks()`
  - Added database error handling

- **Main Application** (`src/main.c`)
  - Added database initialization in startup sequence
  - Added proper database cleanup on exit
  - Enhanced error handling for database failures

- **Build System** (`Makefile`)
  - Added SQLite3 library linking (`-lsqlite3`)
  - Added `database.c` to source file list
  - Updated dependencies

### Technical Improvements
- **ACID Transactions**: All database operations now have transaction support
- **Data Integrity**: Schema validation and constraint enforcement
- **Performance**: Prepared statements and efficient queries
- **Concurrency**: Safe multi-instance access (read operations)
- **Error Recovery**: Graceful handling of database errors
- **Memory Safety**: Proper resource cleanup and null checking

### Database Features
- **Automatic Schema Creation**: Database and tables created on first run
- **Transaction Support**: Bulk operations wrapped in transactions
- **Prepared Statements**: Protection against SQL injection
- **Connection Management**: Proper initialization and cleanup
- **Error Reporting**: Database errors reported through UI module

### Migration Path
- Old format: `tasks.txt` (plain text)
- New format: `todo.db` (SQLite database)
- Migration tool: `./migrate.sh`
- Backward compatibility: API unchanged

### Dependencies
- **New External Dependency**: SQLite3 development libraries
- **Runtime Requirement**: SQLite3 shared library
- **Platform Support**: Available on macOS, Linux, Windows

## [1.3.0] - 2025-07-03 (K&R Style Formatting) ✅ MERGED

**Pull Request**: #8 - Successfully merged into `dev` branch  
**Merge Commit**: `1d0f6f9`  
**Status**: ✅ Production Ready

### Added
- **K&R Formatting Infrastructure**
  - `.clang-format` - Comprehensive K&R style configuration
  - `format.sh` - Interactive formatting script with user guidance
  - `make format` - Convenient formatting command in build system

- **Automated Code Formatting**
  - Consistent K&R (Kernighan & Ritchie) style across entire codebase
  - 4-space indentation with no tabs
  - 80-character line limit
  - Right-aligned pointer declarations (`char *ptr`)
  - Linux-style brace placement (K&R variant)

- **Developer Tools**
  - Interactive formatting script with dependency checking
  - Educational K&R style guidelines in script output
  - Build system integration for easy formatting

### Changed
- **All Source Files Formatted**
  - `src/main.c` - Applied K&R brace style and spacing
  - `src/task.c` - Consistent function declaration formatting
  - `src/ui.c` - Standardized brace placement
  - `src/menu.c` - Uniform control structure formatting
  - `src/database.c` - Comprehensive K&R style application
  - `include/*.h` - Header file formatting consistency

- **Build System Enhancement**
  - `Makefile` - Added `format` target for code formatting
  - Updated `.PHONY` targets to include formatting

### Technical Improvements
- **Code Consistency**: 100% K&R compliance across all files
- **Readability**: Uniform formatting improves code navigation
- **Maintainability**: Consistent style reduces cognitive load
- **Automation**: One-command formatting prevents style drift
- **Professional Standards**: Authentic K&R style implementation

### Formatting Rules Applied
- **Brace Style**: Opening braces on same line as declarations
- **Indentation**: 4 spaces consistently, no tabs
- **Spacing**: Proper spacing around operators and keywords
- **Line Length**: 80-character limit with intelligent wrapping
- **Pointer Style**: Right-aligned pointer declarations
- **Control Structures**: Consistent spacing in if/while/for statements

### Developer Workflow
```bash
make format              # Format all source files
make clean && make       # Verify compilation after formatting
git diff                 # Review formatting changes
```

### Quality Assurance
- ✅ All files compile without warnings after formatting
- ✅ No functional changes, formatting only
- ✅ Build system integration ensures easy adoption
- ✅ Interactive script prevents accidental changes

### File Statistics
- **Files Processed**: 9 C source and header files
- **Lines Optimized**: 35 insertions(+), 44 deletions(-)
- **Net Improvement**: 9 lines saved through more compact formatting
- **Consistency**: 0% → 100% K&R compliance

This release establishes a solid foundation for consistent, professional C code formatting that matches industry standards and the original K&R style from "The C Programming Language" book.
