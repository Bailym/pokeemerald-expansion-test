#!/usr/bin/env python3
"""Open mGBA with the game booted straight into a playtest scenario.

Copies pokeemerald.gba to a play folder on the Windows side, writes the scenario's ID into the
copy's gBootScenario byte, and launches mGBA on it. The real ROM is never touched, so opening it
normally still plays the intro. Scenarios live in include/constants/debug_scenarios.h and
data/scripts/debug_scenarios.inc.

    python3 tools/playtest/play.py balwyn_done
    python3 tools/playtest/play.py --list
"""

import argparse
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
ROM = REPO / "pokeemerald.gba"
MAP_FILE = REPO / "pokeemerald.map"
SCENARIOS_HEADER = REPO / "include/constants/debug_scenarios.h"
MGBA = Path(os.environ.get("MGBA", "/mnt/c/Program Files/mGBA/mGBA.exe"))
ROM_BASE = 0x08000000


def read_scenarios():
    scenarios = {}
    for match in re.finditer(r"^#define SCENARIO_(\w+)\s+(\d+)", SCENARIOS_HEADER.read_text(), re.MULTILINE):
        name, scenario_id = match.group(1).lower(), int(match.group(2))
        if name != "none":
            scenarios[name] = scenario_id
    return scenarios


def find_symbol_address(symbol):
    match = re.search(rf"^\s+0x([0-9a-fA-F]+)\s+{symbol}$", MAP_FILE.read_text(), re.MULTILINE)
    if not match:
        sys.exit(f"{symbol} isn't in {MAP_FILE.name}. Build with plain `make` (scenarios are off in release builds).")
    return int(match.group(1), 16)


def windows_play_folder():
    local_app_data = subprocess.run(["cmd.exe", "/c", "echo %LOCALAPPDATA%"], capture_output=True, text=True,
                                    cwd="/mnt/c").stdout.strip()
    folder = Path(subprocess.run(["wslpath", "-u", local_app_data], capture_output=True, text=True).stdout.strip())
    return folder / "kernia-playtest"


def make_scenario_rom(name, scenario_id):
    offset = find_symbol_address("gBootScenario") - ROM_BASE
    rom = bytearray(ROM.read_bytes())
    if rom[offset] != 0:
        sys.exit(f"gBootScenario in {ROM.name} isn't 0 (found {rom[offset]}). Is the .map file out of date?")
    rom[offset] = scenario_id

    folder = windows_play_folder()
    folder.mkdir(parents=True, exist_ok=True)
    scenario_rom = folder / f"{name}.gba"
    scenario_rom.write_bytes(rom)
    # A leftover save from an earlier session would show up under Continue; scenarios always start fresh.
    scenario_rom.with_suffix(".sav").unlink(missing_ok=True)
    return scenario_rom


def main():
    scenarios = read_scenarios()
    parser = argparse.ArgumentParser(description="Open mGBA booted into a playtest scenario.")
    parser.add_argument("scenario", nargs="?", choices=sorted(scenarios), metavar="SCENARIO")
    parser.add_argument("--list", action="store_true", help="list the scenarios and exit")
    args = parser.parse_args()

    if args.list or not args.scenario:
        print("\n".join(sorted(scenarios, key=scenarios.get)))
        return
    if not ROM.exists() or not MAP_FILE.exists():
        sys.exit("Build the ROM with `make` first.")
    if MAP_FILE.stat().st_mtime < ROM.stat().st_mtime - 5:
        sys.exit(f"{MAP_FILE.name} is older than {ROM.name}; rebuild with `make`.")
    if not MGBA.exists() and not shutil.which(str(MGBA)):
        sys.exit(f"mGBA isn't at {MGBA}. Set the MGBA environment variable to its path.")

    scenario_rom = make_scenario_rom(args.scenario, scenarios[args.scenario])
    windows_rom = subprocess.run(["wslpath", "-w", str(scenario_rom)], capture_output=True, text=True).stdout.strip()
    subprocess.Popen([str(MGBA), windows_rom], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL,
                     start_new_session=True)
    print(f"Opened mGBA on {scenario_rom.name} ({windows_rom}).")


if __name__ == "__main__":
    main()
