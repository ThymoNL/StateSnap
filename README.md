# StateSnap
StateSnap is a module for Orbiter implementing an autosave feature.
When StateSnap is enabled it will automatically save the current simulation to your Scenarios folder as "StateSnap".

This way you can revert to roughly what you were doing in case you made a mistake or Orbiter crashed.

# Installing
1. Get the dll from the release (or build it yourself, see below).
   2. The pre-built dll has been tested against the latest Orbiter Beta.
2. Place the dll in the `Modules\Plugin` directory in your Orbiter installation.
3. In the Orbiter Launchpad, enable the StateSnap module from the `Modules` tab.

## Building
You need the following things:
* CMake
* MSVC Toolchain
* (Recommended) CLion

### CMake variables
`ORBITER_SDK_DIR`: Path to Orbitersdk directory.\
`ORBITER_PLUGIN_DIR`: Path to install plugin to.