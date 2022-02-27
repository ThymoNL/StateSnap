/*
 *     StateSnap - A module or Orbiter to periodically make scenario snapshots.
 *     Copyright (C) 2022  Thymo van Beers
 *
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License along
 *     with this program; if not, write to the Free Software Foundation, Inc.,
 *     51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#define ORBITER_MODULE
#include "StateSnap.h"
#include "Orbitersdk.h"

StateSnap::StateSnap(HINSTANCE hDLL) : Module(hDLL) {
    // TODO: Read cfg file
    filename = (char *)"StateSnap";
    interval = 10;
}

void StateSnap::clbkSimulationStart(oapi::Module::RenderMode mode) {
    threadExit = false;
    saveThread = std::thread([this] { Runnable(); });
    saveThread.detach();
}

void StateSnap::clbkSimulationEnd() {
    threadExit = true;
    cv.notify_all();
}

void StateSnap::Runnable() {
    while (true) {
        std::unique_lock<std::mutex> lk(mutex);
        if (cv.wait_for(lk, std::chrono::minutes(interval), [this] { return threadExit.load(); })) {
            break; // Woke up by exit
        }

        saveNeeded = true; // Signal to main thread.
    }
}

void StateSnap::clbkPostStep(double simt, double simdt, double mjd) {
    if (saveNeeded) {
        oapiSaveScenario(filename, "");
        saveNeeded = false;
    }
}

// DLL entry/exit points
StateSnap *module;

DLLCLBK void InitModule(HINSTANCE hDLL)
{
    module = new StateSnap(hDLL);
    oapiRegisterModule(module);
}

DLLCLBK void ExitModule(HINSTANCE hModule)
{
    // Module is deleted by Orbiter
}
