Assignment 6:
Passwordcheck_1: FLAG{strings to the rescue} PW: gargelkarx
Passwordcheck_2: FLAG{to encrypt or not encrypt} PW: streng_geheim

Passwordcheck_3: FLAG{a nullaby} PW: ?
Encoding mit UCS-2 UTF-16 -> andere Formatierung und fehlende Nullterminierung führt dazu das Strings das ohne passende parameter die Flag nicht findet.

 strings -eb password_check_3
@8	@
01234!
FLAG{a nullaby}

