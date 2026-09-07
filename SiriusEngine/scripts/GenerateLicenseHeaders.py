import os
from pathlib import Path

COPYRIGHT_HEADER = """/*
 * Copyright (c) Kaloyan Badankov
 */"""

SEARCH_STRING = "Copyright (c) Kaloyan Badankov"

def add_copyright_to_files(directory):
    # Extensions to modify
    target_extensions = {'.h', '.cpp'}
    
    # Recursively find all files in the directory
    for filepath in Path(directory).rglob('*'):
        if filepath.is_file() and filepath.suffix in target_extensions:
            try:
                # Read the file content
                with open(filepath, 'r', encoding='utf-8') as f:
                    content = f.read()
                
                # Check if the copyright string is already present
                if SEARCH_STRING not in content:
                    print(f"Adding copyright to: {filepath}")
                    
                    # Write the header, a blank line, and then the original content
                    with open(filepath, 'w', encoding='utf-8') as f:
                        f.write(f"{COPYRIGHT_HEADER}\n\n{content}")
                else:
                    # Optional: uncomment to see skipped files
                    # print(f"Skipping (already exists): {filepath}")
                    pass
                    
            except UnicodeDecodeError:
                print(f"Warning: Skipped {filepath} (Not a valid UTF-8 text file)")
            except Exception as e:
                print(f"Error processing {filepath}: {e}")

if __name__ == "__main__":
    add_copyright_to_files("../include")
    add_copyright_to_files("../source")
    print("Copyright update complete.")
