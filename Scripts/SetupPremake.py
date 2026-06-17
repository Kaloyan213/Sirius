import sys
import os
import platform
import stat
import subprocess
import shutil
from pathlib import Path
import Utils

class PremakeConfiguration:
    premakeVersion = "5.0.0-beta8"
    premakeLicenseUrl = "https://raw.githubusercontent.com/premake/premake-core/master/LICENSE.txt"
    
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.abspath(os.path.join(script_dir, ".."))
    premakeDirectory = os.path.join(project_root, "Vendor/premake/binaries")

    @classmethod
    def _GetSystemInfo(cls):
        system = platform.system()
        if system == "Windows":
            return "windows", "zip", "premake5.exe"
        elif system == "Linux":
            return "linux", "tar.gz", "premake5"
        else:
            raise RuntimeError(f"Unsupported platform: {system}")

    @classmethod
    def GetPremakeUrl(cls):
        sys_name, ext, _ = cls._GetSystemInfo()
        return f"https://github.com/premake/premake-core/releases/download/v{cls.premakeVersion}/premake-{cls.premakeVersion}-{sys_name}.{ext}"

    @classmethod
    def Validate(cls):
        if not cls.CheckIfPremakeInstalled():
            print("Premake is not installed.")
            if not cls.InstallPremake():
                return False
        
        # Final Verification: Does it run?
        if not cls.VerifyBinary():
            print("Detected incompatible binary. Re-installing from source...")
            if not cls.CompilePremakeFromSource():
                return False
        
        print(f"Correct Premake located at {os.path.abspath(cls.premakeDirectory)}")
        return True

    @classmethod
    def CheckIfPremakeInstalled(cls):
        _, _, exe_name = cls._GetSystemInfo()
        premakeExe = Path(os.path.join(cls.premakeDirectory, exe_name))
        return premakeExe.exists()

    @classmethod
    def VerifyBinary(cls):
        """Runs the binary with --version to check for GLIBC compatibility."""
        _, _, exe_name = cls._GetSystemInfo()
        exe_path = os.path.join(cls.premakeDirectory, exe_name)
        try:
            subprocess.check_call([exe_path, "--version"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
            return True
        except:
            return False

    @classmethod
    def InstallPremake(cls):
        while True:
            reply = input(f"Premake not found. Download Premake {cls.premakeVersion}? [Y/N]: ").lower().strip()
            if reply == 'n': return False
            if reply == 'y': break

        sys_name, ext, exe_name = cls._GetSystemInfo()
        zip_url = cls.GetPremakeUrl()
        premakePath = os.path.join(cls.premakeDirectory, f"premake-{cls.premakeVersion}-{sys_name}.{ext}")
        
        print(f"Downloading {zip_url}...")
        Utils.DownloadFile(zip_url, premakePath)
        Utils.UnzipFile(premakePath, deleteZipFile=True)
        
        if platform.system() == "Linux":
            exe_path = os.path.join(cls.premakeDirectory, exe_name)
            st = os.stat(exe_path)
            os.chmod(exe_path, st.st_mode | stat.S_IEXEC)

        # Download License
        licensePath = os.path.join(cls.premakeDirectory, "LICENSE.txt")
        Utils.DownloadFile(cls.premakeLicenseUrl, licensePath)
        
        return True

    @classmethod
    def CompilePremakeFromSource(cls):
        # 1. Define paths
        build_dir = os.path.join(cls.project_root, "build") # Create a clean build dir
        src_dir = os.path.join(cls.project_root, "temp_premake_build")
        
        # 2. Cleanup existing build artifacts
        if os.path.exists(build_dir): shutil.rmtree(build_dir)
        os.makedirs(build_dir)
        
        # 3. Clone source if not already there
        if not os.path.exists(src_dir):
            subprocess.check_call(["git", "clone", "--recursive", "https://github.com/premake/premake-core.git", src_dir])
        
        print(f"Compiling Premake in {build_dir}...")
        
        # 4. Run build from inside the 'build' directory
        # We tell 'make' to look at the Bootstrap.mak in the source directory
        subprocess.check_call(["make", "-f", os.path.join(src_dir, "Bootstrap.mak"), "linux"], cwd=build_dir)
        
        # 5. Move the binary to your target directory
        src_binary = os.path.join(build_dir, "bin/release/premake5")
        dst_binary = os.path.join(cls.premakeDirectory, "premake5")
        
        if os.path.exists(dst_binary): os.remove(dst_binary)
        shutil.move(src_binary, dst_binary)
        
        # 6. Cleanup only the temporary build folder
        shutil.rmtree(build_dir)
        print("Compilation successful!")
        return True