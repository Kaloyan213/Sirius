import sys
import os
import platform
import requests
import time
import tarfile
from zipfile import ZipFile

if platform.system() == "Windows":
    import winreg

def GetSystemEnvironmentVariable(name):
    if platform.system() == "Windows":
        try:
            key = winreg.CreateKey(winreg.HKEY_LOCAL_MACHINE, r"System\CurrentControlSet\Control\Session Manager\Environment")
            return winreg.QueryValueEx(key, name)[0]
        except:
            return None
    return os.environ.get(name)

def DownloadFile(url, filepath):
    filepath = os.path.abspath(filepath)
    os.makedirs(os.path.dirname(filepath), exist_ok=True)
    
    print(f"Downloading {url} to {filepath}")
    
    headers = {'User-Agent': "Mozilla/5.0"}
    response = requests.get(url, headers=headers, stream=True)
    response.raise_for_status() # Raise error if download fails
    
    total_size = int(response.headers.get('content-length', 0))
    downloaded = 0
    startTime = time.time()
    
    with open(filepath, 'wb') as f:
        for data in response.iter_content(chunk_size=1024*1024):
            downloaded += len(data)
            f.write(data)
            
            # Progress bar logic
            if total_size > 0:
                percent = (downloaded / total_size) * 100
                elapsed = time.time() - startTime
                speed = (downloaded / 1024) / elapsed if elapsed > 0 else 0
                sys.stdout.write(f"\rDownloading: {percent:.2f}% ({speed:.2f} KB/s)   ")
                sys.stdout.flush()
    sys.stdout.write('\n')

def UnzipFile(filepath, deleteZipFile=True):
    filepath = os.path.abspath(filepath)
    extract_to = os.path.dirname(filepath)
    
    print(f"Extracting {filepath} to {extract_to}...")
    
    if filepath.endswith('.tar.gz'):
        with tarfile.open(filepath, "r:gz") as tar:
            tar.extractall(path=extract_to)
    elif filepath.endswith('.zip'):
        with ZipFile(filepath, 'r') as zip_ref:
            zip_ref.extractall(extract_to)
    else:
        raise NotImplementedError(f"Unsupported archive format: {filepath}")

    if deleteZipFile:
        os.remove(filepath)
    print("Extraction complete.")