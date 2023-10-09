# Assignment 31

Unsere Abgabe enthält:

  - den kommentierten Source-Code des Crackme: [crackme.c](./crackme.c)
  - das ausführbare Crackme: [crack](./crack)
  - ein [Makefile](Makefile)
  - ein Setup-Script, das vom Makefile aufgerufen wird und die kompilierte Binary 
    unserem Server übergibt [setup_crackme.rb](./setup_crackme.rb)
  - ein automatisierten Löser [solve_crackme](./solve_crackme) bzw der Quellcode
    für diesen [solveme/src/main.rs](./solveme/src/main.rs)
  - eine textuelle Beschreibung der Schwachstelle [crackme.md](crackme.md)

Hinweise:
  - Die Ausnutzung basiert auf Adressen, die zur Compilezeit festgelegt werden. Wenn das Crackme neu kompiliert
      wird, müssen in der `main.rs` die gesendeten Bytes durch die neue Adresse der `win`-Funktion angepasst werden.
  - Der Schlüssel zur Entschlüsselung der Flag wird von einem Server geschickt. Die kompilierte Binary wird mit
      dem Schlüssel an den Server geschickt, um diesen Abruf zu ermöglichen. Dafür wird das Skript `setup_crackme.rb`
      im Makefile ausgeführt.