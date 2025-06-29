#!/bin/bash

echo "[ArcOS Installer] Starting setup..."

TARGET_DIR="$HOME/Documents/ArcOS"
REPO_URL="https://github.com/Preclik02/ArcOS.git"
BASHRC="$HOME/.bashrc"
EXPORT_LINE='export PATH="$HOME/Documents/ArcOS/ArcNull:$PATH"'

# Step 1: Clone repository
echo "[1/5] Cloning ArcOS repo to $TARGET_DIR..."
if git clone "$REPO_URL" "$TARGET_DIR"; then
    echo "[OK] Repo cloned successfully."
else
    echo "[!] Clone of repo failed. Make sure the directory is empty or doesn't exist."
    exit 1
fi

# Step 2: Compile binaries
echo "[2/5] Compiling ArcNull programs..."

CPP_DIR="$TARGET_DIR/ArcNull/cpp"
C_DIR="$TARGET_DIR/ArcNull/c"
BIN_DIR="$TARGET_DIR/ArcNull"

# List of C++ files and output names
cpp_files=(
    "arcnull.cpp arcnull"
    "apps.cpp apps"
    "ssh_connect.cpp ssh_connect"
    "vnc_connect.cpp vnc_connect"
    "Arcc.cpp Arcc"
    "rpg.cpp rpg"
    "idek.cpp idek"
)

# List of C files and output names
c_files=(
    "nmap_check.c nmap_check"
    "ip_check.c ip_check"
)

# Compile C++ files
for item in "${cpp_files[@]}"; do
    src=$(echo "$item" | cut -d' ' -f1)
    out=$(echo "$item" | cut -d' ' -f2)

    # Compile arcnull.cpp from ArcNull root, others from cpp/
    if [[ "$src" == "arcnull.cpp" ]]; then
        src_path="$TARGET_DIR/ArcNull/$src"
    else
        src_path="$CPP_DIR/$src"
    fi

    echo "Compiling C++: $src -> $out..."
    if ! g++ "$src_path" -o "$BIN_DIR/$out"; then
        echo "[!] Compilation failed for $src."
        exit 1
    fi
done

# Compile C files
for item in "${c_files[@]}"; do
    src=$(echo "$item" | cut -d' ' -f1)
    out=$(echo "$item" | cut -d' ' -f2)

    echo "Compiling C: $src -> $out..."
    if ! gcc "$C_DIR/$src" -o "$BIN_DIR/$out"; then
        echo "[!] Compilation failed for $src."
        exit 1
    fi
done

# Step 3: Add to PATH
echo "[3/5] Adding ArcNull to PATH in .bashrc..."
if grep -Fxq "$EXPORT_LINE" "$BASHRC"; then
    echo "[OK] PATH line already exists in .bashrc"
else
    if echo "$EXPORT_LINE" >> "$BASHRC"; then
        echo "[OK] PATH line added to .bashrc"
    else
        echo "[!] Failed to add the directory to the PATH. Make sure $BASHRC exists."
        exit 1
    fi
fi

# Step 4: Source .bashrc
echo "[4/5] Reloading .bashrc..."
if source "$BASHRC"; then
    echo "[OK] .bashrc reloaded."
else
    echo "[!] Failed to reload .bashrc. Please restart your terminal manually."
fi

echo "[✔] ArcOS setup complete."
