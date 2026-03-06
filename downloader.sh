#!/bin/bash
# --- VAC-SFTWARE One-Click Installer ---
# Created by: Shrijiith Mahesh 

echo "🚀 Initializing VAC Deployment Protocol..."
sudo apt install git
# Step 1: Clone the Four Friends Repository
git clone https://github.com/shrijiithmahesh-eng/VAC_Software.git

# Step 2: Move into the folder
cd VAC_Software

# Step 3: Set up the directories we planned
mkdir -p bin/VAC boot

# Step 4: Give a message to the team
echo "✅ VAC-SFTWARE is now installed!"
echo "📂 Folders: /bin/VAC, /boot, and doc.txt are ready."
echo "Four Friends: Shrijiith, Vishvaswar, Vaisnavi, Nikeaten."
echo "Lol Bye. see you on $RANDOM"
