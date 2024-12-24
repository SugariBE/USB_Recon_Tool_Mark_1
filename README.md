USB_Recon_Tool_Mark_1

### **Description**  
The USB Recon Tool is a lightweight program designed to collect system and network information from a Windows machine. It stores this data in a hidden text file on the USB drive where the program resides. The tool is protected with a password and operates discreetly using PowerShell commands.

---

### **How It Works**  
1. **Execution**:  
   - The program is run directly from a USB drive.  
   - It uses PowerShell to execute commands like `systeminfo` and `ipconfig` to collect data.

2. **Data Storage**:  
   - Collected information is saved in a hidden file (`ipconfig_output.txt`) on the USB drive.  
   - The file is hidden using the `attrib +h +r +s` command.

3. **Password Protection**:  
   - A password is required to unhide the file.  
   - If the password is correct, the file becomes visible. If incorrect, new data is appended to the file, and it remains hidden.

4. **Windows-Only**:  
   - The tool is compatible only with Windows OS and uses native system commands.

---

### **Key Features**  
- **Stealth Mode**: Runs PowerShell commands in the background without showing a visible window.  
- **Portability**: Operates directly from a USB flash drive.  
- **Security**: Protected by a password to control access to the hidden file.  

---

### **Code Overview**  
1. **PowerShell Commands**:  
   - `systeminfo > ipconfig_output.txt`: Collects system information.  
   - `ipconfig >> ipconfig_output.txt`: Adds network details.  
   - `attrib +h +r +s`: Hides the output file.  
   - `attrib -h -s -r`: Makes the file visible if the password is correct.  

2. **Hidden Execution**:  
   - PowerShell commands are run using the `CreateProcess` API in hidden mode (`SW_HIDE`).  

3. **Password Logic**:  
   - On execution, the program asks for a password:  
     - **Correct**: Unhides the file.  
     - **Incorrect**: Collects and hides new data.  

---

### **Setup and Usage**  
- Place the program on a USB drive and run it on a target Windows machine.  
- The tool collects and hides information automatically after execution.  
- To access the hidden file, re-run the program and enter the correct password.

---

### **Ethical Note**  
This tool is for authorized use only. Ensure you have permission before deploying it on any machine.  
