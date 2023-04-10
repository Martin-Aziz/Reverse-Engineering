# Softwareausstattung

Wenn Sie einen eigenen Rechner für die Veranstaltung mitbringen wollen -- was durchaus zu empfehlen ist, installieren Sie bitte (direkt auf dem Gerät oder in einer VM) ein 64-Bit Ubuntu Linux (oder ein anderes Linux, das auf der glibc basiert) in einer aktuellen Version. Eine Anleitung und Unterstützung finden Sie [hier](https://github.com/informatik-mannheim/linux-hsma/blob/master/doc/readme.md). Bitte versuchen Sie nicht, die Übungen ohne Linux zu lösen, es wartet eine Welt der Frustration und des Schmerzes 😭 auf Sie, durch die schon viele andere gegangen sind, die diesen einen wichtigen Tipp ignoriert haben.

Für die Durchführung der Assignments benötigen Sie die entsprechenden Tools, die Sie am besten vorher installieren. Auf der VM im Poolraum sind diese Tools bereits vorhanden. Bei Ihrem eigenen Rechner müssen Sie sie selbst installieren:

  * Java JDK 17 (wird von Ghidra benötigt)<br>`sudo apt install openjdk-17-jdk`
  * [Ghidra](https://ghidra-sre.org/) in der aktuellsten Version<br>Herunterladen und das ZIP-File auspacken. Ghidra wird über das Skript `ghidraRun` gestartet
  * [Radare 2](https://github.com/radareorg/radare2/releases/download/5.7.6/radare2_5.7.6_amd64.deb) in der aktuellen Version herunterladen und das Paket installieren<br>`sudo dpkg -i radare2_5.7.6_amd64.deb`
  * Git<br>`sudo apt install git meld git-cola`
  * GNU C-Compiler, Assembler und Debugger<br>`sudo apt install g++ make remake cmake gdb nasm`
  * Ruby-Interpreter für Crackmes<br>`sudo apt install ruby3.0`
  * Python-PIP<br>`sudo apt install python3-pip`
  * Hex-Editor<br>`sudo apt install hexedit hexyl`
  * [Java-Decompiler (jd)](https://github.com/java-decompiler/jd-gui/releases/download/v1.6.6/jd-gui-1.6.6.deb) in der aktuellen Version herunterladen und das Paket installieren<br>`sudo dpkg -i d-gui-1.6.6.deb`
  * Visual Studio Code als Editor<br>`sudo snap install code --classic`
