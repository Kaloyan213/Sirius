import platform
import subprocess
import os
import stat

from SetupBuildTools import BuildTools as BuildToolsRequirements
from SetupPython import PythonConfiguration as PythonRequirements
from SetupPremake import PremakeConfiguration as PremakeRequirements
# from SetupVulkan import VulkanConfiguration as VulkanRequirements

BuildToolsRequirements.EnsureInstalled()
PythonRequirements.Validate()

premakeInstalled = PremakeRequirements.Validate()
#VulkanRequirements.Validate()

script_dir = os.path.dirname(os.path.abspath(__file__))
project_root = os.path.abspath(os.path.join(script_dir, ".."))

print("\nUpdating submodules...")
subprocess.call(["git", "submodule", "update", "--init", "--recursive"], cwd=project_root)

if premakeInstalled:
    if platform.system() == "Windows":
        print("\nRunning premake (Windows)...")
        bat_path = os.path.join(script_dir, "Win-GenProjects.bat")
        subprocess.call([bat_path, "nopause"], cwd=project_root)
    
    elif platform.system() == "Linux":
        script_path = os.path.join(script_dir, "Linux-GenProjects.sh")
        
        st = os.stat(script_path)
        os.chmod(script_path, st.st_mode | stat.S_IEXEC)
        
        print("\nRunning premake (Linux)...")
        subprocess.call(["/bin/bash", script_path], cwd=project_root)

    print("\nSetup completed!")