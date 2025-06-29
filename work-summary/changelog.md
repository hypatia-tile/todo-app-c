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
