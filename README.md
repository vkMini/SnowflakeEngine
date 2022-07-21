# Snowflake Engine

## What is Snowflake Engine?

Snowflake Engine is a 2D rendering engine (with planned 3D support) made with the primary use case of game development in mind. It is also made with performance and ease of use in mind, so you can make your game and release it as fast as possible.

As of currently, the engine is still very early into its development, so many core features of any game engine are missing and are yet to be implemented.

## Getting Started

While the engine currently doesn't have any editor UI to make a game in, you can still build the engine from source and test it in its current state. The process of doing so is very straightforward and simple.

### Prerequisites

First, make you have [Git](https://git-scm.com/downloads) installed as this will be needed to obtain the engine's source code and keep it up to date with the latest commits.

Next, for Windows users, you'll need to have [Visual Studio 2022](https://visualstudio.microsoft.com/vs/) installed. This is will be the primary development environment used by Snowflake Engine for its development. It'll also be used to build the engine from source later on.

For MacOS and Linux users, you can use [XCode](https://developer.apple.com/xcode/) and [Visual Studio Code](https://code.visualstudio.com) respectively.

For Linux users optionally, you'll want to have the [Makefile Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.makefile-tools) extensions for VS Code installed, as this will help with the building process on Linux.

But Linux users will need to have [GNU Make](https://www.gnu.org/software/make/) installed to build the engine. 

### Building the engine

1. Cloning the engine

First, you'll want to clone the engine's source code into a folder on your computer using the command ```git clone https://github.com/vkMini/SnowflakeEngine.git```.

2. Generating Project Files

Once you have cloned the engine, go inside of the "Scripts" and here, you'll find scripts for generating project files for Windows, MacOS and Linux. Each generating project files for Visual Studio 2022, XCode and Makefile respectively. 

If you do want a script to generate project files for something else, you'll need to change the script manually. You can refer to the [Premake documentation](https://premake.github.io/docs/Using-Premake) for all available options.

Anyways, all you need to do is run the script for your respective platform and your project files should be generated.

3. Building and running the engine

Once you have generated your project files, you can open the Visual Studio solution, XCode project or the root direcotry in Visual Studio Code and you can now build and run the engine from source!

In Visual Studio, simply press F5 or click "Local Windows Debugger".

In XCode, click the "Run" button or use the shortcut "CMD + R"

In Visual Studio Code, assuming you have the "Makefile Tools" extension installed, you just click the "Run" button. For more info, you can refer to this [blog post](https://earthly.dev/blog/vscode-make/).

And that's it! You should now be up and running with the engine from it's source code.

## Current Plans for Snowflake Engine (**NOTE**: None of what is here is currently being worked on, but what I plan to have in the engine in the future)

- Create a functional editor UI interface
- Add support for an Entity Component System
- Add support for physics
- Add support for C# Scripting
- Add support for more graphics APIs, preferably Vulkan and/or DirectX
- Add support for 3D once 2D is complete.

## Contributing to Snowflake's developement

As of currently, Snowflake Engine is being developed by one person, me, vkMini. And developing a game engine by yourself is no easy task. That's why I need help from you guys, the community, with its development.

You can do this by doing things such as reporting bugs and opening isseus, or suggesting new features and improvements.

And if you have a copy of the engine's code, you can fix some these bugs or even add some of these suggested features and improvements yourself.

In the end, any and all contributions and help with the engine's development is greatly appreciated :heart:

## Credits

[The Cherno](https://www.youtube.com/c/TheChernoProject): Hazel 2D being the base of Snowflake Engine
