#!/bin/bash

# Migration script to transfer tasks from tasks.txt to SQLite database

echo "Todo App Migration Script"
echo "========================="

# Check if tasks.txt exists
if [ ! -f "tasks.txt" ]; then
    echo "No tasks.txt file found. Nothing to migrate."
    exit 0
fi

echo "Found tasks.txt with the following tasks:"
cat -n tasks.txt

echo ""
read -p "Do you want to migrate these tasks to SQLite database? (y/N): " response

if [[ "$response" =~ ^[Yy]$ ]]; then
    echo "Starting migration..."
    
    # Create backup
    cp tasks.txt tasks.txt.backup
    echo "Created backup: tasks.txt.backup"
    
    # Start the app once to create database, then exit immediately
    echo "Creating database..."
    timeout 2s ./dist/todo >/dev/null 2>&1 || true
    
    # Use sqlite3 to import tasks
    echo "Importing tasks..."
    while IFS= read -r line; do
        if [ -n "$line" ]; then
            sqlite3 todo.db "INSERT INTO tasks (text) VALUES ('$line');"
            echo "Imported: $line"
        fi
    done < tasks.txt
    
    echo "Migration completed successfully!"
    echo "Your tasks are now stored in todo.db"
    echo "Original file backed up as tasks.txt.backup"
    
    # Show imported tasks
    echo ""
    echo "Tasks in database:"
    sqlite3 todo.db "SELECT id, text, created_at FROM tasks;"
else
    echo "Migration cancelled."
fi
