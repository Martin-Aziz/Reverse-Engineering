### Probleme:
- Keine Ausführungsberechtigung für die Datei
Lösung: chmod


### Vorgehen:
gbd password_check_4
run
gdp "bt" um den Stack auszulesen
Interessant für uns sind wahrscheinlich:
    Frame 7 - main
    Frame 6 - readPassword
Diese unstersuchen wir mit dem "disas" befehl

-Leider konnten wir den Assembly code nicht sinnoller interpretieren als die vermeindlichen Adressen der Flag und des Passworts auszulesen: 

Flag : 0x555555603028
Password : 0x555555603028

