#!/usr/bin/python3
# -*- coding: utf-8 -*-

import subprocess
import os

# Absoluter Pfad zum Skript
script_path = os.path.abspath(__file__)

# Verzeichnis in dem das Skript liegt (Gleiches Verzeichnis in dem auch das Python Skript liegt)
script_dir = os.path.dirname(script_path)

# Speichere den Pfad zu unserer Crackme in dem Executable_Path
executable_path = os.path.join(script_dir, 'crackme')

# Festlegen der korrekten Inputs (Um die Sicherheitslücke und den Hinweis zu erhalten müsste man das Skript 2x starten mit einer sehr großen Zahl)
input1 = '999999999999999'

# Executable in einem Subprocess laufen lassen und den Output aufzeichnen
result = subprocess.run([executable_path], input=f'{input1}\n', capture_output=True, encoding='utf-8')

# Aufteilen des Ergebnisses für richtiges Layout
lines = result.stdout.strip().split(':')

# Ausgabe der Ein und Ausgaben
input1_entered = False

for line in lines:
	if not input1_entered:
		print(f'{line}: {input1}')
		input1_entered = True
		continue
	print(line)

