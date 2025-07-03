#!/bin/bash

# K&R Style Formatter Script
# Formats all C source files according to K&R style

echo "🎯 K&R Style Formatter"
echo "======================"

# Check if clang-format is available
if ! command -v clang-format &> /dev/null; then
    echo "❌ clang-format not found. Please install it:"
    echo "   macOS: brew install clang-format"
    echo "   Ubuntu: sudo apt-get install clang-format"
    exit 1
fi

echo "✅ Found clang-format: $(which clang-format)"
echo ""

# Find all C source files
C_FILES=$(find . -name "*.c" -o -name "*.h" | grep -E "^./src/|^./include/" | sort)

if [ -z "$C_FILES" ]; then
    echo "❌ No C source files found in src/ or include/"
    exit 1
fi

echo "📁 Found C files:"
echo "$C_FILES"
echo ""

# Ask for confirmation
read -p "🔄 Format all these files with K&R style? (y/N): " response

if [[ "$response" =~ ^[Yy]$ ]]; then
    echo ""
    echo "🎨 Formatting files..."
    
    # Format each file
    for file in $C_FILES; do
        echo "   Formatting: $file"
        clang-format -i -style=file "$file"
    done
    
    echo ""
    echo "✅ All files formatted successfully!"
    echo "💡 Tip: Run 'git diff' to see what changed"
else
    echo "❌ Formatting cancelled."
fi

echo ""
echo "📚 K&R Style Guidelines:"
echo "   • Opening braces on same line as declaration"
echo "   • 4-space indentation (no tabs)"
echo "   • Spaces around operators: x = y + z"
echo "   • No space before function parentheses: func()"
echo "   • Space after control statements: if (), while ()"
