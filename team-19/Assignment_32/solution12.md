# Crackme12

In diesem crackme wird das Passwort mit einem vorher gesetzten String verglichen. Der string ist obfuscated. Die Funktion "set_and_obfuscate_password" macht aus "bhpa" "bird" indem es auf jeden char seine stelle addiert.

# code
    printf("%c ",'b'+0);
    printf("%c ",'h'+1);
    printf("%c ",'p'+2);
    printf("%c ",'a'+3);

# flag
Enter the password: bird
FLAG{_is_the_w0rd}
