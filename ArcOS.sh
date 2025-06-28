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

cd "$TARGET_DIR/ArcNull" || {
    echo "[!] Failed to enter ArcNull directory."
    exit 1
}

compile_list=(
    "arcnull.cpp arcnull"
    "apps.cpp apps"
    "ssh_connect.cpp ssh_connect"
    "vnc_connect.cpp vnc_connect"
    "Arcc.cpp Arcc"
    "rpg.cpp rpg"
    "idek.cpp idek"
)

for item in "${compile_list[@]}"; do
    src=$(echo "$item" | cut -d' ' -f1)
    out=$(echo "$item" | cut -d' ' -f2)
    
    echo "Compiling $src -> $out..."
    if ! g++ "$src" -o "$out"; then
        echo "[!] Compilation failed for $src. The repo may not have cloned properly. Please manually check the files."
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

