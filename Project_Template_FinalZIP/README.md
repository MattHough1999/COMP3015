


# COMP3015: Initial Prototype

This is a brief write up about my C1 project submission for COMP3015...
In this write up you will find:
A link to the video walkthrough; A link to the git repo; Information about the project and code.


## Installation/Setup

There is no installation required for the executable, however if you wish to open and run the project in Visual Studio there are some steps you must follow.

### Executable
Inside the **Project.zip** there is a folder called **BUILD** It contains the executable **Project_Template.exe**.
### Project
#### Step One: Opening The Dependencies Window
As mentioned above, running the project through Visual Studio will require some basic setup.
First: Open the **Project** Folder. Inside there is a Visual Studio Solution file: **Project_Template.sln** open it.
Next: In the solution explorer right click **Project_Template** and open **Properties**. This will open the properties window.
Then: Open **VC++ Directories** in the **General** drop down there will be **Include Directories** and **Library Directories**. Follow these next steps for both.
Click on the file path and then on the drop down arrow that will appear. Then click **<Edit...>**
This will open a new window with two file paths, You need to change this file path to fit your machine.
#### Step Two: Setting Dependencies
Inside the **Project** folder there is a folder called **Dependencies** this folder contains 2 folders (**Include** and **lib**). You must add both of these directories to both the **Include Directories** and **Library Directories**.

Then Click **Apply**. You can now close this window.

#### Step Three: Build and Run
The project should now build and run. If there are build errors open the project properties as before and ensure that the project has **glfw3.lib** and **opengl32.lib** under: **Linker**-> **Input**->**Additional Dependencies**

## Program Operation

### Executable
To run the project open/run the **Project_Template.exe** inside the **BUILD** folder.
The program will run and open a display window.
### Project
To run the project through visual studio ensure you have completed the "Installation/Setup" Portion of this document.
You can then click **Local Windows Debugger** which will run the program.
### During Run Time
If successfully built the program should display a rotating teapot which changes colour. This will continue until you wish to stop the program. 
You can stop the program by closing the program window or by stopping the program through visual studio.

## Links
### YouTube Video
https://youtu.be/fLXdPrNxk1c
### Git Repo
https://github.com/MattHough1999/COMP3015
