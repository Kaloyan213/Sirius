import platform
import shutil
import subprocess
import sys

class BuildTools:
    @staticmethod
    def EnsureInstalled():
        if platform.system() == "Linux":
            if shutil.which("ninja") is None or shutil.which("g++") is None or shutil.which("cmake") is None:
                print("Missing build tools (ninja/g++/cmake).")
                print("Attempting to install via 'sudo apt install build-essential git cmake ninja-build'...")
                
                try:
                    subprocess.check_call(["sudo", "apt", "update"])
                    subprocess.check_call(["sudo", "apt", "install", "-y", "build-essential", "git", "cmake", "ninja-build"])
                except subprocess.CalledProcessError:
                    print("\nError: Failed to install build tools automatically.")
                    print("Please run this command manually and try again:")
                    print("sudo apt update && sudo apt install -y build-essential git cmake ninja-build")
                    sys.exit(1)
