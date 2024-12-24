Description 

The USB Recon Tool is a portable program designed to gather system and network information from a Windows machine. It saves this data into a hidden text file on the USB drive containing the program. The tool is password-protected and operates discreetly by utilizing PowerShell commands executed in hidden mode. This project can also be implemented in C++ or C#, offering flexibility for developers familiar with different programming languages.

How It Works

Execution:

The program is run directly from a USB flash drive.
It uses PowerShell commands to collect data like system information (systeminfo) and network configuration (ipconfig).

Data Storage:

The collected information is saved in a text file named ipconfig_output.txt.
The file is hidden using the command attrib +h +r +s.

Password Protection:

The program asks for a password when run:
Correct Password: Unhides the file for review.
Incorrect Password: Collects and appends new data to the file, keeping it hidden.

Windows-Only:

The tool is designed to work exclusively on Windows OS and uses native system commands.
Alternative Implementations:

The functionality can be replicated in C++ or C#, leveraging their ability to handle system processes and manage files.

Key Features

Stealth Mode: Executes PowerShell commands in the background without showing a visible window.
Portability: Runs directly from a USB drive, requiring no installation.
Password Security: Ensures controlled access to the hidden file.
Language Flexibility: Can be implemented in C, C++, or C#, offering a variety of development options.

Code Highlights

PowerShell Commands:

systeminfo > ipconfig_output.txt: Gathers system information.
ipconfig >> ipconfig_output.txt: Adds network details.
attrib +h +r +s: Hides the text file.
attrib -h -s -r: Unhides the file if the password is correct.

Hidden Execution:

The tool uses the CreateProcess API in C to run PowerShell commands in a completely hidden mode (SW_HIDE).

Password Logic:

Ensures only authorized users can unhide the data file while appending new data if access is denied.

Setup and Usage

Deploy: Place the compiled program on a USB drive.
Run: Execute it on a Windows machine by clicking the program file.

Collect Data:

The program collects system and network data and saves it in a hidden file on the USB drive.
Access Data: Re-run the program and enter the correct password to make the file visible.

Ethical Note

This tool is intended for authorized and ethical use only. Ensure you have permission before deploying it on any machine. Misuse of this tool may violate laws and ethical standards.
