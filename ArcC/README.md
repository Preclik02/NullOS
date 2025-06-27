```markdown
# ArcC & Arcc

**ArcC** is a chaotic C-based framework and **Arcc** is its companion compiler — a cursed duo built for ArcOS. Inspired by **Brainfuck** and **Whitespace**, ArcC takes the concept of unreadable code to new levels with its own `.arc` file format and a custom cipher (sifra). No, really — **you won’t know what the code means until it's compiled.**

---

## 🤯 What Is This?

- **ArcC** is a C-like framework, but not really. It’s like if C and an ancient spellbook had a baby.
- **Arcc** is the compiler that makes sense of the mess. It uses a Python script to:
  1. Convert `.arc` files to `.c`
  2. Compile them with `gcc`
  3. Delete the generated `.c` file (like it never happened)

---

## 🧪 Status

- ✅ Tested on basic C programs
- ❌ Not suitable for complex projects (yet)
- 🔐 Uses its own custom encryption/decryption mechanism (C++ + Python)
- 🔎 To understand the cipher (sifra), read the documentation… if you dare

---

## ⚙️ How It Works

1. Write your cursed `.arc` code (good luck).
2. Call `arcc yourfile.arc` from the **ArcNull** shell.
3. `arcc` compiles it and runs the resulting program (if compilation succeeds).
4. `.c` file gets deleted immediately.

---

## 🧠 What’s in the .arc Files?

- Utter chaos
- A custom language only **you** understand
- The `.arc` extension isn’t recognized by the system, but **Arcc** knows what’s up

---

## 🛠 Setup

Make sure you have:

- Python 3 installed
- `gcc` installed
- ArcC and Arcc cloned into your ArcOS directory (`~/Documents/ArcOS`)

Then add the compiler script to your PATH in `~/.bashrc`:

```bash
export PATH="$HOME/Documents/ArcOS/Arcc:$PATH"
source ~/.bashrc
```

Run from **ArcNull**:

```bash
arcc helloworld.arc
```

---

## 📜 Documentation

Want to decode the cipher (sifra)? The docs will guide you through letters, symbols, and chaos. Every command is based on randomly chosen characters that you’ll need to decipher.

It’s terrible. It’s funny. It’s yours.

---

## 🧩 Contributions

This project is not meant to be practical — but feel free to contribute if you want to help improve the madness.

---

## 📄 License

MIT License

---

## 💬 Final Thoughts

ArcC and Arcc aren’t just tools. They’re a puzzle. They’re an experience. Most importantly — they’re a joke only you can understand.

Use wisely.
```
