# --- VAC-SFTWARE One-Click Installer ---
#!/bin/bash
# --- VAC-SOFTWARE Martian Deployment Protocol ---
# Created by: Shrijiith Mahesh (@shrijiithmahesh-eng)

echo "🔍 Scanning Planetary OS Environment..."

# 1. DETECT THE DISTRO
if [ -f /etc/os-release ]; then
    . /etc/os-release
    DISTRO=$ID
else
    DISTRO="unknown"
fi

# 2. INSTALL GIT (The Universal Tool)
case $DISTRO in
    ubuntu|debian|raspbian)
        echo "📡 Debian-based system detected. Using apt..."
        sudo apt update && sudo apt install -y git
        ;;
    arch|manjaro)
        echo "📡 Arch-based system detected. Using pacman..."
        sudo pacman -Sy --noconfirm git
        ;;
    fedora|centos|rhel)
        echo "📡 RedHat-based system detected. Using dnf..."
        sudo dnf install -y git
        ;;
    *)
        echo "⚠️  Unknown Distro: $DISTRO. Attempting to proceed anyway..."
        ;;
esac

# 3. DEPLOY THE SYNDICATE REPO
echo "🚀 Initializing VAC Deployment Protocol..."
git clone https://github.com/shrijiithmahesh-eng/VAC_Software.git || { echo "❌ ERROR: Clone failed!"; exit 1; }

cd VAC_Software || exit

# 4. INITIALIZE MARTIAN DIRECTORIES
echo "📁 Partitioning 20GB Disk Space..."
mkdir -p bin/VAC boot/systemv-vac

# 5. FINAL STATUS & CREDITS
echo "------------------------------------------------"
echo "✅ VAC-SOFTWARE IS NOW INSTALLED!"
echo "🌍 Mission Control: Shrijiith (Software), Nikeaten (Hardware),"
echo "🧠 Logic Team: Vishvaswar, Panveen, Vaisnavi"
echo "🎨 Design Lead: Danshik"
echo "------------------------------------------------"
echo "Lol Bye. See you on Mars!. In the year $RANDOM 🔴"
